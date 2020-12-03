#include "wabt/src/binary-writer.h"
#include "wabt/src/error.h"
#include "wabt/src/ir.h"
#include "wabt/src/validator.h"

#include "codegen/codegen.h"
#include "codegen/symtab.h"
#include "codegen/stringpool.h"
#include "codegen/wat-writer.h"
#include "utils/cast.h"
#include "utils/error.h"
#include "utils/result.h"

namespace dp {
namespace internal {

static bool toWasmType(Type* typ, wabt::Type& wtyp) {
	assert(typ != nullptr);
	if (auto ptype = dyn_cast<PrimitiveType>(typ)) {
		switch (ptype->kind()) {
		case PrimitiveType::I32:
			wtyp = wabt::Type(wabt::Type::I32);
			return true;
		case PrimitiveType::I64:
			wtyp = wabt::Type(wabt::Type::I32);
			return true;
		case PrimitiveType::F32:
			wtyp = wabt::Type(wabt::Type::I32);
			return true;
		case PrimitiveType::F64:
			wtyp = wabt::Type(wabt::Type::I32);
			return true;
		default:
			return false;
		}
	} else {
		return false;
	}
}

static void toWasmType(const TypeVector& typVec, wabt::TypeVector& wtypVec) {
	for (auto typ : typVec) {
		wabt::Type wtyp;
		if (toWasmType(typ, wtyp)) {
			wtypVec.emplace_back(wtyp);
		}
	}
}

static void functypet2funcsig(FunctionType* typ, wabt::FuncSignature& sig) {
	toWasmType(typ->params(), sig.param_types);
	TypeVector results;
	results.push_back(typ->result());
	toWasmType(results, sig.result_types);
}

class WasmVisitor {
public:
	Result visitModule(Module* node) {
		if (Failed(initEnv())) {
			return Result::Error;
		}
		for (auto& stmt : node->stmts) {
			if (Failed(visitStatement(stmt.get(), false))) {
				return Result::Error;
			}
		}
		if (Failed(generateDataSegment())) {
			return Result::Error;
		}
		return Result::Ok;
	}

	void appendTypeField(wabt::FuncSignature& sig) {
		auto type_field = std::make_unique<wabt::TypeModuleField>();
		auto type       = std::make_unique<wabt::FuncType>();
		type->sig       = sig;
		type_field->type.reset(type.release());
		module->AppendField(std::move(type_field));
	}

	void importFunc(const std::string& moduleName, const std::string& funcName, FunctionType* ftyp) {
		wabt::Location loc;
		auto           import = wabt::MakeUnique<wabt::FuncImport>();
		import->module_name   = moduleName;
		import->field_name    = funcName;

		symTab.addSym(funcName, module->funcs.size(), ftyp);

		auto func  = &import->func;
		func->name = funcName;
		functypet2funcsig(ftyp, func->decl.sig);
		appendTypeField(func->decl.sig);

		auto importField = wabt::MakeUnique<wabt::ImportModuleField>(std::move(import), loc);
		module->AppendField(std::move(importField));
	}

	// init some builtin function to import
	Result initEnv() {
		TypeVector params;
		params.push_back(Type::I32());
		auto typ = Type::Func(params, Type::I32());
		importFunc("env", "puts", cast<FunctionType>(typ));

		return Result::Ok;
	}

	Result generateDataSegment() {
		wabt::Location loc;
		auto           dataField           = wabt::MakeUnique<wabt::DataSegmentModuleField>(loc, "StrPool");
		dataField->data_segment.kind       = wabt::SegmentKind::Active;
		dataField->data_segment.memory_var = wabt::Var(module->memories.size());
		dataField->data_segment.offset.push_back(wabt::MakeUnique<wabt::ConstExpr>(wabt::Const::I32(0)));
		dataField->data_segment.data = stringPool.data();

		auto     memory_field                    = wabt::MakeUnique<wabt::MemoryModuleField>(loc, "memory");
		uint32_t byte_size                       = WABT_ALIGN_UP_TO_PAGE(dataField->data_segment.data.size());
		uint32_t page_size                       = WABT_BYTES_TO_PAGES(byte_size);
		memory_field->memory.page_limits.initial = page_size;
		memory_field->memory.page_limits.max     = page_size;
		memory_field->memory.page_limits.has_max = true;

		module->AppendField(std::move(memory_field));
		module->AppendField(std::move(dataField));

		return Result::Ok;
	}

