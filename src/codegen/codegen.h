#pragma once

#include "common.h"
#include "ast/ast.h"

namespace dp {
namespace internal {

class CodeGen {
public:
	//static std::string generateWat(Module& bexp);
	static std::string generateWasm(Module* bexp);
};

} // namespace internal
} // namespace dp
