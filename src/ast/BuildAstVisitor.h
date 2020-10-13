/*
 * Antlr parse tree visitor, constructing AST
 *
 */

#pragma once

#include "antlr4-runtime.h"
#include "DLParserBaseVisitor.h"
#include "ast.h"

class ParseTreeException : public exception {
	const char* what() const throw() {
		return "Unknown node type";
	}
}

class UnknownOperatorException : public exception {
	const char* what() const throw() {
		return "Unknown operator";
	}
}

class UnknownSpecifierException : public exception {
	const char* what() const throw() {
		return "Unknown access specifier";
	}
}

class BuildAstVisitor : public DLParserBaseVisitor {
public:
	ASTNode visitExp(DLParser::ExpContext* ctx) override {
		if (ctx == nullptr) {
			return nullptr;
		}

		if (ctx.CONST() != nullptr) {
			new node = BinaryExpression(
					ctx.CONST().getText(),
					visitExpPost(ctx.expPost()).op(),
					visitExpPost(ctx.expPost()).right());

		} else if (ctx.IDENTIFIER() != nullptr) {
			new node = BinaryExpression(
					ctx.IDENTIFIER().getText(),
					visitExpPost(ctx.expPost()).op(),
					visitExpPost(ctx.expPost()).right());

		} else if (ctx.QUOTED_STRING() != nullptr) {
			new node = BinaryExpression(
					ctx.QUOTED_STRING().getText(),
					visitExpPost(ctx.expPost()).op(),
					visitExpPost(ctx.expPost()).right());

		} else if (ctx.unAryOp() != nullptr) {
			new node = UnaryExpression(
					ctx.unAryOp().getText(),
					true,
					visitExpPost(ctx.expPost()));

		} else if (ctx.newExp() != nullptr) {
			new node = visitExpPost(ctx.expPost());

		} else {
			throw new ParseTreeException();
		}
		return node;
	};

	ASTNode visitExpPost(DLParser::ExpPostContext* ctx) override {
		// TODO: sematic meaning?
		if (ctx.OPEN_SQUARE_SYMBOL() != nullptr) {
			if (ctx.expList() != nullptr) {

			} else if (ctx.exp() != nullptr) {

			} else {
			}

		} else if (ctx.AT_SIGN_SYMBOL() != nullptr) {

		} else if (ctx.OPEN_PAR_SYMBOL() != nullptr) {
			if (ctx.expList() != nullptr) {

			} else {
			}

		} else if (ctx.DOT_SYMBOL() != nullptr) {

		} else if (ctx.aryOp() != nullptr) {
			new node = UnaryExpression(
					ctx.unAryOp().getText(),
					true,
					visitExpPost(ctx.expPost()));
		} else {
			throw new ParseTreeException();
		}
		return node;
	};

	// abondaned if using op()
	// a.k.a. char* visitAryOp(), return operator characters
	ASTNode visitAryOp(DLParser::AryOpContext* ctx) override {
		if (ctx.PLUS_OPERATOR() != nullptr) {

		} else if (ctx.MINUS_OPERATOR() != nullptr) {

		} else if (ctx.MULT_OPERATOR() != nullptr) {

		} else if (ctx.DIV_OPERATOR() != nullptr) {

		} else if (ctx.MOD_OPERATOR() != nullptr) {

		} else if (ctx.ASSIGN_OPERATOR() != nullptr) {

		} else if (ctx.EQUAL_OPERATOR() != nullptr) {

		} else if (ctx.LOGICAL_AND_OPERATOR() != nullptr) {

		} else if (ctx.LOGICAL_OR_OPERATOR() != nullptr) {

		} else {
			throw new UnknownOperatorException();
		}
		return node;
	};

	// same as visitAryOp()
	ASTNode visitUnAryOp(DLParser::UnAryOpContext* ctx) override {
		if (ctx.BITWISE_AND_OPERATOR() != nullptr) {

		} else if (ctx.LOGICAL_NOT_OPERATOR() != nullptr) {

		} else if (ctx.BITWISE_NOT_OPERATOR() != nullptr) {

		} else {
			throw new UnknownOperatorException();
		}
		return node;
	};

	ASTNode visitNewExp(DLParser::NewExpContext* ctx) override {
		if (ctx.expList() != nullptr) {
			new node = VariableDeclaration(
					ctx.IDENTIFIER().getText(),
					visitvisitExpList(ctx.expList()));
		} else {
			new node = VariableDeclaration(
					ctx.IDENTIFIER().getText());
		}
		return node;
	};

