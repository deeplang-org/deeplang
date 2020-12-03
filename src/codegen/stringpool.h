#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

namespace dp {
namespace internal {

class StringPool {
public:
	StringPool()
			: offset_(0) {
	}

	StringPool(int offset)
			: offset_(offset) {
	}

	int add(const std::string& k) {
		auto off = find(k);
		if (off < 0) {
			off = offset_;
			table_.insert(std::make_pair(k, offset_));
			std::copy(k.begin(), k.end(), std::back_inserter(data_));
			data_.push_back('\0');
			offset_ += data_.size();
		}
		return off;
	}

	void remove(const std::string& k) {
		table_.erase(table_.find(k));
	}

	int find(std::string k) {
		auto it = table_.find(k);
		if (it != table_.end()) {
			return it->second;
		}
		return -1;
	}

	std::vector<uint8_t> data() {
		return data_;
	}

private:
	std::unordered_map<std::string, int> table_;
	std::vector<uint8_t>                 data_;
	int                                  offset_;
};

} // namespace internal
} // namespace dp
