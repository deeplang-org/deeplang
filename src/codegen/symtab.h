#pragma once

#include <list>
#include <string>
#include <unordered_map>

#include "ast/type.h"

namespace dp {
namespace internal {

class SymTab {

	struct SymItem {
		std::string name;
		int         index;
		Type*       type;
	};

	using SymMap = std::unordered_map<std::string, SymItem>;

	std::list<SymMap> _envs;

public:
	SymTab() {
		// global Env
		newEnv();
	}

	bool  addSym(const std::string& name, int index, Type* type);
	void  removeSym(const std::string& name);
	bool  hasSym(const std::string& name);
	Type* getSymType(const std::string& name);
	int   getSymIdx(const std::string& name);

	void newEnv();
	void dropEnv();
};

} // namespace internal
} // namespace dp
