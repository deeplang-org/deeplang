#pragma once

#include "common.h"
#include "ast/ast.h"

namespace dp {
namespace internal {

class CodeGen {
public:
	//static std::string generateWat(Module& bexp);
	static bool GenerateWasmToFile(Module* mod, const std::string& fileName);
};

} // namespace internal
} // namespace dp
