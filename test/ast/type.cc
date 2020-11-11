#include "ast/type.h"
#include "utils/cast.h"
#include "gtest/gtest.h"

using namespace dp;
using namespace dp::internal;

TEST(testCase, Type_Cast) {
	Type* i32 = Type::I32();
	Type* i64 = Type::I64();
	Type* f32 = Type::F32();
	Type* f64 = Type::F64();

	ASSERT_TRUE(dyn_cast<PrimitiveType>(i32) != nullptr);
	ASSERT_TRUE(dyn_cast<PrimitiveType>(i64) != nullptr);
	ASSERT_TRUE(dyn_cast<PrimitiveType>(f32) != nullptr);
	ASSERT_TRUE(dyn_cast<PrimitiveType>(f64) != nullptr);
	ASSERT_TRUE(dyn_cast<FunctionType>(i32) == nullptr);

	TypeVector params;
	Type* fun = FunctionType::MakeType(params, i32);
	ASSERT_TRUE(dyn_cast<FunctionType>(fun) != nullptr);
}

TEST(testCase, Type_IsSame) {
	Type* i32 = Type::I32();
	Type* ai32 = Type::I32();
	ASSERT_TRUE(Type::IsSame(i32, ai32));
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
