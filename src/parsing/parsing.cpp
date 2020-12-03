#include "parsing.h"
#include "ast/ast.h"
#include "antlr4-runtime.h"
#include "parsing/gen/DLLexer.h"
#include "parsing/gen/DLParser.h"
#include "parsing/gen/DLParserVisitor.h"
#include "parsing/parseError.h"
#include "utils/error.h"
#include "utils/cast.h"
#include <cmath>
#include <typeinfo>

namespace dp {
namespace internal {

static Location makeLocation(antlr4::ParserRuleContext* ctx) {
	auto start = ctx->getStart();
	auto end   = ctx->getStop();
	return Location{
		Range{
				Position{ start->getLine(), start->getCharPositionInLine() },
				Position{ end->getLine(), end->getCharPositionInLine() } }
	};
}

static Location makeLocation(antlr4::Token* tok) {
	return Location{
		Range{
				Position{ tok->getLine(), tok->getCharPositionInLine() },
				Position{ tok->getLine(), tok->getCharPositionInLine() } }
	};
}

antlrcpp::Any Parser::visitAryOp(DLParser::AryOpContext* context) {
	UNREACHABLE("op");
}

antlrcpp::Any Parser::visitSemiexpressionStmt(DLParser::SemiexpressionStmtContext* context) {
	if (context->blockExpression()) {
        SemiExpressionStatement* semiStmt = new SemiExpressionStatement(makeLocation(context));
        semiStmt->expr = std::move((static_cast<ExpressionStatement*>(visit(context->blockExpression())))->expr);
		return semiStmt;
	} else if (context->unblockExpression()) {
		SemiExpressionStatement* stmt = new SemiExpressionStatement(makeLocation(context));
		stmt->expr                = std::unique_ptr<Expression>(static_cast<Expression*>(visit(context->unblockExpression())));
		return stmt;
	} else if (context->ifExpression()) {
		SemiExpressionStatement* ifexpr = new SemiExpressionStatement(makeLocation(context));
		ifexpr->expr                      = std::move((static_cast<ExpressionStatement*>(visit(context->ifExpression())))->expr); 
		return ifexpr;
	} else {
		UNREACHABLE("visitSemiexpressionStatement");
	}
}

antlrcpp::Any Parser::visitExpressionStmt(DLParser::ExpressionStmtContext* context) {
	if (context->blockExpression()) {
		return visit(context->blockExpression());
	} else if (context->unblockExpression()) {
		ExpressionStatement* stmt = new ExpressionStatement(makeLocation(context));
		stmt->expr                = std::unique_ptr<Expression>(static_cast<Expression*>(visit(context->unblockExpression())));
		return stmt;
	} else if (context->ifExpression()) {
		ExpressionStatement* ifexpr = new ExpressionStatement(makeLocation(context));
		ifexpr                      = static_cast<ExpressionStatement*>(visit(context->ifExpression()));
		return ifexpr;
	} else {
		UNREACHABLE("visitExpressionStatement");
	}
}

antlrcpp::Any Parser::visitExpressionList(DLParser::ExpressionListContext* context) {
	std::vector<Expression*>*                     exps        = new std::vector<Expression*>();
	std::vector<DLParser::ExpressionStmtContext*> expStmtCtxs = context->expressionStmt();
	for (auto expStmtCtx : expStmtCtxs) {
		ExpressionStatement* es = visit(expStmtCtx);
		Expression*          e  = es->expr.get();
		es->expr.release();
		exps->push_back(e);
		delete es;
	}
	return exps;
}

antlrcpp::Any Parser::visitBlockExpression(DLParser::BlockExpressionContext* context) {
	ExpressionStatement* be = new ExpressionStatement(makeLocation(context));
	BlockExpression*     e  = new BlockExpression(makeLocation(context));

	if (context->statements()) {
		std::vector<Statement*>* stmts = visit(context->statements());
		for (auto stm : *stmts) {
			e->stmts.emplace_back(stm);
		}
		delete stmts;
	}
	be->expr = std::unique_ptr<Expression>(static_cast<Expression*>(e));
	return be;
}

antlrcpp::Any Parser::visitUnblockExpression(DLParser::UnblockExpressionContext* context) {
	if (context->CONST()) {
		int v = stoi(context->CONST()->getText());
		return static_cast<Expression*>(
				new LiteralExpression(v, makeLocation(context->CONST()->getSymbol())));
	} else if (context->IDENTIFIER()) {
		auto        id = context->IDENTIFIER();
		Expression* e  = static_cast<Expression*>(
        new PathExpression(id->getText(), makeLocation(id->getSymbol())));
		return e;
	} else if (context->expressionList()) {
		CallExpression* ce           = new CallExpression(makeLocation(context));
		Expression*     method       = static_cast<Expression*>(visit(context->unblockExpression(0)));
		ce->method                   = std::unique_ptr<Expression>(method);
		std::vector<Expression*>* ev = visit(context->expressionList());
		for (auto e : *ev) {
			std::unique_ptr<Expression> p(e);
			ce->params.emplace_back(std::move(p));
		}
		delete ev;
		return static_cast<Expression*>(ce);
	} else if (context->QUOTED_STRING()) {
		std::string s = context->QUOTED_STRING()->getText();
		s.pop_back();
		s.erase(s.begin());
		Expression* e = static_cast<Expression*>(
				new LiteralExpression(s, makeLocation(context->QUOTED_STRING()->getSymbol())));
		return e;
	} else {
		if (context->unblockExpression(0) && context->unblockExpression(1)) {
			BinaryOperator op;
			if (context->PLUS_OPERATOR()) {
				op = BinaryOperator::Plus;
			} else if (context->MINUS_OPERATOR()) {
				op = BinaryOperator::Minus;
			} else if (context->MULT_OPERATOR()) {
				op = BinaryOperator::Mult;
			} else if (context->DIV_OPERATOR()) {
				op = BinaryOperator::Div;
			} else if (context->GREATER_THAN_OPERATOR()) {
				op = BinaryOperator::GT;
			} else if (context->GREATER_OR_EQUAL_OPERATOR()) {
				op = BinaryOperator::GE;
			} else if (context->LESS_THAN_OPERATOR()) {
				op = BinaryOperator::LT;
			} else if (context->LESS_OR_EQUAL_OPERATOR()) {
				op = BinaryOperator::LE;
			} else if (context->EQUAL_OPERATOR()) {
				op = BinaryOperator::Eq;
			} else if (context->NOT_EQUAL_OPERATOR()) {
				op = BinaryOperator::Neq;
			} else {
				UNREACHABLE("unsupport operator");
			}
			BinaryExpression* be    = new BinaryExpression(op, makeLocation(context));
			Expression*       left  = static_cast<Expression*>(visit(context->unblockExpression(0)));
			Expression*       right = static_cast<Expression*>(visit(context->unblockExpression(1)));
			be->left                = std::unique_ptr<Expression>(left);
			be->right               = std::unique_ptr<Expression>(right);

			return static_cast<Expression*>(be);
		} else {
			UNREACHABLE("visitUnblockExpression");
		}
	}
}

antlrcpp::Any Parser::visitIfExpression(DLParser::IfExpressionContext* context) {
	ExpressionStatement* es     = new ExpressionStatement(makeLocation(context));
	IfExpression*        ifexpr = new IfExpression(makeLocation(context));
	ifexpr->condition           = std::unique_ptr<Expression>(static_cast<Expression*>(visit(context->unblockExpression())));
	ifexpr->then_branch         = std::unique_ptr<BlockExpression>(static_cast<BlockExpression*>((static_cast<ExpressionStatement*>(visit(context->blockExpression()))->expr).get()));
	if (context->elseExpression()) {
		ifexpr->else_branch = std::unique_ptr<Expression>(static_cast<Expression*>((static_cast<ExpressionStatement*>(visit(context->elseExpression()))->expr).get()));
	}
	es->expr = std::unique_ptr<IfExpression>(ifexpr);
	return es;
}

antlrcpp::Any Parser::visitElseExpression(DLParser::ElseExpressionContext* context) {
	ExpressionStatement* ifexpr = new ExpressionStatement(makeLocation(context));
	if (context->ifExpression()) { // else if
		ifexpr = static_cast<ExpressionStatement*>(visit(context->ifExpression()));
	} else { //  else
		BlockExpression* be = new BlockExpression(makeLocation(context));
		be                  = static_cast<BlockExpression*>((static_cast<ExpressionStatement*>(visit(context->blockExpression()))->expr).get());
		ifexpr->expr        = std::unique_ptr<Expression>(static_cast<Expression*>(be));
	}
	return ifexpr;
}

antlrcpp::Any Parser::visitTupleType(DLParser::TupleTypeContext* context) {
	UNREACHABLE("visitTupleType");
}

antlrcpp::Any Parser::visitType(DLParser::TypeContext* context) {
	if (context->IDENTIFIER()) {
		std::string typName = context->IDENTIFIER()->getText();
		return PrimitiveType::MakeType(typName);
	} else {
		// TODO: customize type and tuple
		return Type::Unit();
	}
}

antlrcpp::Any Parser::visitParam(DLParser::ParamContext* context) {
	Identifier id(context->IDENTIFIER()->getText());
	Type*      t = visit(context->type());
	Param*     p = new Param(id);
	p->typ       = t;
	return p;
}

antlrcpp::Any Parser::visitParamList(DLParser::ParamListContext* context) {
	ParamVector*                         params    = new ParamVector();
	std::vector<DLParser::ParamContext*> paramsCtx = context->param();
	for (auto paramCtx : paramsCtx) {
		Param* p = visit(paramCtx);
		params->push_back(*p);
	}
	return params;
}

antlrcpp::Any Parser::visitLocalStmt(DLParser::LocalStmtContext* context) {
	LocalStatement* v = new LocalStatement(
			context->IDENTIFIER()->getText(), makeLocation(context));
	PrimitiveType* t = visit(context->type());
	v->typ           = static_cast<PrimitiveType*>(t);
	if (context->blockExpression()) {
		ExpressionStatement* estmt = static_cast<ExpressionStatement*>(visit(context->blockExpression()));
		v->init                    = std::move(estmt->expr);
		delete estmt;
	} else if (context->unblockExpression()) {
		v->init = std::unique_ptr<Expression>(static_cast<Expression*>(visit(context->unblockExpression())));
	} else if (context->ifExpression()) {
		ExpressionStatement* estmt = static_cast<ExpressionStatement*>(visit(context->ifExpression()));
		v->init                    = std::move(estmt->expr);
		delete estmt;
	}
	return static_cast<Statement*>(v);
}

antlrcpp::Any Parser::visitFunctionStmt(DLParser::FunctionStmtContext* context) {
	FunctionStatement* decl = new FunctionStatement(
			context->IDENTIFIER()->getText(), makeLocation(context));
	decl->body          = std::unique_ptr<BlockExpression>(static_cast<BlockExpression*>((static_cast<ExpressionStatement*>(visit(context->blockExpression()))->expr).get()));
	ParamVector* params = visit(context->paramList());

	Type*          t       = visit(context->type());
	PrimitiveType* retType = static_cast<PrimitiveType*>(t);
	//	ft->Result             = std::unique_ptr<Type>(retType);
	TypeVector paramVec;
	for (auto& param : *params) {
		paramVec.emplace_back(param.typ);
	}
	auto ft = FunctionType::MakeType(paramVec, retType);

	decl->typ = ft;
	decl->params.swap(*params);
	delete params;

	decl->isPublic = true;
	return static_cast<Statement*>(decl);
}

antlrcpp::Any Parser::visitStatement(DLParser::StatementContext* context) {
	if (context->localStmt()) {
		return static_cast<Statement*>(visit(context->localStmt()));
	} else if (context->functionStmt()) {
		return static_cast<Statement*>(visit(context->functionStmt()));
	} else if (context->expressionStmt()) {
		auto es = static_cast<ExpressionStatement*>(visit(context->expressionStmt()));
		return static_cast<Statement*>(es);
	} else if (context->semiexpressionStmt()) {
		auto ses = static_cast<SemiExpressionStatement*>(visit(context->semiexpressionStmt()));
		return static_cast<Statement*>(ses);
	} else {
		UNREACHABLE("visitStatement");
	}
}

antlrcpp::Any Parser::visitStatements(DLParser::StatementsContext* context) {
	std::vector<Statement*>* stmts = new std::vector<Statement*>();
	Statement*               stm   = static_cast<Statement*>(visit(context->statement()));
	stmts->push_back(stm);
	if (context->statements()) {
		std::vector<Statement*>* tails = visit(context->statements());
		stmts->insert(stmts->end(), tails->begin(), tails->end());
	}
	return static_cast<std::vector<Statement*>*>(stmts);
}

antlrcpp::Any Parser::visitModule(DLParser::ModuleContext* context) {
	auto    filename               = context->getStart()->getTokenSource()->getSourceName();
	Module* m                      = new Module(filename, makeLocation(context));
	m->id                          = Identifier(filename);
	std::vector<Statement*>* stmts = visit(context->statements()).as<std::vector<Statement*>*>();
	for (auto stm : *stmts) {
		m->stmts.emplace_back(stm);
	}
	delete stmts;
	return m;
}

Module* Parser::parseModule(antlr4::ANTLRInputStream sourceStream) {
	antlr4::ANTLRInputStream  input = sourceStream;
	DLLexer                   lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);

	tokens.fill();
	for (auto token : tokens.getTokens()) {
		std::cout << token->toString() << std::endl;
	}

	DLParser parser(&tokens);
	parser.addErrorListener(new ParseErrorHanler());
	antlr4::tree::ParseTree* tree = parser.module();

	std::cout << prettyPrint(tree->toStringTree(&parser)) << std::endl;
	Module* module = visit(tree);
	return module;
}

std::string Parser::prettyPrint(std::string treeString) {
	int         indentSize = 3;
	int         currIndex  = 0;
	std::string outString  = std::string(1, treeString[0]);
	std::string indent     = "";
	for (int i = 1; i < treeString.size(); i++) {
		if (treeString[i] == '(' && treeString[i + 1] != ' ') {
			currIndex += indentSize;
			std::string indentSpace = "";
			for (int i = 0; i < currIndex; i++) {
				indentSpace += " ";
			}
			outString += '\n' + indentSpace + '(';
		} else if (treeString[i] == ')') {
			outString += ')';
			if (currIndex > indentSize)
				currIndex -= indentSize;
		} else {
			outString += treeString[i];
		}
	}
	return outString;
}

} // namespace internal
} // namespace dp