	// Statements

	Result visitStatement(Statement* stmt, bool isLastStmt) {
		switch (stmt->kind()) {
		case StatementKind::Expression:
			return visitExpressionStatement(cast<ExpressionStatement>(stmt), isLastStmt);
		case StatementKind::SemiExpression:
			return visitSemiExpressionStatement(cast<SemiExpressionStatement>(stmt));
		case StatementKind::Function:
			return visitFunction(cast<FunctionStatement>(stmt));
		case StatementKind::Local:
			return visitLocalStatement(cast<LocalStatement>(stmt));
		default:
			UNREACHABLE("visitStatement");
		}
	}

	Result visitFunction(FunctionStatement* funcStmt) {
		auto           name = funcStmt->id.name;
		wabt::Location loc;

		if (!symTab.addSym(name, module->funcs.size(), funcStmt->typ)) {
			return Result::Error;
		}

		auto func_field = std::make_unique<wabt::FuncModuleField>(loc, name);
		func            = &func_field->func;

		if (Failed(visitFunctionType(funcStmt->typ))) {
			return Result::Error;
		}

		symTab.newEnv();

		for (auto param : funcStmt->params) {
			int index = func->local_types.size();
			func->bindings.emplace(param.id.name, wabt::Binding(index));
			wabt::Type ltyp;
			if (toWasmType(param.typ, ltyp)) {
				func->local_types.AppendDecl(ltyp, 1);
			} else {
				Error(funcStmt->loc, "visitFunction toWasmType");
				return Result::Error;
			}
			symTab.addSym(param.id.name, index, param.typ);
		}

		if (Failed(visitBlockExpression(funcStmt->body.get()))) {
			return Result::Error;
		}

		symTab.dropEnv();

		if (exprType != Type::Unit()) {
			if (auto retType = dyn_cast<PrimitiveType>(funcStmt->typ->result())) {
				if (retType->isUnit()) {
					auto expr = std::make_unique<wabt::DropExpr>();
					exprs.push_back(std::move(expr));
				} else if (Type::IsSame(exprType, retType)) {
					// TODO: Return
					Error(funcStmt->loc, "return");
					return Result::Error;
				} else {
					Error(funcStmt->loc, "return value is not same with return type");
					return Result::Error;
				}
			} else {
				UNREACHABLE("cast error");
			}
		}

		func->exprs.swap(exprs);

		module->AppendField(std::move(func_field));

		if (funcStmt->isPublic) {
			auto export_field          = std::make_unique<wabt::ExportModuleField>(loc);
			export_field->export_.kind = wabt::ExternalKind::Func;
			export_field->export_.name = name;
			auto index                 = module->funcs.size() - 1;
			export_field->export_.var  = wabt::Var(index, loc);
			module->AppendField(std::move(export_field));
		}

		return Result::Ok;
	}

	Result visitFunctionType(FunctionType* funcType) {
		wabt::Location loc;

		functypet2funcsig(funcType, func->decl.sig);
		appendTypeField(func->decl.sig);

		return Result::Ok;
	}

	Result visitLocalStatement(LocalStatement* localStmt) {
		std::string name  = localStmt->id.name;
		int         index = func->local_types.size();

		wabt::Type type;
		if (!toWasmType(localStmt->typ, type)) {
			Error(localStmt->loc, "visitLocalStatement toWasmType");
			return Result::Error;
		}

		func->bindings.emplace(name, wabt::Binding(index));
		func->local_types.AppendDecl(type, 1);

		visitExpression(localStmt->init.get());

		if (!symTab.addSym(name, index, localStmt->typ)) {
			Error(localStmt->loc, "declared variable '%s' is exists", name.c_str());
			return Result::Error;
		}

		wabt::Var var(name);
		var.set_index(index);
		auto expr = std::make_unique<wabt::LocalSetExpr>(var);
		exprs.push_back(std::move(expr));
		exprType = Type::Unit();
		return Result::Ok;
	}

