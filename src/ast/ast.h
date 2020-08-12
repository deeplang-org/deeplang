#pragma once
#include "common.h"

namespace dp {
namespace internal {

enum class AstKind {
	Module,

	// Statement
	ExpressionStatement,
	FunctionDeclaration,
	VariableDeclaration,

	// Expression
	ArrayExpression,
	BinaryExpression,
	BlockExpression,
	CallExpression,
	LiteralExpression,
	NewExpression,
	UnaryExpression,
	UpdateExpression,

	// Type
	Type,
	FunctionType,
	VariableType
};

// forward decl
class Identifier;
class Literal;
class Expression;
class Statement;
class Declaration;
class Type;

class ASTNode {
public:
	AstKind kind;
	ASTNode(AstKind kind)
			: kind(kind) {
	}
	~ASTNode() {
	}
};

class Module : public ASTNode {
public:
	std::vector<std::unique_ptr<Declaration>> stmts;
};

class Expression : public ASTNode {
public:
	std::unique_ptr<Type> expTyp;

	Expression(AstKind kind)
			: ASTNode(kind) {
	}
	~Expression() {
	}
};

class Statement : public ASTNode {
public:
	Statement(AstKind kind)
			: ASTNode(kind) {
	}
	~Statement() {
	}
};

class Declaration : public Statement {
public:
	Declaration(AstKind kind)
			: Statement(kind) {
	}
	~Declaration() {
	}
};

// Type

class Type : public ASTNode {
public:
	Type(AstKind kind)
			: ASTNode(kind) {
	}
	~Type() {
	}

	bool isFunctonType() const {
		return kind == AstKind::FunctionType;
	}
	bool isVariableType() const {
		return kind == AstKind::VariableType;
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
			: Type(AstKind::VariableType), typ(typ) {
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

	FunctionType()
			: Type(AstKind::FunctionType) {
	}
	~FunctionType() {
	}
};

// Identifier

class Identifier {
public:
	std::string name;

	Identifier(std::string name)
			: name(name) {
	}
	~Identifier() {
	}
};

// Expression

class Literal : public Expression {
public:
	union {
		int         i32val;
		long        i64val;
		float       f32val;
		double      f64val;
		std::string strval;
	};

	Literal(int value)
			: Expression(AstKind::LiteralExpression), i32val(value) {
	}
	~Literal() {
	}
};

// class ArrayExpression : public Expression {
// public:
// 	std::vector<ASTNode*> elements;

// 	ArrayExpression(std::vector<ASTNode*> elements)
// 			: ASTNode(AstKind::ArrayExpression), elements(elements) {
// 	}
// 	~ArrayExpression() {
// 	}
// };

// class NewExpression : public Expression {
// public:
// 	std::unique_ptr<ASTNode> callee;
// 	std::vector<ASTNode*>    arguments;

// 	NewExpression(ASTNode* callee, std::vector<ASTNode*> arguments)
// 			: ASTNode(AstKind::NewExpression), callee(callee), arguments(arguments) {
// 	}
// 	~NewExpression() {
// 	}
// };

// class CallExpression : public Expression {
// public:
// 	std::shared_ptr<ASTNode> callee;
// 	std::vector<ASTNode*>    arguments;

// 	CallExpression(std::shared_ptr<ASTNode> callee, std::vector<ASTNode*> arguments)
// 			: ASTNode(AstKind::CallExpression), callee(callee), arguments(arguments) {
// 	}
// 	~CallExpression() {
// 	}
// };

enum class BinaryOperator {
	Plus,
	Minus,
	Mult,
	Div,
	BitwiseAnd,
	BitwiseOr,
};

class BinaryExpression : public Expression {
public:
	BinaryOperator              op;
	std::unique_ptr<Expression> left;
	std::unique_ptr<Expression> right;

	BinaryExpression(BinaryOperator op)
			: Expression(AstKind::BinaryExpression), op(op) {
	}
	~BinaryExpression() {
	}
};

// class UnaryExpression : public Expression {
// public:
// 	enum class UnaryOperator {
// 		Minus,
// 	};
// 	UnaryOperator            op;
// 	bool                     prefix;
// 	std::unique_ptr<ASTNode> argument;

// 	UnaryExpression(UnaryOperator op, bool prefix, ASTNode* argument)
// 			: ASTNode(AstKind::UnaryExpression), op(op), prefix(prefix), argument(argument) {
// 	}
// 	~UnaryExpression() {
// 	}
// };

// class UpdateExpression : public Expression {
// public:
// 	enum class UpdateOperator {
// 		Increment,
// 		Decrement,
// 	};
// 	UpdateOperator           op;
// 	bool                     prefix;
// 	std::unique_ptr<ASTNode> argument;

// 	UpdateExpression(UpdateOperator op, bool prefix, ASTNode* argument)
// 			: ASTNode(AstKind::UpdateExpression), op(op), prefix(prefix), argument(argument) {
// 	}
// 	~UpdateExpression() {
// 	}
// };


class BlockExpession : public Expression {
public:
	std::vector<std::unique_ptr<Statement>> stmts;

	BlockExpession()
			: Expression(AstKind::BlockExpression) {
	}
	~BlockExpession() {
	}
};

// Statement

class ExpressionStatement : public Statement {
public:
	ExpressionStatement(AstKind kind)
			: Statement(kind) {
	}
	std::unique_ptr<Expression> expr;
};

// Declaration

class VariableDeclaration : public Declaration {
public:
	Identifier                  id;
	std::unique_ptr<Type>       vartype;
	std::unique_ptr<Expression> init;

	VariableDeclaration(std::string name)
			: Declaration(AstKind::VariableDeclaration), id(name) {
	}
	~VariableDeclaration() {
	}
};

class FunctionDeclaration : public Declaration {
public:
	Identifier                      id;
	std::unique_ptr<FunctionType>   signature;
	std::unique_ptr<BlockExpession> body;

	FunctionDeclaration(std::string name)
			: Declaration(AstKind::FunctionDeclaration), id(name) {
	}
	~FunctionDeclaration() {
	}
};

} // namespace internal
} // namespace dp
