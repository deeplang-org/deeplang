#include "wabt/src/binary-writer.h"
#include "wabt/src/error.h"
#include "wabt/src/ir.h"
#include "wabt/src/validator.h"

#include "codegen/codegen.h"
#include "utils/cast.h"
#include "utils/error.h"
#include "utils/result.h"
#include "parsing/symtab.h"

namespace dp {
namespace internal {

class WasmVisitor {
public:
	Result visitModule(Module* node) {
		initEnv();
		for (auto& stmt : node->stmts) {
			visitStatement(stmt.get());
		}
		generateDataSegment();
		return Result::Ok;
	}

	// init some builtin function to import
	Result initEnv() {
		wabt::Location loc;
		auto           import = wabt::MakeUnique<wabt::FuncImport>();
		import->module_name   = "env";
		import->field_name    = "puts";

		auto func  = &import->func;
		func->name = "puts";
		func->decl.sig.param_types.emplace_back(wabt::Type::I32);
		func->decl.sig.result_types.emplace_back(wabt::Type::I32);
		auto type_field = std::make_unique<wabt::TypeModuleField>(loc);
		auto type       = std::make_unique<wabt::FuncType>();
		type->sig       = func->decl.sig;
		type_field->type.reset(type.release());
		module->AppendField(std::move(type_field));

		auto importField = wabt::MakeUnique<wabt::ImportModuleField>(std::move(import), loc);
		module->AppendField(std::move(importField));
	}

	Result generateDataSegment() {
		wabt::Location loc;
		auto           dataField           = wabt::MakeUnique<wabt::DataSegmentModuleField>(loc, "StrPool");
		dataField->data_segment.kind       = wabt::SegmentKind::Active;
		dataField->data_segment.memory_var = wabt::Var(module->memories.size());
		dataField->data_segment.offset.push_back(
				wabt::MakeUnique<wabt::ConstExpr>(wabt::Const::I32(0)));

		auto map = constStringSymTab.table;
		for (auto it = map.begin(); it != map.end(); it++) {
			std::string data = it->first;
			for (auto dataIter = data.begin(); dataIter != data.end(); dataIter++) {
				dataField->data_segment.data.push_back(*dataIter);
			}
			dataField->data_segment.data.push_back('\0');
		}

		auto     memory_field                    = wabt::MakeUnique<wabt::MemoryModuleField>(loc, "memory");
		uint32_t byte_size                       = WABT_ALIGN_UP_TO_PAGE(dataField->data_segment.data.size());
		uint32_t page_size                       = WABT_BYTES_TO_PAGES(byte_size);
		memory_field->memory.page_limits.initial = page_size;
		memory_field->memory.page_limits.max     = page_size;
		memory_field->memory.page_limits.has_max = true;

		module->AppendField(std::move(memory_field));
		module->AppendField(std::move(dataField));
	}
	// Statements

	Result visitStatement(Statement* stmt) {
		switch (stmt->kind()) {
		case StatementKind::ExpressionStatement:
			visitExpressionStatement(static_cast<ExpressionStatement*>(stmt));
			break;
		case StatementKind::FunctionDeclaration:
			visitFunction(static_cast<FunctionDeclaration*>(stmt));
			break;
		case StatementKind::VariableDeclaration:
			visitVariableDeclaration(static_cast<VariableDeclaration*>(stmt));
			break;
		default:
			return Result::Error;
		}
		return Result::Ok;
	}

