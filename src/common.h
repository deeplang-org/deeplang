#pragma once

#include <cstdarg>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace dp {

#define UNREACHABLE(v)                                   \
	do {                                                   \
		std::cout << "unreachable code: " << v << std::endl; \
		exit(1);                                             \
	} while (0)

struct Location {
	std::string  fileName;
	unsigned int line;
	unsigned int firstColumn;
	unsigned int lastColumn;
};


inline std::string StringPrintf(const char* format, ...) {
	va_list args;
	va_list args_copy;
	va_start(args, format);
	va_copy(args_copy, args);
	size_t            len = vsnprintf(nullptr, 0, format, args) + 1; // For \0.
	std::vector<char> buffer(len);
	va_end(args);
	vsnprintf(buffer.data(), len, format, args_copy);
	va_end(args_copy);
	return std::string(buffer.data(), len - 1);
}

} // namespace dp
