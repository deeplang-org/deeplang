#include "ast/type.h"
#include "utils/cast.h"

#include <unordered_map>

namespace dp {
namespace internal {

Type* Type::Unit() {
	return PrimitiveType::MakeType(PrimitiveType::Unit);
}

Type* Type::I32() {
	return PrimitiveType::MakeType(PrimitiveType::I32);
}

Type* Type::I64() {
	return PrimitiveType::MakeType(PrimitiveType::I64);
}

Type* Type::F32() {
	return PrimitiveType::MakeType(PrimitiveType::F32);
}

Type* Type::F64() {
	return PrimitiveType::MakeType(PrimitiveType::F64);
}

Type* Type::String() {
	return PrimitiveType::MakeType(PrimitiveType::I32);
}

Type* Type::Func(TypeVector& params, Type* result) {
	return FunctionType::MakeType(params, result);
}

bool Type::IsSame(Type* t1, Type* t2) {
	return t1 == t2;
}

bool Type::isNumberic() const {
	if (auto typ = dyn_cast<PrimitiveType>(this)) {
		return typ->isNumberic();
	}
	return false;
}

PrimitiveType* PrimitiveType::MakeType(Kind kind) {
	switch (kind) {
	case PrimitiveType::Unit: {
		static auto typ = new PrimitiveType(PrimitiveType::Unit);
		return typ;
	}
	case PrimitiveType::I32: {
		static auto typ = new PrimitiveType(PrimitiveType::I32);
		return typ;
	}
	case PrimitiveType::I64: {
		static auto typ = new PrimitiveType(PrimitiveType::I64);
		return typ;
	}
	case PrimitiveType::F32: {
		static auto typ = new PrimitiveType(PrimitiveType::F32);
		return typ;
	}
	case PrimitiveType::F64: {
		static auto typ = new PrimitiveType(PrimitiveType::F64);
		return typ;
	}
	case PrimitiveType::Bool: {
		static auto typ = new PrimitiveType(PrimitiveType::Bool);
		return typ;
	}
	case PrimitiveType::String: {
		static auto typ = new PrimitiveType(PrimitiveType::String);
		return typ;
	}
	default:
		UNREACHABLE("PrimitiveType::MakeType");
	}
}

PrimitiveType* PrimitiveType::MakeType(const std::string& typName) {
	Kind t;
	if (typName == "Unit") {
		t = PrimitiveType::Unit;
	} else if (typName == "i32") {
		t = PrimitiveType::I32;
	} else if (typName == "i64") {
		t = PrimitiveType::I64;
	} else if (typName == "f32") {
		t = PrimitiveType::F32;
	} else if (typName == "f64") {
		t = PrimitiveType::F64;
	} else if (typName == "string") {
		t = PrimitiveType::String;
	} else {
		UNREACHABLE("can't recognize type name");
	}
	return PrimitiveType::MakeType(t);
}

struct TypeVectorHasher {
	size_t operator()(const TypeVector& V) const {
		size_t hash = V.size();
		for (auto& t : V) {
			auto i = reinterpret_cast<intptr_t>(t);
			hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		}
		return hash;
	}
};

FunctionType* FunctionType::MakeType(TypeVector& params, Type* result) {
	static std::unordered_map<TypeVector, FunctionType*, TypeVectorHasher> typeVecMap;

	TypeVector typeVec(params);
	typeVec.push_back(result);

	auto it = typeVecMap.find(typeVec);
	if (it != typeVecMap.end()) {
		return it->second;
	}

	auto typ = new FunctionType(params, result);
	typeVecMap.emplace(typeVec, typ);
	return typ;
}

TypeVector FunctionType::params() {
	return params_;
}

Type* FunctionType::result() {
	return result_;
}

} // namespace internal
} // namespace dp
