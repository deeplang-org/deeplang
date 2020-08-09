#pragma once

#include "common.h"
#include "ast/ast.h"

namespace dp {
namespace internal {
	class CodeGen {
	public:
		CodeGen();

		std::string generate(BinaryExpression bexp);
	};
} // inernal namespace 
} // dp namespace