	Result visitFunction(FunctionDeclaration* funNode) {
		auto           name = funNode->id.name;
		wabt::Location loc;

		auto func_field = std::make_unique<wabt::FuncModuleField>(loc, name);
		func            = &func_field->func;

		visitFunctionType(funNode->signature.get());

		for (auto& param : funNode->params) {
			int index = func->local_types.size();
			func->bindings.emplace(param.get()->id.name, wabt::Binding(index));
			func->local_types.AppendDecl(static_cast<PrimitiveType*>(param->typ.get())->toWasmType(), 1);
		}

		visitExpressionStatement(funNode->body.get());
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

	Result visitFunctionType(FunctionType* node) {
		wabt::Location loc;

		// TODO: first order function
		PrimitiveType* resultType = static_cast<PrimitiveType*>(node->Result.get());
		//		func->decl.sig.result_types.push_back(resultType->toWasmType());
		for (auto& param : node->Params) {
			func->decl.sig.param_types.emplace_back(static_cast<PrimitiveType*>(param.get())->toWasmType());
		}

		auto type_field = std::make_unique<wabt::TypeModuleField>(loc);
		auto type       = std::make_unique<wabt::FuncType>();

		type->sig = func->decl.sig;
		type_field->type.reset(type.release());

		module->AppendField(std::move(type_field));
		return Result::Ok;
	}

	Result visitVariableDeclaration(VariableDeclaration* varDecl) {
		std::string    name  = varDecl->id.name;
		int            index = func->local_types.size();
		wabt::Type     type  = wabt::Type::I32;
		wabt::Location loc;

		func->bindings.emplace(name, wabt::Binding(index));
		func->local_types.AppendDecl(type, 1);

		visitExpression(varDecl->init.get());

		wabt::Var var(name, loc);
		var.set_index(index);
		auto expr = std::make_unique<wabt::LocalSetExpr>(var);
		exprs.push_back(std::move(expr));
		return Result::Ok;
	}

    Result visitExpressionStatement(ExpressionStatement* exprStmt) {
        switch (exprStmt->esKind) {
            case ExpressionStatementKind::Condition:
                    return visitExpression(static_cast<ConditionExStmt*>(exprStmt)->lcond.get());
            case ExpressionStatementKind::Normal:
                    return visitExpression(exprStmt->expr.get());
        }
    }

	// Expressions

	Result visitExpression(Expression* expr) {
		switch (expr->kind()) {
		case ExpressionKind::Literal:
			return visitLiteralExpression(static_cast<LiteralExpression*>(expr));
		case ExpressionKind::Path:
			return visitPathExpression(static_cast<PathExpression*>(expr));
		case ExpressionKind::Binary:
			return visitBinaryExpression(static_cast<BinaryExpression*>(expr));
		case ExpressionKind::Block:
			return visitBlockExpression(static_cast<BlockExpession*>(expr));
		case ExpressionKind::Call:
			return visitCallExpression(static_cast<CallExpression*>(expr));
		default:
			UNREACHABLE("visitExpression");
			return Result::Error;
		}
	}

	Result visitCallExpression(CallExpression* methodCall) {
		wabt::Location loc;
		for (auto& param : methodCall->params) {
			visitExpression(param.get());
		}
		auto                        pathExpr    = static_cast<PathExpression*>(methodCall->method.get());
		wabt::Var                   methodName  = wabt::Var(wabt::string_view(pathExpr->id.name));
		int                         index       = module->GetFuncIndex(methodName);
		wabt::Var                   methodIndex = wabt::Var(index);
		std::unique_ptr<wabt::Expr> expr =
				std::make_unique<wabt::CallExpr>(methodIndex, loc);
		exprs.push_back(std::move(expr));
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
			int offset = constStringSymTab.offset;
			constStringSymTab.push(lit->strval, offset);
			expr     = std::make_unique<wabt::ConstExpr>(wabt::Const::I32(offset, loc), loc);
			exprType = Type::String();
			break;
		}
		default:
			UNREACHABLE("visitLiteral");
		}
		exprs.push_back(std::move(expr));
		return Result::Ok;
	}

	Result visitBlockExpression(BlockExpession* block) {
		for (auto& stmt : block->stmts) {
			visitStatement(stmt.get());
		}
		return Result::Ok;
	}

	Result visitPathExpression(PathExpression* path) {
		wabt::Location loc;
		int            ind = func->bindings.FindIndex(path->id.name);
		wabt::Var      var(ind, loc);

		if (ind < 0) {
			std::cout << "var '" << path->id.name << "' is not found!" << std::endl;
			return Result::Error;
		}

		std::unique_ptr<wabt::Expr> expr =
				std::make_unique<wabt::LocalGetExpr>(var);
		exprs.push_back(std::move(expr));
		// TODO: get var type
		exprType = Type::I32();

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

		BinaryOprandType typ = BinaryOprandType::I32;

		if (leftType->isNumberic() && rightType->isNumberic()) {
			auto leftPrim  = cast<PrimitiveType>(leftType.get()),
					 rightPrim = cast<PrimitiveType>(rightType.get());
			if (leftPrim->kind() != rightPrim->kind()) {
				// TODO: convert type
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
		} else {
			//TODO: emit error message
			return Result::Error;
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

	WasmVisitor()
			: module(std::make_unique<wabt::Module>()) {
	}

	std::unique_ptr<wabt::Module> module;
	wabt::ExprList                exprs;
	wabt::Func*                   func;
	TypePtr                       exprType;
	SymTab<int>                   constStringSymTab = 0;
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

bool CodeGen::GenerateWasmToFile(Module* mod, const std::string& fileName) {
	do {
		Errors errors;
		auto   visitor = std::make_unique<WasmVisitor>();
		auto   result  = visitor->visitModule(mod);
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

bool CodeGen::GenerateWasm(Module* mod, std::vector<uint8_t>& bcBuffer) {
	do {
		Errors errors;
		auto   visitor = std::make_unique<WasmVisitor>();
		auto   result  = visitor->visitModule(mod);
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
