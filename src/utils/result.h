#pragma once

namespace dp {

struct Result {
	enum Enum {
		Ok,
		Error,
	};

	Result()
			: Result(Ok) {
	}
	Result(Enum e)
			: enum_(e) {
	}
	operator Enum() const {
		return enum_;
	}
	Result& operator|=(Result rhs);

private:
	Enum enum_;
};

inline Result operator|(Result lhs, Result rhs) {
	return (lhs == Result::Error || rhs == Result::Error) ? Result::Error
																												: Result::Ok;
}

inline Result& Result::operator|=(Result rhs) {
	enum_ = *this | rhs;
	return *this;
}

inline bool Succeeded(Result result) {
	return result == Result::Ok;
}
inline bool Failed(Result result) {
	return result == Result::Error;
}

// #define CHECK_RESULT(expr)  \
// 	do {                      \
// 		if (Failed(expr)) {     \
// 			return ::dp::Result::Error; \
// 		}                       \
// 	} while (0)

} // namespace dp
