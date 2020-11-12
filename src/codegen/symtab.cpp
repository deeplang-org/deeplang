#include "codegen/symtab.h"

namespace dp {
namespace internal {

bool SymTab::addSym(const std::string& name, int index, Type* type) {
	auto& map = _envs.front();
	if (map.find(name) != map.end()) {
		return false;
	}
	map.emplace(name, SymItem{name, index, type});
	return true;
}

void SymTab::removeSym(const std::string& name) {
	auto& map = _envs.front();
	map.erase(name);
}

bool SymTab::hasSym(const std::string& name) {
	for (auto& map : _envs) {
		if (map.find(name) != map.end()) {
			return true;
		}
	}
	return false;
}

Type* SymTab::getSymType(const std::string& name) {
	for (auto& map : _envs) {
		auto it = map.find(name);
		if (it != map.end()) {
			return it->second.type;
		}
	}
	return nullptr;
}

int SymTab::getSymIdx(const std::string& name) {
	for (auto& map : _envs) {
		auto it = map.find(name);
		if (it != map.end()) {
			return it->second.index;
		}
	}
	return -1;
}

void SymTab::newEnv() {
	_envs.push_front(SymMap{});
}

void SymTab::dropEnv() {
	if (_envs.size() > 1) {
		_envs.pop_front();
	}
}

} // namespace internal
} // namespace dp