	ASTNode visitExpList(DLParser::ExpListContext* ctx) override {
		// do something
		new node = BlockExpession(
				std::vector<node*> stmts = { visitExp(ctx.exp()) });

		if (ctx.COMMA_SYMBOL() != nullptr) { //recursively
			new enode = visitExpList(ctx.expList());
			node.stmts.insert(node.stmts.end(),
												enode.stmts.begin(), enode.stmts.end());
		} else {
			// end of list
		}
		return node;
	};

	ASTNode visitStatement(DLParser::StatementContext* ctx) override {
		if (ctx.IF_SYMBOL() != nullptr) {
			new node = IfStatement(
					visitExp(ctx.exp()),
					visitCompoundBlock(ctx.compoundBlock(0)),
					visitCompoundBlock(ctx.compoundBlock(1)));
		} else if (ctx.FOR_SYMBOL() != nullptr) {
			new node = ForStatement(
					visitCompoundBlock(ctx.compoundBlock(0)),
					visitExp(ctx.exp(0)),
					visitExp(ctx.exp(1)),
					visitCompoundBlock(ctx.compoundBlock(1)));

		} else if (ctx.jumpStatement() != nullptr) {
			new node = visitJumpStatement(ctx.jumpStatement());

		} else {
			throw new ParseTreeException();
		}
		return node;
	};

	ASTNode visitCompoundBlock(DLParser::CompoundBlockContext* ctx) override {
		if (ctx.blockList() != nullptr) { //if exists
			new node = BlockExpession(
					visitBlockList(ctx.blockList()).stmts);
		} else {
			new node = BlockExpession(
					nullptr);
		}
		return node;
	};

	ASTNode visitBlockList(DLParser::BlockListContext* ctx) override {
		if (ctx.statement() != nullptr) {
			new node = BlockExpession(
					std::vector<node*> stmts = { visitStatement(ctx.statement()) });

		} else if (ctx.exp() != nullptr) {
			new node = BlockExpession(
					std::vector<node*> stmts = { visitExp(ctx.exp()) });

		} else if (ctx.decl() != nullptr) {
			new node = BlockExpession(
					std::vector<node*> stmts = { visitDecl(ctx.decl()) });

		} else {
			throw new UnknownOperatorException();
		}

		if (ctx.blockList() != nullptr) { //recursively
			new enode = visitBlockList(ctx.blockList());
			node.stmts.insert(node.stmts.end(),
												enode.stmts.begin(), enode.stmts.end());
		} else {
			// end of list
		}
		return node;
	};

	ASTNode visitJumpStatement(DLParser::JumpStatementContext* ctx) override {
		if (ctx.BREAK_SYMBOL() != nullptr) {
			new node = BreakStatement();

		} else if (ctx.RETURN_SYMBOL() != nullptr) {
			if (ctx.exp() != nullptr) {
				new node = ReturnStatement(
						visitExp(ctx.exp()));
			} else {
				new node = ReturnStatement(
						nullptr);
			}
		} else {
			throw new ParseTreeException();
		}
		return node;
	};

	// TODO: type

	// type and typeTail?
	ASTNode visitType(DLParser::TypeContext* ctx) override {
		if (ctx.IDENTIFIER() != nullptr) {

		} else if (ctx.refType() != nullptr) {

		} else {
			throw new ParseTreeException();
		}
		return node;
	};

	ASTNode visitTypeTail(DLParser::TypeTailContext* ctx) override {
		if (ctx.COMMA_SYMBOL() != nullptr) {

		} else if (ctx.JSON_SEPARATOR_SYMBOL() != nullptr) {

		} else {
			throw new ParseTreeException();
		}
		return node;
	};

	ASTNode visitFunctionType(DLParser::FunctionTypeContext* ctx) override {
		// terminal node, check JSON and create node
		new node = FunctionType(
				visitType(ctx.type(0)),
				visitType(ctx.type(1)));

		return node;
	};

	ASTNode visitRefType(DLParser::RefTypeContext* ctx) override {
		if (ctx.MUT_SYMBOL() != nullptr) {

		} else {
		}
		return node;
	};

	// decl