	Result visitExpressionStatement(ExpressionStatement* exprStmt, bool isLastStmt) {
		if (Failed(visitExpression(exprStmt->expr.get()))) {
			return Result::Error;
		}
		// Drop unused oprands in stack
		if (!isLastStmt && exprType != Type::Unit()) {
			auto expr = std::make_unique<wabt::DropExpr>();
			exprs.push_back(std::move(expr));
			exprType = Type::Unit();
		}
		return Result::Ok;
	}

	Result visitSemiExpressionStatement(SemiExpressionStatement* semiStmt) {
		if (Failed(visitExpression(semiStmt->expr.get()))) {
			return Result::Error;
		}
		if (exprType != Type::Unit()) {
			auto expr = std::make_unique<wabt::DropExpr>();
			exprs.push_back(std::move(expr));
			exprType = Type::Unit();
		}
		return Result::Ok;
	}

	// Expressions

	Result visitExpression(Expression* expr) {
		switch (expr->kind()) {
		case ExpressionKind::Literal:
			return visitLiteralExpression(cast<LiteralExpression>(expr));
		case ExpressionKind::Path:
			return visitPathExpression(cast<PathExpression>(expr));
		case ExpressionKind::Binary:
			return visitBinaryExpression(cast<BinaryExpression>(expr));
		case ExpressionKind::Block:
			return visitBlockExpression(cast<BlockExpression>(expr));
		case ExpressionKind::Call:
			return visitCallExpression(cast<CallExpression>(expr));
		case ExpressionKind::If:
			return visitIfExpression(cast<IfExpression>(expr));
		default:
			UNREACHABLE("visitExpression");
		}
	}

	Result visitElseExpression(ElseExpression* elseExpr) {
		if (elseExpr->kind() == ExpressionKind::If) { // else if
			return visitIfExpression(cast<IfExpression>(elseExpr));
		} else if (elseExpr->kind() == ExpressionKind::Block) { // else
			return visitBlockExpression(cast<BlockExpression>(elseExpr));
		} else {
			UNREACHABLE("visitElseExpression");
		}
		return Result::Ok;
	}

	Result visitIfExpression(IfExpression* ifexpr) {
		wabt::Location                loc;
		std::unique_ptr<wabt::IfExpr> expr = std::make_unique<wabt::IfExpr>(loc);

		// FIXME: restrict conditonExpr
		visitExpression(ifexpr->condition.get());
		auto pt = dyn_cast<PrimitiveType>(exprType);
		if (!pt || !pt->isI32()) {
			Error(ifexpr->loc, "conditonExpr is not i32 type");
			return Result::Error;
		}

		expr->true_.exprs.swap(exprs);
		if (Failed(visitBlockExpression(ifexpr->then_branch.get()))) {
			return Result::Error;
		}
		expr->true_.exprs.swap(exprs);
		Type* thenType = exprType;

		Type* elseType{};
		if (ifexpr->else_branch) { //else
			expr->false_.swap(exprs);
			if (Failed(visitElseExpression(ifexpr->else_branch.get()))) {
				return Result::Error;
			}
			expr->false_.swap(exprs);
			elseType = exprType;
		} else {
			elseType = Type::Unit();
		}

		if (!Type::IsSame(thenType, elseType)) {
			Error(ifexpr->loc, "thenExpr and elseExpr is not same type");
			return Result::Error;
		}

		TypeVector voidVector;
		auto       blockType = Type::Func(voidVector, thenType);
		functypet2funcsig(cast<FunctionType>(blockType), expr->true_.decl.sig);
		appendTypeField(expr->true_.decl.sig);

		exprs.push_back(std::move(expr));
		return Result::Ok;
	}

	Result visitCallExpression(CallExpression* methodCall) {
		wabt::Location loc;
		for (auto& param : methodCall->params) {
			visitExpression(param.get());
		}

		if (auto pathExpr = dyn_cast<PathExpression>(methodCall->method.get())) {
			wabt::Var                   methodName  = wabt::Var(wabt::string_view(pathExpr->id.name));
			int                         index       = module->GetFuncIndex(methodName);
			wabt::Var                   methodIndex = wabt::Var(index);
			std::unique_ptr<wabt::Expr> expr        = std::make_unique<wabt::CallExpr>(methodIndex, loc);
			exprs.push_back(std::move(expr));

			auto typ = symTab.getSymType(pathExpr->id.name);
			if (auto ftyp = dyn_cast<FunctionType>(typ)) {
				exprType = ftyp->result();
			} else {
				Error(methodCall->loc, "symbol '%s' is not functype", pathExpr->id.name.c_str());
				return Result::Error;
			}
		} else {
			Error(methodCall->loc, "method is not a pathexpr");
			return Result::Error;
		}

		return Result::Ok;
	}

