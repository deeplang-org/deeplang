#include "include/type.h"
#include "cast.h"

namespace dp {
namespace internal {

TypePtr Type::I32() {
	return std::make_unique<PrimitiveType>(PrimitiveType::I32);
}

TypePtr Type::I64() {
	return std::make_unique<PrimitiveType>(PrimitiveType::I64);
}

TypePtr Type::F32() {
	return std::make_unique<PrimitiveType>(PrimitiveType::F32);
}

TypePtr Type::F64() {
	return std::make_unique<PrimitiveType>(PrimitiveType::F64);
}

TypePtr Type::String() {
	return std::make_unique<PrimitiveType>(PrimitiveType::String);
}

bool Type::isNumberic() const {
	if (auto typ = dyn_cast<PrimitiveType>(this)) {
		return typ->isNumberic();
	}
	return false;
}

} // namespace internal
} // namespace dp
