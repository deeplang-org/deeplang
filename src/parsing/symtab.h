#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

namespace dp {
namespace internal {

template <class T>
class SymTab {
public:
	std::unordered_map<std::string, T> table;
	std::vector<uint8_t>               data;
	int                                offset;

	SymTab()
			: offset(0) {
	}

	SymTab(int offset)
			: offset(offset) {
	}

	T add(const std::string& k, T v) {
		if (table.find(k) != table.end()) {
			return table.at(k);
		}
		table.insert(std::make_pair(k, v));
		std::copy(k.begin(), k.end(), std::back_inserter(data));
		data.push_back('\0');
		offset = data.size() + 1;
		return v;
	}

	void remove(T v) {
		table.erase(table.find(v));
	}

	T find(std::string k) {
		return table.find(k);
	}
};

} // namespace internal
} // namespace dp
