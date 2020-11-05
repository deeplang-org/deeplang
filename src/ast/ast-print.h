/*
 *  ast-print.h
 *  TODO: width limit
 *        text wrap
 *
 *
 */




#pragma once
#include "common.h"

#include "ast/ast.h"
#include "ast/type.h"
#include "utils/error.h"

namespace dp {
namespace internal {

constexpr unsigned int hash(const char *s, int off = 0) {                        
    return !s[off] ? 5381 : (hash(s, off+1)*33) ^ s[off];                           
}


void AstPrint(ASTNode object, int indent = 0) {
	std::string objectType = object.toString();
	std::string indentStuff = (indent, '\t');
	switch(hash(objectType)){
		case hash("Identifier"):
			printf(indentStuff);
			printf("Identifier name : %s", object.name);
			break;
		case hash("Module"):
			printf(indentStuff);
			printf("Module {\n");
			printf(indentStuff); printf(indentStuff);
			printf("id : \n");
			AstPrint(object.id, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("stmts : \n");
			PrintStatementPtrVec(object.stmts, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		/*  case hash("Statement"):
		 *  case hash("StatementMixin"):
		 *  -> VariableDeclaration
		 *	   FunctionDeclaration
		 *     Expression
		 *
		 */
		case hash("ExpressionStatement"):
			printf(indentStuff);
			printf("ExpressionStatement {\n");
			printf(indentStuff); printf(indentStuff);
			printf("expr : \n");
			PrintExpressionPtr(object.expr, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("VariableDeclaration"):
			printf(indentStuff);
			printf("VariableDeclaration {\n");
			printf(indentStuff); printf(indentStuff);
			printf("id : \n");
			AstPrint(object.id, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("vartype : \n");
			PrintTypePtr(object.vartype, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("init : \n");
			PrintExpressionPtr(object.init, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("FunctionDeclaration"):
			printf(indentStuff);
			printf("FunctionDeclaration {\n");
			printf(indentStuff); printf(indentStuff);
			printf("id : \n");
			AstPrint(object.id, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("signature : \n");
			PrintFunctionTypePtr(object.signature, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("init : \n");
			PrintExpressionStatementPtr(object.body, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("params : \n");
			PrintParamPtrVec(object.params, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("isPublic : %s \n", object.isPublic?"true":"false");
			printf(indentStuff);
			printf("}\n");
			break;

		/*
		 *  case hash("Expression"):
		 *  case hash("ExpressionMixin"):
		 *  -> ExpressionKind
		 *
		 */
		case hash("BinaryExpression"):
			printf(indentStuff);
			printf("BinaryExpression {\n");
			printf(indentStuff); printf(indentStuff);
			printf("op : \n");
			// TODO: BinaryOperator{Plus, Minus, ...}
			// AstPrint(object.op, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("left : \n");
			PrintExpressionPtr(object.left, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("right : \n");
			PrintExpressionPtr(object.right, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("CallExpression"):
			printf(indentStuff);
			printf("CallExpression {\n");
			printf(indentStuff); printf(indentStuff);
			printf("receiver : \n");
			PrintExpressionPtr(object.receiver, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("method : \n");
			PrintExpressionPtr(object.method, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("params : \n");
			PrintExpressionPtrVec(object.params, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("LiteralExpression"):
			printf(indentStuff);
			printf("LiteralExpression {\n");
			printf(indentStuff); printf(indentStuff);
			printf("type : %d \n", typ);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("PathExpression"):
			printf(indentStuff);
			printf("PathExpression {\n");
			printf(indentStuff); printf(indentStuff);
			printf("id : \n");
			AstPrint(object.id, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("BlockExpession"):
			printf(indentStuff);
			printf("BlockExpession {\n");
			printf(indentStuff); printf(indentStuff);
			printf("stmts : \n");
			PrintStatementPtrVec(object.stmts, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		//TODO: ConditionExpression, ElseExpression
		case hash("IfExpression"):
			printf(indentStuff);
			printf("IfExpression {\n");
			printf(indentStuff); printf(indentStuff);
			printf("condition : \n");
			PrintConditionExpressionPtr(object.condition, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("then_branch : \n");
			PrintBlockExpessionPtr(object.then_branch, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("else_branch : \n");
			PrintElseExpressionPtr(object.else_branch, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("WhileExpression"):
			printf(indentStuff);
			printf("WhileExpression {\n");
			printf(indentStuff); printf(indentStuff);
			printf("condition : \n");
			PrintConditionExpressionPtr(object.condition, indent+1);
			printf(indentStuff); printf(indentStuff);
			printf("body : \n");
			PrintBlockExpessionPtr(object.body, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("BreakExpression"):
			printf(indentStuff);
			printf("BreakExpression {\n");
			printf(indentStuff); printf(indentStuff);
			printf("value : \n");
			PrintExpressionPtr(object.value, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		case hash("ContinueExpression"):
			printf(indentStuff);
			printf("ContinueExpression {}\n");
			break;
		case hash("ReturnExpression"):
			printf(indentStuff);
			printf("ReturnExpression {\n");
			printf(indentStuff); printf(indentStuff);
			printf("value : \n");
			PrintExpressionPtr(object.value, indent+1);
			printf(indentStuff);
			printf("}\n");
			break;
		default:
			// no match
			break;
	}

	return;
}

/*
 *  pointer printer
 *  std::unique<*>
 */
void PrintTypePtr(std::unique_ptr<Type> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("TypePtr Type : %s  \n", object->getTypeClassName());
	return;
}

void PrintStatementPtr(std::unique_ptr<Statement> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("StatementPtr : \n");
	AstPrint(*object, indent+1);
	return;
}

void PrintModulePtr(std::unique_ptr<Module> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("ModulePtr : \n");
	AstPrint(*object, indent+1);
	return;
}

void PrintExpressionPtr(std::unique_ptr<Expression> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("ExpressionPtr : \n");
	AstPrint(*object, indent+1);
	return;
}

void PrintParamPtr(std::unique_ptr<Param> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("Param {\n");
	printf(indentStuff); printf(indentStuff);
	printf("id : \n");
	AstPrint(object->id, indent+1);
	printf(indentStuff); printf(indentStuff);
	printf("type : \n");
	PrintTypePtr(object->typ, indent+1);
	printf(indentStuff);
	printf("}\n");
	return;
}

void PrintFunctionTypePtr(std::unique_ptr<FunctionType> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("FunctionType {\n");
	printf(indentStuff); printf(indentStuff);
	printf("Params : \n");
	PrintTypePtr(object->Params, indent+1);
	printf(indentStuff); printf(indentStuff);
	printf("Result : \n");
	PrintTypePtrVec(object->Result, indent+1);
	printf(indentStuff);
	printf("}\n");
	return;
}

void PrintExpressionStatementPtr(std::unique_ptr<ExpressionStatement> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("ExpressionStatementPtr : \n");
	AstPrint(*object, indent+1);
	return;
}

void PrintConditionExpressionPtr(std::unique_ptr<ConditionExpression> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("ConditionExpressionPtr : \n");
	AstPrint(*object, indent+1);
	return;
}

void PrintBlockExpessionPtr(std::unique_ptr<BlockExpession> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("BlockExpessionPtr : \n");
	AstPrint(*object, indent+1);
	return;
}

void PrintElseExpressionPtr(std::unique_ptr<ElseExpression> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("ElseExpressionPtr : \n");
	AstPrint(*object, indent+1);
	return;
}


/*
 *  vector printer
 *  std::vector<*>
 */
void PrintTypePtrVec(std::vector<TypePtr> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("TypePtrVec { \n");
	for (std::vector<TypePtr>::iterator it = object.begin();
			it != object.end(); ++it)
	{
		PrintTypePtr(*it, indent+1);
	}
	printf(indentStuff);
	printf("} \n");
}

void PrintStatementPtrVec(std::vector<StatementPtr> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("StatementPtrVec { \n");
	for (std::vector<StatementPtr>::iterator it = object.begin();
			it != object.end(); ++it)
	{
		PrintStatementPtr(*it, indent+1);
	}
	printf(indentStuff);
	printf("} \n");
}

void PrintExpressionPtrVec(std::vector<ExpressionPtr> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("ExpressionPtrVec { \n");
	for (std::vector<ExpressionPtr>::iterator it = object.begin();
			it != object.end(); ++it)
	{
		PrintExpressionPtr(*it, indent+1);
	}
	printf(indentStuff);
	printf("} \n");
}

void PrintParamPtrVec(std::vector<ParamPtr> object, int indent = 0) {
	std::string indentStuff = (indent, '\t');
	printf(indentStuff);
	printf("ParamPtrVec { \n");
	for (std::vector<ParamPtr>::iterator it = object.begin();
			it != object.end(); ++it)
	{
		PrintParamPtr(*it, indent+1);
	}
	printf(indentStuff);
	printf("} \n");
}





} // namespace internal
} // namespace dp
