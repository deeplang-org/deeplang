#include "parsing.h"
#include "ast/ast.h"
#include "antlr4-runtime.h"
#include "DLLexer.h"
#include "DLParser.h"
#include "DLParserVisitor.h"
#include "utils/error.h"
#include <cmath>
#include <typeinfo>



namespace dp {
namespace internal {
    

antlrcpp::Any Parser::visitAryOp(DLParser::AryOpContext *context) {
    UNREACHABLE("op");
}

antlrcpp::Any Parser::visitExpressionStatement(DLParser::ExpressionStatementContext *context) {
    if (context->blockExpression()) {
        return visit(context->blockExpression());
    } else if (context->unblockExpression()) {
        ExpressionStatement* stmt = new ExpressionStatement();
        stmt->expr = std::unique_ptr<Expression>(
            static_cast<Expression*>(visit(context->unblockExpression())));
        return stmt;
    } else {
        UNREACHABLE("visitExpressionStatement");
    }
}


antlrcpp::Any Parser::visitBlockExpression(DLParser::BlockExpressionContext *context) {
    ExpressionStatement* be = new ExpressionStatement();
    BlockExpession* e = new BlockExpession();


    std::vector<Statement*>* stmts = visit(context->statements());
    for (auto stm : *stmts) {
        e->stmts.push_back(std::make_unique<Statement>(*stm));
    }
    delete stmts;
    be->expr = std::unique_ptr<Expression>(static_cast<Expression*>(e));
    return be;
}

antlrcpp::Any Parser::visitUnblockExpression(DLParser::UnblockExpressionContext *context) {
    if (context->CONST()) {
        int v = stoi(context->CONST()->getText());
        return static_cast<Expression*>(new LiteralExpression(v));
    } else if (context->IDENTIFIER()) {
        Expression* e = static_cast<Expression*>(new PathExpression(context->IDENTIFIER()->getText()));
        return e;
    } else {
        // std::vector<UnblockExpressionContext*> rest = context->unblockExpression();
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
            } else {
                UNREACHABLE("unsupport operator");
            }
            BinaryExpression* be = new BinaryExpression(op);
            Expression* left = static_cast<Expression*>(visit(context->unblockExpression(0)));
            Expression* right = static_cast<Expression*>(visit(context->unblockExpression(1)));
            be->left = std::unique_ptr<Expression>(left);
            be->right = std::unique_ptr<Expression>(right);
            
            return static_cast<Expression*>(be);
        } else {
            UNREACHABLE("visitUnblockExpression");
        }

    }
}


antlrcpp::Any Parser::visitTupleType(DLParser::TupleTypeContext *context) {
    UNREACHABLE("visitTupleType");
}

antlrcpp::Any Parser::visitType(DLParser::TypeContext *context) {
    return new FunctionType();
}

antlrcpp::Any Parser::visitVariableDecl(DLParser::VariableDeclContext *context) {
    VariableDeclaration* v = new VariableDeclaration(context->IDENTIFIER()->getText());
    ExpressionStatement* estmt = static_cast<ExpressionStatement*>(visit(context->expressionStatement()));
    v->init = std::move(estmt->expr);
    delete estmt;
    return static_cast<Statement*>(v);
}

antlrcpp::Any Parser::visitFunctionDecl(DLParser::FunctionDeclContext *context) {
    FunctionDeclaration* decl = new FunctionDeclaration(context->IDENTIFIER()->getText());
    decl->signature = std::unique_ptr<FunctionType>(
        static_cast<FunctionType*>(visit(context->type())));
    decl->body = std::unique_ptr<ExpressionStatement>(
        static_cast<ExpressionStatement*>(visit(context->blockExpression())));
    decl->isPublic = true;
    return static_cast<Statement*>(decl);
}

antlrcpp::Any Parser::visitDecl(DLParser::DeclContext *context) {
    if (context->functionDecl()) {
        return static_cast<Statement*>(visit(context->functionDecl()));
    } else if (context->variableDecl()) {
        return static_cast<Statement*>(visit(context->variableDecl()));
    } else {
        UNREACHABLE("visitDecl");
    }
}

antlrcpp::Any Parser::visitStatement(DLParser::StatementContext *context) {
    if (context->decl()) {
        return static_cast<Statement*>(visit(context->decl()));
    } else if (context->expressionStatement()) {
        return static_cast<Statement*>(visit(context->expressionStatement()));
    } else {
        UNREACHABLE("visitStatement");
    }
}

antlrcpp::Any Parser::visitStatements(DLParser::StatementsContext *context) {
    std::vector<Statement*>* stmts = new std::vector<Statement*>();
    Statement* stm = static_cast<Statement*>(visit(context->statement()));
    stmts->push_back(stm);
    if (context->statements()) {
        std::vector<Statement*>* tails = visit(context->statements());
        stmts->insert(stmts->end(), tails->begin(), tails->end());
    }
    return static_cast<std::vector<Statement*>*>(stmts);
}

antlrcpp::Any Parser::visitModule(DLParser::ModuleContext *context) {
    Module* m = new Module("anonymous");
    m->id = Identifier("anonymous");
    std::vector<Statement*>* stmts = visit(context->statements()).as<std::vector<Statement*>*>();
    for (auto stm : *stmts) {
        m->stmts.push_back(std::make_unique<Statement>(*stm));
    }
    delete stmts;
    return m;
}




Module* Parser::parseModule(antlr4::ANTLRInputStream sourceStream) {
    antlr4::ANTLRInputStream input = sourceStream;
    DLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }

    DLParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.module();


    std::cout << prettyPrint(tree->toStringTree(&parser)) << std::endl;
    Module* module = visit(tree);

    return module;
}

std::string Parser::prettyPrint (std::string treeString) {
    int indentSize = 3;
    int currIndex = 0;
    std::string outString = std::string(1,treeString[0]);
    std::string indent = "";
    for (int i = 1; i < treeString.size(); i++) {
        if(treeString[i] == '(' && treeString[i+1] != ' '){
           currIndex += indentSize;
           std::string indentSpace = "";
           for(int i = 0; i < currIndex; i++) {
               indentSpace += " ";
           }
           outString += '\n' + indentSpace + '(';
        }
        else if(treeString[i] == ')'){
          outString += ')';
          if(currIndex > indentSize)
            currIndex -= indentSize;
        }
        else {
          outString += treeString[i];
        }
    }
    return outString;
}

} // internal namespace
} // dp namespace


