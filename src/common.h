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

struct Position {
  size_t line = 0;
  size_t character = 0;
  bool operator==(const Position &o) const {
    return line == o.line && character == o.character;
  }
  bool operator<(const Position &o) const {
    return line != o.line ? line < o.line : character < o.character;
  }
  bool operator<=(const Position &o) const {
    return line != o.line ? line < o.line : character <= o.character;
  }
  std::string toString() const;
};

struct Range {
  Position start;
  Position end;
  bool operator==(const Range &o) const {
    return start == o.start && end == o.end;
  }
  bool operator<(const Range &o) const {
    return !(start == o.start) ? start < o.start : end < o.end;
  }
  bool includes(const Range &o) const {
    return start <= o.start && o.end <= end;
  }
  bool intersects(const Range &o) const {
    return start < o.end && o.start < end;
  }
};

struct Location {
  Range range;
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
