#include "codegen.h"

#include "wabt/src/ir.h"


namespace dp {
namespace internal {

enum class Result {
	Ok,
	Error
};
//
//class WasmVisitor {
//public:
//	Result visitModule(Module* node) {
//		for (auto stmt : node->stmts) {
//			if (stmt->kind == AstKind::FunctionDeclaration) {
//				visitFunction(static_cast<FunctionDeclaration*>(stmt));
//			}
//		}
//	}
//
//	Result visitFunction(FunctionDeclaration* funNode) {
//		auto     name = funNode->id.name;
//		wabt::Location loc;
//		auto     func_field = std::make_unique<wabt::FuncModuleField>(loc, name);
//		auto&    func       = func_field->func;
//
//		visitFunctionType(funNode->signature, func);
//		visitFunctionBody(funNode->body, func);
//
//		module->AppendField(std::move(func_field));
//	}
//
//	Result visitFunctionType(FunctionType& node, Func& func) {
//		Location loc;
//
//		// TODO: params type
//		func.decl.sig.result_types.push_back(Type::I32);
//
//		auto type_field = std::make_unique<TypeModuleField>(loc);
//		auto type       = std::make_unique<FuncType>();
//
//		type->sig = func.decl.sig;
//		type_field->type.reset(type.release());
//
//		module->AppendField(std::move(type_field));
//		return Result::Ok;
//	}
//
//	Result visitFunctionBody(BlockExpession* body, wabt::Func& func) {
//		wabt::ExprList exprs;
//		for (auto node : body->stmts) {
//			visitStatement(node, exprs, func);
//		}
//		func.exprs.swap(exprs);
//		return Result::Ok;
//	}
//
//	Result visitVariableDeclaration(std::unique_ptr<VariableDeclaration>& varDecl, Func& func) {
//		std::string name = varDecl->id.name;
//		Type        type = Type::I32;
//		Location    loc;
//		func.bindings.emplace(name, Binding(loc, func.local_types.size()));
//		func.local_types.AppendDecl(type, func.local_types.size());
//		return Result::Ok;
//	}
//
//	Result visitIdentifier(Identifier* id, ExprList& exprs, Func& func) {
//		return Result::Ok;
//	}
//
//	Result visitLiteral(Literal* lit, ExprList& exprs) {
//		Location              loc;
//		std::unique_ptr<Expr> expr = std::make_unique<ConstExpr>(Const::I32(lit->i32val, loc), loc);
//		exprs.push_back(std::move(expr));
//		return Result::Ok;
//	}
//
//	//enum class BinaryOprandeType
//	//{
//	//	I32,
//	//	I64,
//	//	F32,
//	//	F64
//	//};
//
//	Result visitUnaryExpression(UnaryExpression* node, ExprList& exprs) {
//		return Result::Ok;
//	}
//
//	Result visitStatement(Statement* stmt, ExprList& exprs, Func& func) {
//		switch (stmt->kind) {
//		case AstKind::Literal:
//			visitLiteral(static_cast<Literal*>(stmt), exprs);
//			break;
//		case AstKind::Identifier:
//			visitIdentifier(static_cast<Identifier*>(stmt), exprs, func);
//			break;
//		case AstKind::BinaryExpression:
//			visitBinaryExpression(static_cast<BinaryExpression*>(stmt), exprs, func);
//			break;
//		case AstKind::UnaryExpression:
//		case AstKind::UpdateExpression:
//			return Result::Error;
//		}
//		return Result::Ok;
//	}
//
//	Result visitBinaryExpression(BinaryExpression* node, ExprList& exprs, Func& func) {
//		Location              loc;
//		std::unique_ptr<Expr> expr;
//		switch (node->op) {
//		case BinaryOperator::Plus:
//			expr = std::make_unique<BinaryExpr>(Opcode::I32Add, loc);
//			break;
//		case BinaryOperator::Minus:
//			expr = std::make_unique<BinaryExpr>(Opcode::I32Sub, loc);
//			break;
//		case BinaryOperator::Mult:
//			expr = std::make_unique<BinaryExpr>(Opcode::I32Mul, loc);
//			break;
//		case BinaryOperator::Div:
//			expr = std::make_unique<BinaryExpr>(Opcode::I32DivS, loc);
//			break;
//		case BinaryOperator::BitwiseAnd:
//			expr = std::make_unique<BinaryExpr>(Opcode::I32And, loc);
//			break;
//		case BinaryOperator::BitwiseOr:
//			expr = std::make_unique<BinaryExpr>(Opcode::I32Or, loc);
//			break;
//		}
//
//		exprs.push_back(std::move(expr));
//
//		return Result::Ok;
//	}
//
//	std::string result() {
//		return std::string();
//	}
//
//	WasmVisitor()
//			: module(std::make_unique<Module>()) {
//	}
//
//	std::unique_ptr<Module> module;
//};

CodeGen::CodeGen() {
	std::unique_ptr<Module> module;
}

std::string CodeGen::generateWat(Module& bexp) {
	//auto visitor = std::make_unique<WasmVisitor>();

	//// Validate Module

	//// Gernerate Wat

	//return visitor->result();
	return std::string();
}

} // namespace internal
} // namespace dp
