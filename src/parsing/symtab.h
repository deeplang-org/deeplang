#pragma once
#include <unordered_map>
#include <string>

namespace dp {
namespace internal {

template <class T>
class SymTab {
public:
	typedef std::shared_ptr<SymTab<T>> SymTabSharedPtr;

	SymTabSharedPtr pre;

	std::unordered_map<std::string, T> table;

	SymTab() {
	}

	SymTab(SymTabSharedPtr symTab)
			: pre(symTab) {
	}

	~SymTab() {
	}

	void push(std::string k, T v);

	void remove(T v);

	T find(std::string k);
};

} // namespace internal
} // namespace dp