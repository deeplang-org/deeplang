#include <gtest/gtest.h>
#include "src/ast/ast.h"
#include "src/parsing/parsing.h"

TEST(testCase, codegen){
		dp::internal::Literal e1(1, "1");
		dp::internal::Literal e2(2, "2");
		dp::internal::BinaryExpression addexp("+", std::make_unique(e1), std::make_unique(e2));

		
		dp::inernal::CodeGen gen;

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
