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

}

antlrcpp::Any Parser::visitExpressionStatement(DLParser::ExpressionStatementContext *context) {

}


antlrcpp::Any Parser::visitBlockExpression(DLParser::BlockExpressionContext *context) {
}

antlrcpp::Any Parser::visitUnblockExpression(DLParser::UnblockExpressionContext *context) {


}

antlrcpp::Any Parser::visitUnblockExpressionPost(DLParser::UnblockExpressionPostContext *context) {

}

antlrcpp::Any Parser::visitTupleType(DLParser::TupleTypeContext *context) {
}

antlrcpp::Any Parser::visitType(DLParser::TypeContext *context) {
}

antlrcpp::Any Parser::visitVariableDecl(DLParser::VariableDeclContext *context) {

}

antlrcpp::Any Parser::visitFunctionDecl(DLParser::FunctionDeclContext *context) {

}

antlrcpp::Any Parser::visitDecl(DLParser::DeclContext *context) {
}

antlrcpp::Any Parser::visitStatement(DLParser::StatementContext *context) {
}

antlrcpp::Any Parser::visitStatements(DLParser::StatementsContext *context) {
}

antlrcpp::Any Parser::visitModule(DLParser::ModuleContext *context) {
    Module* m = new Module();
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


