#include "gtest/gtest.h"
#include "ast/ast.h"
#include "parsing/parsing.h"

TEST(testCase, ast){
    // dp::internal::Declaration decl(
    //     dp::internal::Types ts,
    //     dp::internal::Args args,
    //     dp::internal::Stmts stmts
    // );

    // dp::internal::Parser parser;
    
    // std::string code = "        \
    //     fun main() -> () {      \
    //         let a : i32 = 1;    \
    //         let b : i32 = 2;    \
    //         let r : i32 = a + b;\
    //     }                       ";
    
    // ASSERT_TRUE(dp::internal::test::ast_eq(decl, parser.parse(code)));
}

int main(int argc,char **argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
