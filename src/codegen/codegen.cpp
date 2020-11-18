#include "wabt/src/binary-writer.h"
#include "wabt/src/error.h"
#include "wabt/src/ir.h"
#include "wabt/src/validator.h"

#include "codegen/codegen.h"
#include "codegen/symtab.h"
#include "codegen/stringpool.h"
#include "utils/cast.h"
#include "utils/error.h"
#include "utils/result.h"

namespace dp {
namespace internal {

static bool toWasmType(Type* typ, wabt::Type& wtyp) {
	if (!typ) {
		return false;
	}
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
		dataField->data_segment.data = stringPool.data;

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
			return visitExpressionStatement(static_cast<ExpressionStatement*>(stmt), isLastStmt);
			break;
		case StatementKind::FunctionDeclaration:
			return visitFunction(static_cast<FunctionDeclaration*>(stmt));
			break;
		case StatementKind::VariableDeclaration:
			return visitVariableDeclaration(static_cast<VariableDeclaration*>(stmt));
			break;
		default:
			UNREACHABLE("visitStatement");
		}
	}

	Result visitFunction(FunctionDeclaration* funNode) {
		auto           name = funNode->id.name;
		wabt::Location loc;

		if (!symTab.addSym(name, module->funcs.size(), funNode->signature)) {
			return Result::Error;
		}

		auto func_field = std::make_unique<wabt::FuncModuleField>(loc, name);
		func            = &func_field->func;

		if (Failed(visitFunctionType(funNode->signature))) {
			return Result::Error;
		}

		symTab.newEnv();

		for (auto param : funNode->params) {
			int index = func->local_types.size();
			func->bindings.emplace(param.id.name, wabt::Binding(index));
			wabt::Type ltyp;
			if (toWasmType(param.typ, ltyp)) {
				func->local_types.AppendDecl(ltyp, 1);
			} else {
				Error(Location(), "visitFunction toWasmType");
				return Result::Error;
			}
			symTab.addSym(param.id.name, index, param.typ);
		}

		if (Failed(visitExpressionStatement(funNode->body.get(), true))) {
			return Result::Error;
		}

		symTab.dropEnv();

		if (exprType != nullptr) {
			if (auto retType = dyn_cast<PrimitiveType>(funNode->signature->result())) {
				if (retType->isUnit()) {
					auto expr = std::make_unique<wabt::DropExpr>();
					exprs.push_back(std::move(expr));
				} else if (Type::IsSame(exprType, retType)) {
					// TODO: Return
					Error(Location(), "return");
					return Result::Error;
				} else {
					Error(Location(), "return value is not same with return type");
					return Result::Error;
				}
			} else {
				UNREACHABLE("cast error");
			}
		}

		func->exprs.swap(exprs);

		module->AppendField(std::move(func_field));

		if (funNode->isPublic) {
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

	Result visitVariableDeclaration(VariableDeclaration* varDecl) {
		std::string name  = varDecl->id.name;
		int         index = func->local_types.size();

		wabt::Type type;
		if (!toWasmType(varDecl->typ, type)) {
			Error(Location(), "visitVariableDeclaration toWasmType");
			return Result::Error;
		}

		func->bindings.emplace(name, wabt::Binding(index));
		func->local_types.AppendDecl(type, 1);

		visitExpression(varDecl->init.get());

		if (!symTab.addSym(name, index, varDecl->typ)) {
			Error(Location(), "declared variable '%s' is exists", name.c_str());
			return Result::Error;
		}

		wabt::Var var(name);
		var.set_index(index);
		auto expr = std::make_unique<wabt::LocalSetExpr>(var);
		exprs.push_back(std::move(expr));
		exprType = nullptr;
		return Result::Ok;
	}

	Result visitExpressionStatement(ExpressionStatement* exprStmt, bool isLastStmt) {
		if (Failed(visitExpression(exprStmt->expr.get()))) {
			return Result::Error;
		}
		// Drop unused oprands in stack
		if (!isLastStmt && exprType != nullptr) {
			auto expr = std::make_unique<wabt::DropExpr>();
			exprs.push_back(std::move(expr));
			exprType = nullptr;
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
			Error(Location(), "conditonExpr is not i32 type");
			return Result::Error;
		}

		expr->true_.label = "ifExpr";

		if (Failed(visitBlockExpression(ifexpr->then_branch.get()))) {
			return Result::Error;
		}
		expr->true_.exprs.swap(exprs);
		Type* thenType = exprType;

		if (ifexpr->else_branch) { //else
			if (Failed(visitElseExpression(ifexpr->else_branch.get()))) {
				return Result::Error;
			}
		}
		expr->false_.swap(exprs);
		Type* elseType = exprType;

		if (!Type::IsSame(thenType, elseType)) {
			Error(Location(), "thenExpr and elseExpr is not same type");
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
				Error(Location(), "symbol '%s' is not functype", pathExpr->id.name.c_str());
				return Result::Error;
			}
		} else {
			Error(Location(), "method is not a pathexpr");
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
			auto offset = stringPool.add(lit->strval, stringPool.offset);
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
			Error(Location(), "local variable `%s' is not found!", path->id.name.c_str());
			return Result::Error;
		}

		std::unique_ptr<wabt::Expr> expr =
				std::make_unique<wabt::LocalGetExpr>(var);
		exprs.push_back(std::move(expr));
		exprType = symTab.getSymType(path->id.name);
		if (exprType == nullptr) {
			Error(Location(), "local variable `%s' can't find type!", path->id.name.c_str());
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

	Result visitBinaryExpression(BinaryExpression* bin) {
		wabt::Location              loc;
		std::unique_ptr<wabt::Expr> expr;

		if (Failed(visitExpression(bin->right.get()))) {
			return Result::Error;
		}
		auto rightType = std::move(exprType);
		assert(rightType);

		if (Failed(visitExpression(bin->left.get()))) {
			return Result::Error;
		}
		auto leftType = std::move(exprType);
		assert(leftType);

		BinaryOprandType typ{};

		if (!leftType->isNumberic() || !rightType->isNumberic()) {
			Error(Location(), "binary operand is not number");
			return Result::Error;
		}

		auto leftPrim  = cast<PrimitiveType>(leftType),
				 rightPrim = cast<PrimitiveType>(rightType);

		if (leftPrim->kind() != rightPrim->kind()) {
			Error(Location(), "binary operand is not same numberic type");
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

		switch (bin->op) {
		case BinaryOperator::Plus:
			switch (typ) {
			case BinaryOprandType::I32:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I32Add, loc);
				exprType = Type::I32();
				break;
			case BinaryOprandType::I64:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I64Add, loc);
				exprType = Type::I64();
				break;
			case BinaryOprandType::F32:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::F32Add, loc);
				exprType = Type::F32();
				break;
			case BinaryOprandType::F64:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::F64Add, loc);
				exprType = Type::F64();
				break;
			}
			break;
		case BinaryOperator::Minus:
			switch (typ) {
			case BinaryOprandType::I32:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I32Sub, loc);
				exprType = Type::I32();
				break;
			case BinaryOprandType::I64:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I64Sub, loc);
				exprType = Type::I64();
				break;
			case BinaryOprandType::F32:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::F32Sub, loc);
				exprType = Type::F32();
				break;
			case BinaryOprandType::F64:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::F64Sub, loc);
				exprType = Type::F64();
				break;
			}
			break;
		case BinaryOperator::Mult:
			switch (typ) {
			case BinaryOprandType::I32:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I32Mul, loc);
				exprType = Type::I32();
				break;
			case BinaryOprandType::I64:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I64Mul, loc);
				exprType = Type::I64();
				break;
			case BinaryOprandType::F32:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::F32Mul, loc);
				exprType = Type::F32();
				break;
			case BinaryOprandType::F64:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::F64Mul, loc);
				exprType = Type::F64();
				break;
			}
			break;
		case BinaryOperator::Div:
			switch (typ) {
			case BinaryOprandType::I32:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I32DivS, loc);
				exprType = Type::I32();
				break;
			case BinaryOprandType::I64:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I64DivS, loc);
				exprType = Type::I64();
				break;
			case BinaryOprandType::F32:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::F32Div, loc);
				exprType = Type::F32();
				break;
			case BinaryOprandType::F64:
				expr     = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::F64Div, loc);
				exprType = Type::F64();
				break;
			}
			break;
		}
		exprs.push_back(std::move(expr));
		return Result::Ok;
	}

	WasmVisitor(Errors& errors)
			: module(std::make_unique<wabt::Module>()), errors(errors) {
	}

	void Error(Location loc, const char* format, ...) {
		WABT_SNPRINTF_ALLOCA(buffer, length, format);
		errors.emplace_back(ErrorLevel::Error, loc, buffer);
	}

	std::unique_ptr<wabt::Module> module;
	wabt::ExprList                exprs;
	wabt::Func*                   func;
	Type*                         exprType;
	SymTab                        symTab;
	StringPool<int>               stringPool;
	Errors&                       errors;
};

