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

		return Result::Ok;
	}

	Result generateDataSegment() {
		wabt::Location loc;
		auto           dataField           = wabt::MakeUnique<wabt::DataSegmentModuleField>(loc, "StrPool");
		dataField->data_segment.kind       = wabt::SegmentKind::Active;
		dataField->data_segment.memory_var = wabt::Var(module->memories.size());
		dataField->data_segment.offset.push_back(wabt::MakeUnique<wabt::ConstExpr>(wabt::Const::I32(0)));
		dataField->data_segment.data = constStringSymTab.data;

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

		auto func_field = std::make_unique<wabt::FuncModuleField>(loc, name);
		func            = &func_field->func;

		if (Failed(visitFunctionType(funNode->signature))) {
			return Result::Error;
		}

		for (auto& param : funNode->params) {
			int index = func->local_types.size();
			func->bindings.emplace(param.get()->id.name, wabt::Binding(index));
			func->local_types.AppendDecl(toWasmType(static_cast<PrimitiveType*>(param->typ)), 1);
		}

		if (Failed(visitExpressionStatement(funNode->body.get(), true))) {
			return Result::Error;
		}

		if (exprType != nullptr) {
			if (auto retType = dyn_cast<PrimitiveType>(funNode->signature->result())) {
				if (retType->isUnit()) {
					auto expr = std::make_unique<wabt::DropExpr>();
					exprs.push_back(std::move(expr));
				} else if (Type::IsSame(exprType, retType)) {
					// TODO: Return
					Error(Location(), "");
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

	Result visitFunctionType(FunctionType* funtypeNode) {
		wabt::Location loc;

		assert(funtypeNode->result());
		if (auto resultType = dyn_cast<PrimitiveType>(funtypeNode->result())) {
			if (!resultType->isUnit()) {
				func->decl.sig.result_types.push_back(toWasmType(resultType));
			}
		} else {
			UNREACHABLE("cast error");
		}

		for (auto& param : funtypeNode->params()) {
			if (auto paramType = dyn_cast<PrimitiveType>(param)) {
				func->decl.sig.param_types.emplace_back(toWasmType(paramType));
			} else {
				UNREACHABLE("cast error");
			}
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
			return visitLiteralExpression(static_cast<LiteralExpression*>(expr));
		case ExpressionKind::Path:
			return visitPathExpression(static_cast<PathExpression*>(expr));
		case ExpressionKind::Binary:
			return visitBinaryExpression(static_cast<BinaryExpression*>(expr));
		case ExpressionKind::Block:
			return visitBlockExpression(static_cast<BlockExpression*>(expr));
		case ExpressionKind::Call:
			return visitCallExpression(static_cast<CallExpression*>(expr));
		default:
			UNREACHABLE("visitExpression");
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
		std::unique_ptr<wabt::Expr> expr        = std::make_unique<wabt::CallExpr>(methodIndex, loc);
		exprs.push_back(std::move(expr));
		// TODO: get call return type
		exprType = Type::I32();
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
			auto offset = constStringSymTab.add(lit->strval, constStringSymTab.offset);
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
		for (auto iter = block->stmts.begin(); iter != block->stmts.end(); ++iter) {
			if (Failed(visitStatement(iter->get(), std::next(iter) == block->stmts.end()))) {
				return Result::Error;
			}
		}
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

		BinaryOprandType typ{};

		auto leftPrim  = cast<PrimitiveType>(leftType),
				 rightPrim = cast<PrimitiveType>(rightType);
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


  wabt::Type::Enum toWasmType(Type *typ) {
    // TODO: complete wasm type
		if (auto pt = cast<PrimitiveType>(typ)) {
      if (pt->isI32()) {
        return wabt::Type::I32;
      } else if (pt->isI64()) {
				return wabt::Type::I64;
//      } else if (pt->isUnit()) {
//        return wabt::Type::Void;
      } else if (pt->isF32()) {
        return wabt::Type::F32;
      } else if (pt->isF64()) {
        return wabt::Type::F64;
      } else {
        UNREACHABLE("can't find backend data type");
      }
		} else {
      UNREACHABLE("can't find backend data type");
    }
  }

	std::unique_ptr<wabt::Module> module;
	wabt::ExprList                exprs;
	wabt::Func*                   func;
	Type*                         exprType;
	SymTab<int>                   constStringSymTab = 0;
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
