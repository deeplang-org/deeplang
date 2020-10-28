#pragma once

#include "common.h"

#define  LIB_WABT_TYPE_H
#include "astIncludeFrom.h"

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

	bool isI32() const {
		return kind_ == Kind::I32;
	}

	bool isI64() const {
		return kind_ == Kind::I64;
	}

	bool isUnit() const {
		return kind_ == Kind::Unit;
	}

	wabt::Type::Enum toWasmType() {
		// TODO: complete wasm type
		if (isI32()) {
			return wabt::Type::I32;
		} else if (isI64()) {
			return wabt::Type::I64;
		} else if (isUnit()) {
			return wabt::Type::Void;
		} else {
			UNREACHABLE("can't find backend data type");
		}
	}

	static PrimitiveType* getType() {
		return new PrimitiveType(PrimitiveType::Kind::Unit);
	}

	static PrimitiveType* getType(std::string typName) {
		PrimitiveType::Kind t;
		if (typName == "i32") {
			t = PrimitiveType::Kind::I32;
		} else if (typName == "i64") {
			t = PrimitiveType::I64;
		} else {
			UNREACHABLE("can't recognize type name");
		}
		return new PrimitiveType(t);
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
