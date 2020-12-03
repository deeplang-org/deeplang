#pragma once
#include "ast/ast.h"
#include "antlr4-runtime.h"
#include "parsing/gen/DLParserVisitor.h"

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

	antlrcpp::Any visitExpressionStmt(DLParser::ExpressionStmtContext* context);

	antlrcpp::Any visitSemiexpressionStmt(DLParser::SemiexpressionStmtContext* context);

	antlrcpp::Any visitBlockExpression(DLParser::BlockExpressionContext* context);

	antlrcpp::Any visitUnblockExpression(DLParser::UnblockExpressionContext* context);

	antlrcpp::Any visitIfExpression(DLParser::IfExpressionContext* context);

	antlrcpp::Any visitElseExpression(DLParser::ElseExpressionContext* context);

	antlrcpp::Any visitTupleType(DLParser::TupleTypeContext* context);

	antlrcpp::Any visitType(DLParser::TypeContext* context);

	antlrcpp::Any visitLocalStmt(DLParser::LocalStmtContext* context);

	antlrcpp::Any visitFunctionStmt(DLParser::FunctionStmtContext* context);

	antlrcpp::Any visitStatement(DLParser::StatementContext* context);

	antlrcpp::Any visitStatements(DLParser::StatementsContext* context);

	antlrcpp::Any visitModule(DLParser::ModuleContext* context);
};

} // namespace internal
} // namespace dp
