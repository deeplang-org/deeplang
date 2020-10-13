#pragma once

#include "common.h"

namespace dp {
namespace internal {

class Type;
typedef std::unique_ptr<Type> TypePtr;
typedef std::vector<TypePtr>  TypeVector;

class PrimitiveType;
class FunctionType;

class Type {
public:
	enum TypeClass {
		Primitive,
		Func,
		Reference
	};

	TypeClass typeClass() const {
		return tc_;
	}

	bool isNumberic() const;

	const char* getTypeClassName() const {
		switch (tc_) {
		case TypeClass::Primitive:
			return "Primitive";
		case TypeClass::Func:
			return "Func";
		}
	}

	static TypePtr I32();
	static TypePtr I64();
	static TypePtr F32();
	static TypePtr F64();
	static TypePtr String();

protected:
	Type() = default; // Provided so Type can be member of a union.
	Type(TypeClass e)
			: tc_(e) {
	}

	TypeClass tc_;
};

class PrimitiveType : public Type {
public:
	enum Kind {
		Unit,
		I32,
		I64,
		F32,
		F64,
		Bool,
		String
	};

	PrimitiveType(Kind kind)
			: Type(Primitive), kind_(kind) {
	}
	operator Kind() const {
		return kind_;
	}

	Kind kind() const {
		return kind_;
	}

	const char* getKindName() const {
		switch (kind_) {
		case Kind::I32:
			return "i32";
		case Kind::I64:
			return "i64";
		case Kind::F32:
			return "f32";
		case Kind::F64:
			return "f64";
		case Kind::Unit:
			return "unit";
		case Kind::String:
			return "string";
		}
	}

	bool isNumberic() const {
		switch (kind_) {
		case Kind::I32:
		case Kind::I64:
		case Kind::F32:
		case Kind::F64:
			return true;
		default:
			return false;
		}
	}

	static bool classof(const Type* type) {
		return type->typeClass() == Primitive;
	}

private:
	Kind kind_;
};

class FunctionType : public Type {
public:
	TypeVector Params;
	TypePtr    Result;

	FunctionType()
			: Type(Func) {
	}

	static bool classof(const Type* type) {
		return type->typeClass() == Func;
	}
};

} // namespace internal
} // namespace dp