Result ValidateModule(wabt::Module* module) {
	wabt::Errors          errors;
	wabt::ValidateOptions options;

	auto result = wabt::ValidateModule(module, &errors, options);
	if (wabt::Failed(result)) {
		std::cout << "Codegen Error: " << std::endl;
		for (auto err : errors) {
			std::cout << err.message << std::endl;
		}
		return Result::Error;
	}

	return Result::Ok;
}

Result WriteModule(wabt::Module* module, const std::string& fileName) {
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

bool CodeGen::GenerateWasmToFile(Module* mod, const std::string& fileName, Errors& errors) {
	do {
		auto visitor = std::make_unique<WasmVisitor>(errors);
		auto result  = visitor->visitModule(mod);
		if (Failed(result)) {
			break;
		}

		result = ValidateModule(visitor->module.get());
		if (Failed(result)) {
			break;
		}

		result = WriteModule(visitor->module.get(), fileName);
		if (Failed(result)) {
			break;
		}

		return true;
	} while (false);

	// TODO: print error

	return false;
}

bool CodeGen::GenerateWasm(Module* mod, std::vector<uint8_t>& bcBuffer, Errors& errors) {
	do {
		auto visitor = std::make_unique<WasmVisitor>(errors);
		auto result  = visitor->visitModule(mod);
		if (Failed(result)) {
			break;
		}

		result = ValidateModule(visitor->module.get());
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

	// TODO: print error

	return false;
}

} // namespace internal
} // namespace dp
