#pragma once

#include "common.h"

namespace dp {

enum class ErrorLevel {
	Warning,
	Error,
};

static inline const char* GetErrorLevelName(ErrorLevel error_level) {
	switch (error_level) {
	case ErrorLevel::Warning:
		return "warning";
	case ErrorLevel::Error:
		return "error";
	}
	UNREACHABLE("GetErrorLevelName");
}

class Error {
public:
	Error()
			: level(ErrorLevel::Error) {
	}
	Error(ErrorLevel level, Location loc, const std::string& message)
			: level(level), loc(loc), message(message) {
	}

	ErrorLevel  level;
	Location    loc;
	std::string message;
};

using Errors = std::vector<Error>;

} // namespace dp
