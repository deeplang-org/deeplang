#include "parsing.h"
#include "ast/ast.h"
#include "antlr4-runtime.h"
#include "DLLexer.h"
#include "DLParser.h"
#include "DLParserVisitor.h"
#include <cmath>



namespace dp {
namespace internal {
    

antlrcpp::Any Parser::visitAryOp(DLParser::AryOpContext *context) {
    if (context->PLUS_OPERATOR()) {
        return BinaryOperator::Plus;
    }
    if (context->MINUS_OPERATOR()) {
        return BinaryOperator::Minus;
    }
    if (context->MULT_OPERATOR()) {
        return BinaryOperator::Mult;
    }
    if (context->DIV_OPERATOR()) {
        return BinaryOperator::Div;
    }
}

antlrcpp::Any Parser::visitExpressionStatement(DLParser::ExpressionStatementContext *context) {
    if (context->blockExpression()) {
        return visit(context->blockExpression());
    }
    if (context->unblockExpression()) {
        return visit(context->unblockExpression());
    }
}


antlrcpp::Any Parser::visitBlockExpression(DLParser::BlockExpressionContext *context) {
    return visit(context->statements());
}

antlrcpp::Any Parser::visitUnblockExpression(DLParser::UnblockExpressionContext *context) {
    Expression* postExp = visit(context->unblockExpressionPost());
    switch (postExp->kind) {
    case AstKind::LiteralExpression:
        break;
    case AstKind::PathExpression:
        break;
    case AstKind::BinaryExpression: {
        BinaryExpression* be = static_cast<BinaryExpression*>(postExp);
        if (context->CONST()) {
            int value = stoi(context->CONST()->getText());
            LiteralExpression* ple = new LiteralExpression(value);
            std::unique_ptr<LiteralExpression> le(ple);
            be->left = std::move(le);
        }
        if (context->IDENTIFIER()) {
            PathExpression* ppe = new PathExpression(context->IDENTIFIER()->getText());
            std::unique_ptr<PathExpression> pe(ppe);
            be->left = std::move(pe);
        }
        return be;

    }
    case AstKind::BlockExpression:
    default:
        return nullptr;
    }

}

antlrcpp::Any Parser::visitUnblockExpressionPost(DLParser::UnblockExpressionPostContext *context) {
    BinaryOperator op = visit(context->aryOp());
    BinaryExpression* ppost = visit(context->unblockExpressionPost());
    Expression* pe = visit(context->unblockExpression());
    if (ppost) {
        std::unique_ptr<Expression> e(pe);
        ppost->left = std::move(e);
        BinaryExpression* resExp = new BinaryExpression(op);
        std::unique_ptr<Expression> post(ppost);
        resExp->right = std::move(post);
        return resExp;
    } else {
        return pe;
    }
}

antlrcpp::Any Parser::visitTupleType(DLParser::TupleTypeContext *context) {
    return new VariableType(PrimitiveVariableTypes::Unit);
}

antlrcpp::Any Parser::visitType(DLParser::TypeContext *context) {
    return new VariableType(PrimitiveVariableTypes::Unit);
}

antlrcpp::Any Parser::visitVariableDecl(DLParser::VariableDeclContext *context) {
    
    VariableDeclaration* vd = new VariableDeclaration(context->IDENTIFIER()->getText());
    Type* pType = visit(context->type());
    Expression* pExp = visit(context->expressionStatement());

    std::unique_ptr<Type> t(pType);
    std::unique_ptr<Expression> e(pExp);
    vd->vartype = std::move(t);
    vd->init = std::move(e);
    return vd;
}

antlrcpp::Any Parser::visitFunctionDecl(DLParser::FunctionDeclContext *context) {
    FunctionDeclaration* f = new FunctionDeclaration(context->IDENTIFIER()->getText());
    FunctionType* pType = visit(context->type());
    BlockExpession* pBody = visit(context->blockExpression());
    std::unique_ptr<FunctionType> t(pType);
    std::unique_ptr<BlockExpession> body(pBody);
    f->signature = std::move(t);
    f->body = std::move(body);
    return f;
}

antlrcpp::Any Parser::visitDecl(DLParser::DeclContext *context) {
    if (context->functionDecl()) {
        return visit(context->functionDecl());
    }
    if (context->variableDecl()) {
        return visit(context->variableDecl());
    }
}

antlrcpp::Any Parser::visitStatement(DLParser::StatementContext *context) {
    if (context->decl()) {
        return visit(context->decl());
    }
    if (context->expressionStatement()) {
        return visit(context->expressionStatement());
    }
}

antlrcpp::Any Parser::visitStatements(DLParser::StatementsContext *context) {
    std::vector<Declaration*> vec;
    Declaration* decl = visit(context->statement());
    std::vector<Declaration*> rest = visit(context->statements());
    rest.insert(rest.begin(), decl);
    return vec;
}

antlrcpp::Any Parser::visitModule(DLParser::ModuleContext *context) {
    Module* m = new Module();
    std::vector<Declaration*> ds = visit(context->statements());
    for (auto d:ds) {
        std::unique_ptr<Declaration> p(d);
        m->stmts.push_back(std::move(p));
    }
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
    visit(tree);

    return nullptr;
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


