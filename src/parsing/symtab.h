#pragma once
#include <map>
#include <string>

namespace dp {
namespace internal {

template <class T>
class SymTab {
public:
	std::map<std::string, T> table;
	int                      offset;

	SymTab() {
	}

	SymTab(int offset)
			: offset(offset) {
	}

	~SymTab() {
	}

	void push(std::string k, T v) {
		table.insert(std::make_pair(k, v));
		offset += k.size() + 1;
	}

	void remove(T v);

	T find(std::string k);
};

} // namespace internal
} // namespace dp