#pragma once

#include "ast/ast.h"
#include "common.h"

namespace dp {
namespace internal {

class CodeGen {
public:
	CodeGen();

	std::string generateWat(BinaryExpression& bexp);
	std::string generateWasm(BinaryExpression& bexp);
};

} // namespace internal
} // namespace dp
