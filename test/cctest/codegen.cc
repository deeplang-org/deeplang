#include "gtest/gtest.h"
#include "ast/ast.h"
#include "parsing/parsing.h"

TEST(testCase, codegen){
		dp::internal::Literal e1(1, "1");
		dp::internal::Literal e2(2, "2");
		dp::internal::BinaryExpression addexp(dp::internal::BinaryOperator::Plus,
			dynamic_cast<dp::internal::ASTNode*>(&e1),
			dynamic_cast<dp::internal::ASTNode*>(&e2)
		);

		
		dp::internal::CodeGen gen;

		std::string source = "(i32.add        \
													 (get_local $1) \
													 (get_local $2)	\
													)";
    
    ASSERT_STREQ(gen.genarate(addexp), source);
}
int main(int argc,char **argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