	Result visitLiteralExpression(LiteralExpression* lit) {
		wabt::Location              loc;
		std::unique_ptr<wabt::Expr> expr;
		switch (lit->typ) {
		case LiteralExpression::I32:
			expr     = std::make_unique<wabt::ConstExpr>(wabt::Const::I32(lit->i32val, loc), loc);
			exprType = Type::I32();
			break;
		case LiteralExpression::I64:
			expr     = std::make_unique<wabt::ConstExpr>(wabt::Const::I64(lit->i64val, loc), loc);
			exprType = Type::I64();
			break;
		case LiteralExpression::F32:
			expr     = std::make_unique<wabt::ConstExpr>(wabt::Const::F32(lit->f32val, loc), loc);
			exprType = Type::F32();
			break;
		case LiteralExpression::F64:
			expr     = std::make_unique<wabt::ConstExpr>(wabt::Const::F64(lit->f64val, loc), loc);
			exprType = Type::F64();
			break;
		case LiteralExpression::String: {
			auto offset = stringPool.add(lit->strval);
			expr        = std::make_unique<wabt::ConstExpr>(wabt::Const::I32(offset, loc), loc);
			exprType    = Type::String();
			break;
		}
		default:
			UNREACHABLE("visitLiteral");
		}
		exprs.push_back(std::move(expr));
		return Result::Ok;
	}

	Result visitBlockExpression(BlockExpression* block) {
		symTab.newEnv();
		for (auto iter = block->stmts.begin(); iter != block->stmts.end(); ++iter) {
			if (Failed(visitStatement(iter->get(), std::next(iter) == block->stmts.end()))) {
				return Result::Error;
			}
		}
		symTab.dropEnv();
		return Result::Ok;
	}

	Result visitPathExpression(PathExpression* path) {
		wabt::Location loc;
		int            ind = func->bindings.FindIndex(path->id.name);
		wabt::Var      var(ind, loc);

		if (ind < 0) {
			Error(path->loc, "local variable `%s' is not found!", path->id.name.c_str());
			return Result::Error;
		}

		std::unique_ptr<wabt::Expr> expr =
				std::make_unique<wabt::LocalGetExpr>(var);
		exprs.push_back(std::move(expr));
		exprType = symTab.getSymType(path->id.name);
		if (exprType == Type::Unit()) {
			Error(path->loc, "local variable `%s' can't find type!", path->id.name.c_str());
			return Result::Error;
		}

		return Result::Ok;
	}

	enum class BinaryOprandType {
		I32,
		I64,
		F32,
		F64
	};

	struct BinaryOpHasher {
		size_t operator()(const std::pair<BinaryOperator, BinaryOprandType>& p) const {
			size_t hash = 2u;
			hash ^= static_cast<size_t>(p.first) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
			hash ^= static_cast<size_t>(p.second) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
			return hash;
		}
	};

	Result visitBinaryExpression(BinaryExpression* bin) {
		wabt::Location              loc;
		std::unique_ptr<wabt::Expr> expr;

		if (Failed(visitExpression(bin->left.get()))) {
			return Result::Error;
		}
		auto leftType = std::move(exprType);
		assert(leftType);

		if (Failed(visitExpression(bin->right.get()))) {
			return Result::Error;
		}
		auto rightType = std::move(exprType);
		assert(rightType);

		BinaryOprandType typ{};

		if (!leftType->isNumberic() || !rightType->isNumberic()) {
			Error(bin->loc, "binary operand is not number");
			return Result::Error;
		}

		auto leftPrim  = cast<PrimitiveType>(leftType),
				 rightPrim = cast<PrimitiveType>(rightType);

		if (leftPrim->kind() != rightPrim->kind()) {
			Error(bin->loc, "binary operand is not same numberic type");
			return Result::Error;
		}

		switch (leftPrim->kind()) {
		case PrimitiveType::I32:
			typ = BinaryOprandType::I32;
			break;
		case PrimitiveType::I64:
			typ = BinaryOprandType::I64;
			break;
		case PrimitiveType::F32:
			typ = BinaryOprandType::F32;
			break;
		case PrimitiveType::F64:
			typ = BinaryOprandType::F64;
			break;
		default:
			UNREACHABLE("visitBinaryExpression");
		}

#define BIN_OPCODE(binOp, binType, wOp, retType) { std::make_pair(binOp, binType), std::make_pair(wOp, retType) },

		static std::unordered_map<std::pair<BinaryOperator, BinaryOprandType>,
															std::pair<wabt::Opcode::Enum, Type*>,
															BinaryOpHasher>
				binaryTable = {
#include "binaryop.def"
				};

		auto ret = binaryTable[std::make_pair(bin->op, typ)];
		expr     = std::make_unique<wabt::BinaryExpr>(ret.first, loc);
		exprType = ret.second;

		exprs.push_back(std::move(expr));
		return Result::Ok;
	}