	ASTNode visitDecl(DLParser::DeclContext* ctx) override {
		if (ctx.functionDecl() != nullptr) {
			new node = FunctionDeclaration(
					visitSignature(ctx.signature()).IDENTIFIER().getText(),
					visitSignature(ctx.signature()).type(),
					visitFunctionDef(ctx.functionDef()).compoundBlock());

		} else if (ctx.varDecl() != nullptr) {
			new node = VariableDeclaration(
					visitDecl(ctx.decl).IDENTIFIER().getText(),
					visitDecl(ctx.decl).type(),
					visitExp(visitDecl(ctx.decl).exp()))
		} else if (ctx.classDecl() != nullptr) {

		} else if (ctx.interfaceDecl() != nullptr) {

		} else {
			throw new ParseTreeException();
		}
		return node;
	};

	ASTNode visitFunctionDecl(DLParser::FunctionDeclContext* ctx) override {
		if (ctx.functionDef() != nullptr) {
			new node = FunctionDeclaration(
					visitCompoundBlock(ctx.compoundBlock));
		} else {
			new node = FunctionDeclaration(
					nullptr);
		}
		return node;
	};

	// TODO: waiting for function definition grammar
	ASTNode visitSignature(DLParser::SignatureContext* ctx) override {
		// ter
		return node;
	};

	// param list in signature?
	ASTNode visitFunctionDef(DLParser::FunctionDefContext* ctx) override {
		if (ctx.paramList() != nullptr) {

		} else {
		}
		return node;
	};

	ASTNode visitParamList(DLParser::ParamListContext* ctx) override {
		// do something

		if (ctx.COMMA_SYMBOL() != nullptr) { //recursively

		} else {
		}
		return node;
	};

	ASTNode visitVarDecl(DLParser::VarDeclContext* ctx) override {
		if (ctx.LET_SYMBOL() != nullptr) {

			if (ctx.EQUAL_OPERATOR() != nullptr) { //with init

			} else {
			}
		} else if (ctx.LETMUT_SYMBOL() != nullptr) {

		} else {
			throw new ParseTreeException();
		}

		return node;
	};

	ASTNode visitClassDecl(DLParser::ClassDeclContext* ctx) override {

		return node;
	};

	ASTNode visitClassHead(DLParser::ClassHeadContext* ctx) override {
		if (ctx.EXTENDS_SYMBOL() != nullptr) {

		} else {
		}

		if (ctx.IMPL_SYMBOL() != nullptr) {

		} else {
		}

		return node;
	};

	ASTNode visitClassBody(DLParser::ClassBodyContext* ctx) override {
		if (ctx.accessSpecifier() != nullptr) {

		} else if (ctx.constructor() != nullptr) {

		} else {
			throw new ParseTreeException();
		}

		if (ctx.classBody() != nullptr) { //recursively

		} else {
		}

		return node;
	};

	ASTNode visitConstructor(DLParser::ConstructorContext* ctx) override {

		if (ctx.paramList() != nullptr) {

		} else {
		}
		return node;
	};

	ASTNode visitAccessSpecifier(DLParser::AccessSpecifierContext* ctx) override {
		if (ctx.PRIVATE_SYMBOL() != nullptr) {

		} else if (ctx.PUBLIC_SYMBOL() != nullptr) {

		} else {
			throw new UnknownSpecifierException();
		}
		return node;
	};

	ASTNode visitInterfaceList(DLParser::InterfaceListContext* ctx) override {
		// INTERFACE_SYMBOL

		if (ctx.COMMA_SYMBOL() != nullptr) { //recursively

		} else {
		}

		return node;
	};

	ASTNode visitInterfaceDecl(DLParser::InterfaceDeclContext* ctx) override {
		// ter
		return node;
	};

	ASTNode visitInterfaceHead(DLParser::InterfaceHeadContext* ctx) override {

		if (ctx.EXTENDS_SYMBOL() != nullptr) {

		} else {
		}
		return node;
	};

	ASTNode visitInterfaceBody(DLParser::InterfaceBodyContext* ctx) override {
		// decl

		if (ctx.interfaceBody() != nullptr) { //recursively

		} else {
		}
		return node;
	};

	ASTNode visitProgram(DLParser::ProgramContext* ctx) override {
		// decl
		new node = BlockExpession(
				std::vector<node*> stmts = { visitExp(ctx.exp()) });

		if (ctx.program() != nullptr) { //recursively
			new enode = visitProgram(ctx.program());
			node.stmts.insert(node.stmts.end(),
												enode.stmts.begin(), enode.stmts.end());
		} else {
			// end of program
		}
		return node;
	};
}