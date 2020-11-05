#include "ast/type.h"
#include "utils/cast.h"
#include "gtest/gtest.h"

using namespace dp;
using namespace dp::internal;

TEST(testCase, Type_Cast) {
	TypePtr i32 = Type::I32();
	TypePtr i64 = Type::I64();
	TypePtr f32 = Type::F32();
	TypePtr f64 = Type::F64();

	ASSERT_TRUE(dyn_cast<PrimitiveType>(i32.get()) != nullptr);
	ASSERT_TRUE(dyn_cast<PrimitiveType>(i64.get()) != nullptr);
	ASSERT_TRUE(dyn_cast<PrimitiveType>(f32.get()) != nullptr);
	ASSERT_TRUE(dyn_cast<PrimitiveType>(f64.get()) != nullptr);
	ASSERT_TRUE(dyn_cast<FunctionType>(i32.get()) == nullptr);

	TypePtr fun = std::make_unique<FunctionType>();
	ASSERT_TRUE(dyn_cast<FunctionType>(fun.get()) != nullptr);
}

TEST(testCase, Type_IsSame) {
	TypePtr i32 = Type::I32();
	TypePtr ai32 = Type::I32();
	ASSERT_TRUE(Type::IsSame(i32.get(), ai32.get()));
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