	void Error(Location loc, const char* format, ...) {
		WABT_SNPRINTF_ALLOCA(buffer, length, format);
		errors.emplace_back(ErrorLevel::Error, loc, buffer);
	}

	WasmVisitor(Errors& errors)
			: errors(errors) {
	}

	std::unique_ptr<wabt::Module> module   = std::make_unique<wabt::Module>();
	wabt::Func*                   func     = nullptr;
	Type*                         exprType = Type::Unit();
	wabt::ExprList                exprs;
	SymTab                        symTab;
	StringPool                    stringPool;
	Errors&                       errors;
};

Result ValidateModule(wabt::Module* module, Errors& errors) {
	wabt::Errors          werrs;
	wabt::ValidateOptions options;

	auto result = wabt::ValidateModule(module, &werrs, options);
	if (wabt::Failed(result)) {
		for (auto err : werrs) {
			errors.emplace_back(ErrorLevel::Error, Location(), "[wabt validate] " + err.message);
		}
		return Result::Error;
	}

	return Result::Ok;
}

Result WriteBinaryModule(wabt::Module* module, const std::string& fileName, Errors& errors) {
	wabt::MemoryStream       stream;
	wabt::WriteBinaryOptions options;
	auto                     result = wabt::WriteBinaryModule(&stream, module, options);

	if (wabt::Succeeded(result)) {
		const auto& buffer = stream.output_buffer();
		buffer.WriteToFile(fileName);
		return Result::Ok;
	}

	return Result::Error;
}

Result WriteTextModule(wabt::Module* module, const std::string& fileName, Errors& errors) {
	wabt::MemoryStream    stream;
	wabt::WriteWatOptions options;
	auto                  result = wabt::WriteWat(&stream, module, options);

	if (wabt::Succeeded(result)) {
		const auto& buffer = stream.output_buffer();
		buffer.WriteToFile(fileName);
		return Result::Ok;
	}

	return Result::Error;
}

bool CodeGen::GenerateWasmToFile(Module* mod, const std::string& fileName, Errors& errors) {
	Result result = Result::Ok;
	do {
		auto visitor = std::make_unique<WasmVisitor>(errors);
		result       = visitor->visitModule(mod);
		if (Failed(result)) {
			break;
		}

		result = ValidateModule(visitor->module.get(), errors);
		// if (Failed(result)) {
		// 	break;
		// }

		result = WriteTextModule(visitor->module.get(), fileName, errors);
		if (Failed(result)) {
			break;
		}
	} while (false);

	return Succeeded(result);
}

bool CodeGen::GenerateWasm(Module* mod, std::vector<uint8_t>& bcBuffer, Errors& errors) {
	do {
		auto visitor = std::make_unique<WasmVisitor>(errors);
		auto result  = visitor->visitModule(mod);
		if (Failed(result)) {
			break;
		}

		result = ValidateModule(visitor->module.get(), errors);
		if (Failed(result)) {
			break;
		}

		wabt::MemoryStream       stream;
		wabt::WriteBinaryOptions options;
		auto                     getBuffResult = wabt::WriteBinaryModule(&stream, visitor->module.get(), options);

		if (wabt::Succeeded(getBuffResult)) {
			const auto& buffer = stream.output_buffer();
			bcBuffer           = buffer.data;
			return true;
		}
		return false;
	} while (false);

	return false;
}

} // namespace internal
} // namespace dp
