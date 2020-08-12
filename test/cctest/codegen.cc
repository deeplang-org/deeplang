#include "codegen/codegen.h"

#include "ast/ast.h"

#include "gtest/gtest.h"

using namespace dp;
using namespace dp::internal;

TEST(testCase, codegen) {
	auto mod = std::make_unique<Module>();

	auto mainFunc = std::make_unique<FunctionDeclaration>("main");

	auto sig            = std::make_unique<FunctionType>();
	mainFunc->signature = std::move(sig);

	auto mainFuncBody = std::make_unique<BlockExpession>();

	auto var1Decl     = std::make_unique<VariableDeclaration>("var");
	var1Decl->vartype = std::make_unique<VariableType>(PrimitiveVariableTypes::I32);

	auto addExp   = std::make_unique<BinaryExpression>(BinaryOperator::Plus);
	addExp->left  = std::make_unique<LiteralExpression>(1);
	addExp->right = std::make_unique<LiteralExpression>(2);

	var1Decl->init = std::move(addExp);

	mainFuncBody->stmts.push_back(std::move(var1Decl));
	mainFunc->body = std::move(mainFuncBody);
	mod->stmts.push_back(std::move(mainFunc));

	CodeGen::generateWasm(mod.get());

	//ASSERT_STREQ(gen.genarate(addexp), source);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
