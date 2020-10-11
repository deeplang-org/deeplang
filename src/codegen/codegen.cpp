#include "codegen.h"

#include "wabt/src/binary-writer.h"
#include "wabt/src/error.h"
#include "wabt/src/ir.h"
#include "wabt/src/validator.h"

namespace dp {
namespace internal {

enum class Result {
	Ok,
	Error
};

class WasmVisitor {
public:
	Result visitModule(Module* node) {
		for (auto& stmt : node->stmts) {
			visitStatement(stmt.get());
		}
		return Result::Ok;
	}

	// Statements

	Result visitStatement(Statement* stmt) {
		switch (stmt->kind()) {
		case StatementKind::Expression:
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

		// TODO: params type
		//func->decl.sig.result_types.push_back(wabt::Type::I32);

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
		return visitExpression(exprStmt->expr.get());
	}

	// Expressions

	Result visitExpression(Expression* expr) {
		switch (expr->kind()) {
		case ExpressionKind::Literal:
			visitLiteral(static_cast<LiteralExpression*>(expr));
			break;
		case ExpressionKind::Path:
			visitPathExpression(static_cast<PathExpression*>(expr));
			break;
		case ExpressionKind::Binary:
			visitBinaryExpression(static_cast<BinaryExpression*>(expr));
			break;
		case ExpressionKind::Block:
			visitBlockExpression(static_cast<BlockExpession*>(expr));
			break;
		default:
			return Result::Error;
		}
		return Result::Ok;
	}

	Result visitLiteral(LiteralExpression* lit) {
		wabt::Location              loc;
		std::unique_ptr<wabt::Expr> expr =
				std::make_unique<wabt::ConstExpr>(wabt::Const::I32(lit->i32val, loc), loc);
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
		}

		std::unique_ptr<wabt::Expr> expr =
				std::make_unique<wabt::LocalGetExpr>(var);
		exprs.push_back(std::move(expr));
		return Result::Ok;
	}

	Result visitBinaryExpression(BinaryExpression* node) {
		wabt::Location              loc;
		std::unique_ptr<wabt::Expr> expr;

		visitExpression(node->right.get());
		visitExpression(node->left.get());

		switch (node->op) {
		case BinaryOperator::Plus:
			expr = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I32Add, loc);
			break;
		case BinaryOperator::Minus:
			expr = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I32Sub, loc);
			break;
		case BinaryOperator::Mult:
			expr = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I32Mul, loc);
			break;
		case BinaryOperator::Div:
			expr = std::make_unique<wabt::BinaryExpr>(wabt::Opcode::I32DivS, loc);
			break;
			//case BinaryOperator::BitwiseAnd:
			//	expr = std::make_unique<BinaryExpr>(Opcode::I32And, loc);
			//	break;
			//case BinaryOperator::BitwiseOr:
			//	expr = std::make_unique<BinaryExpr>(Opcode::I32Or, loc);
			//	break;
		}

		exprs.push_back(std::move(expr));

		return Result::Ok;
	}

	std::string result() {
		return std::string();
	}

	WasmVisitor()
			: module(std::make_unique<wabt::Module>()) {
	}

	std::unique_ptr<wabt::Module> module;
	wabt::ExprList                exprs;
	wabt::Func*                   func;
};

static void WriteBufferToFile(wabt::string_view         filename,
															const wabt::OutputBuffer& buffer) {
	//if (s_dump_module) {
	//	std::unique_ptr<FileStream> stream = FileStream::CreateStdout();
	//	if (s_verbose) {
	//		stream->Writef(";; dump\n");
	//	}
	//	if (!buffer.data.empty()) {
	//		stream->WriteMemoryDump(buffer.data.data(), buffer.data.size());
	//	}
	//}

	buffer.WriteToFile(filename);
}

std::string CodeGen::generateWasm(Module* mod, const std::string& fileName) {
	auto visitor = std::make_unique<WasmVisitor>();
	visitor->visitModule(mod);

	wabt::Errors          errors;
	wabt::ValidateOptions options;
	auto                  result = wabt::ValidateModule(visitor->module.get(), &errors, options);
	if (wabt::Succeeded(result)) {
		wabt::MemoryStream       stream;
		wabt::WriteBinaryOptions options;
		result = wabt::WriteBinaryModule(&stream, visitor->module.get(), options);

		if (wabt::Succeeded(result)) {
			WriteBufferToFile(fileName, stream.output_buffer());
		}
	}
	else {
		std::cout << "Codegen Error: " << std::endl;
		for (auto err : errors) {
			std::cout << err.message << std::endl;
		}
	}

	return std::string();
}

} // namespace internal
} // namespace dp
