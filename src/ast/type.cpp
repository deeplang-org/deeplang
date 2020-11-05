#include "ast/type.h"
#include "utils/cast.h"

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

bool Type::IsSame(Type* t1, Type* t2) {
	if (t1->typeClass() == t2->typeClass()) {
		if (auto pt1 = dyn_cast<PrimitiveType>(t1)) {
			return pt1->kind() == cast<PrimitiveType>(t2)->kind();
		} else if (auto ft1 = dyn_cast<FunctionType>(t1)) {
			auto ft2 = cast<FunctionType>(t2);
			if (ft1->Params.size() != ft2->Params.size()) {
				return false;
			}
			for (auto i = 0u; i < ft1->Params.size(); i++) {
				if (! Type::IsSame(ft1->Params[i].get(), ft2->Params[i].get())) {
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool Type::isNumberic() const {
	if (auto typ = dyn_cast<PrimitiveType>(this)) {
		return typ->isNumberic();
	}
	return false;
}

} // namespace internal
} // namespace dp
