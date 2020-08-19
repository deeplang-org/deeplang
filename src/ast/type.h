#pragma once

namespace dp {
namespace internal {

class Type {
public:
	Type() {
	}

	~Type() {
	}

};

enum class PrimitiveVariableTypes {
	I32,
	I64,
	Unit,
};

class VariableType : public Type {
public:
	PrimitiveVariableTypes typ;

	VariableType(PrimitiveVariableTypes typ)
		: typ(typ) {
	}
	~VariableType() {
	}

	bool isI32() const {
		return typ == PrimitiveVariableTypes::I32;
	}

	bool isI64() const {
		return typ == PrimitiveVariableTypes::I64;
	}

	bool isUnit() const {
		return typ == PrimitiveVariableTypes::Unit;
	}
};

class FunctionType : public Type {
public:
	std::vector<std::unique_ptr<Type>> Params;
	std::unique_ptr<Type>              Result;

	FunctionType() {
	}
	~FunctionType() {
	}
};

}
}
