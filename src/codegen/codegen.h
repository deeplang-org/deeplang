#pragma once

#include "common.h"
#include "ast/ast.h"
#include "DLParserVisitor.h"

namespace dp {
namespace internal {

class CodeGen {
public:
	//static std::string generateWat(Module& bexp);
	static std::string generateWasm(Module* bexp, const std::string& fileName);
};

} // namespace internal
} // namespace dp
