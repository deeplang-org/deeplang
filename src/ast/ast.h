#pragma once
#include "common.h"

namespace dp {
namespace internal {

enum class AstKind {
	Module,
	Identifier,
	Literal,

	// Expression
	ArrayExpression,
	NewExpression,
	CallExpression,
	BinaryExpression,
	UnaryExpression,
	UpdateExpression,

	// Statement
	BlockStatement,

	// Declaration
	FunctionDeclaration,
	VariableDeclaration,

	// Type
	Type,
	FunctionType,
	VariableType

};

// forward decl
class ASTNode;
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

class Identifier : public ASTNode {
public:
	std::string name;

	Identifier(std::string name)
			: ASTNode(AstKind::Identifier), name(name) {
	}
	~Identifier() {
	}
};

class Literal : public ASTNode {
public:
	union {
		int         i32val;
		long        i64val;
		float       f32val;
		double      f64val;
		std::string strval;
	};

	Literal(int value)
			: ASTNode(AstKind::Literal), i32val(value) {
	}
	~Literal() {
	}
};

class Expression : public ASTNode {
public:
	Type* expTyp;

	Expression(AstKind kind)
			: ASTNode(kind) {
	}
	~Expression() {
	}

	bool isBinaryExp() const {
		return kind == AstKind::BinaryExpression;
	}
};

class Statement : public ASTNode {
public:
	Statement(AstKind kind)
			: ASTNode(kind) {
	}
	~Statement() {
	}

	bool isBlockStatement() const {
		return kind == AstKind::BlockStatement;
	}
};

class Declaration : public ASTNode {
public:
	Declaration(AstKind kind)
			: ASTNode(kind) {
	}
	~Declaration() {
	}

	bool isFunctionDecl() const {
		return kind == AstKind::FunctionDeclaration;
	}

	bool isVariableDeclaration() const {
		return kind == AstKind::VariableDeclaration;
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
	std::vector<Type*> Params;
	Type*              Result;

	FunctionType(std::vector<Type*> params, Type* result)
			: Type(AstKind::FunctionType), Params(std::move(params)), Result(result) {
	}
	~FunctionType() {
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
	BinaryOperator* op;
	Expression*     left;
	Expression*     right;

	BinaryExpression(BinaryOperator* op, Expression* left, Expression* right)
			: Expression(AstKind::BinaryExpression), op(op), left(left), right(right) {
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

// Statement

class BlockStatement : public Statement {
public:
	std::vector<ASTNode*> body;

	BlockStatement(std::vector<ASTNode*> body)
			: Statement(std::move(AstKind::BlockStatement)), body(body) {
	}
	~BlockStatement() {
	}
};

// Declaration

class VariableDeclaration : public Declaration {
public:
	Identifier* id;
	Type*       vartype;
	Expression* init;

	VariableDeclaration(Identifier* id, Type* vartype, Expression* init)
			: Declaration(AstKind::VariableDeclaration), id(id), vartype(vartype), init(init) {
	}
	~VariableDeclaration() {
	}
};

class FunctionDeclaration : public Declaration {
public:
	Identifier*   id;
	FunctionType* signature;
	Statement*    body;
	FunctionDeclaration(Identifier* id, FunctionType* signature, Statement* body)
			: Declaration(AstKind::FunctionDeclaration), id(id), signature(signature), body(body) {
	}
	~FunctionDeclaration() {
	}
};

} // namespace internal
} // namespace dp
