#pragma once
#include "ast/ast.h"
#include "antlr4-runtime.h"
#include "DLParserVisitor.h"

namespace dp {
namespace internal {

class Parser : public DLParserVisitor {
public:
	Module* parseModule(antlr4::ANTLRInputStream);

private:
	std::string prettyPrint(std::string);

	antlrcpp::Any visitAryOp(DLParser::AryOpContext* context);

	antlrcpp::Any visitParam(DLParser::ParamContext* context);

	antlrcpp::Any visitParamList(DLParser::ParamListContext* context);

	antlrcpp::Any visitExpressionList(DLParser::ExpressionListContext* context);

	antlrcpp::Any visitExpressionStatement(DLParser::ExpressionStatementContext* context);

	antlrcpp::Any visitBlockExpression(DLParser::BlockExpressionContext* context);

	antlrcpp::Any visitUnblockExpression(DLParser::UnblockExpressionContext* context);

	antlrcpp::Any visitTupleType(DLParser::TupleTypeContext* context);

	antlrcpp::Any visitType(DLParser::TypeContext* context);

	antlrcpp::Any visitVariableDecl(DLParser::VariableDeclContext* context);

	antlrcpp::Any visitFunctionDecl(DLParser::FunctionDeclContext* context);

	antlrcpp::Any visitDecl(DLParser::DeclContext* context);

	antlrcpp::Any visitStatement(DLParser::StatementContext* context);

	antlrcpp::Any visitStatements(DLParser::StatementsContext* context);

	antlrcpp::Any visitModule(DLParser::ModuleContext* context);
};

} // namespace internal
} // namespace dp
