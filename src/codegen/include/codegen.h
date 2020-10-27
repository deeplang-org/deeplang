#pragma once

#include "common.h"

#define AST_AST_H
#include "astIncludeBy.h"

namespace dp {
namespace internal {

class CodeGen {
public:
	//static std::string generateWat(Module& bexp);
	static bool GenerateWasmToFile(Module* mod, const std::string& fileName);
  static bool GenerateWasm(Module* mod, std::vector<uint8_t>&);
};

} // namespace internal
} // namespace dp
