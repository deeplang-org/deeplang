#pragma once

#include "common.h"

namespace dp {
namespace internal {

class Type;
using TypeVector = std::vector<Type*>;

class PrimitiveType;
class FunctionType;

class Type {
public:
	enum TypeClass {
		Primitive,
		Function,
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
		case TypeClass::Function:
			return "Function";
		case TypeClass::Reference:
			return "Reference";
		}
	}

	static Type* Unit();
	static Type* I32();
	static Type* I64();
	static Type* F32();
	static Type* F64();
	static Type* String();
	static Type* Func(TypeVector& params, Type* result);

	static bool IsSame(Type* t1, Type* t2);

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

	bool isI32() const {
		return kind_ == Kind::I32;
	}

	bool isI64() const {
		return kind_ == Kind::I64;
	}

	bool isF32() const {
		return kind_ == Kind::F32;
	}

	bool isF64() const {
		return kind_ == Kind::F64;
	}

	bool isUnit() const {
		return kind_ == Kind::Unit;
	}

	static PrimitiveType* MakeType(Kind kind);
	static PrimitiveType* MakeType(const std::string& typName);

	static bool classof(const Type* type) {
		return type->typeClass() == Type::Primitive;
	}

private:
	PrimitiveType(Kind kind)
			: Type(Type::Primitive), kind_(kind) {
	}

	Kind kind_;
};

class FunctionType : public Type {
public:
	static bool classof(const Type* type) {
		return type->typeClass() == Type::Function;
	}

	TypeVector params();
	Type*      result();

	static FunctionType* MakeType(TypeVector& params, Type* result);

private:
	FunctionType(TypeVector& params, Type* result)
			: Type(Type::Function), params_(params), result_(result) {
	}

	TypeVector params_;
	Type*      result_;
};

} // namespace internal
} // namespace dp
