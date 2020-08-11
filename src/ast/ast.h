#pragma once
#include "common.h"

namespace dp {
namespace internal {

enum class AstKind {
	Module,
	Identifier,
	Literal,
	ArrayExpression,
	NewExpression,
	CallExpression,
	BinaryExpression,
	UnaryExpression,
	UpdateExpression,
	BlockStatement,
	FunctionType,
	FunctionDeclaration,
	VariableDeclaration
};

class ASTNode {
public:
	AstKind kind;
	ASTNode(AstKind kind)
			: kind(kind) {
	}
	~ASTNode() {
	}
};

class ModuleNode : public ASTNode {
public:
	std::vector<ASTNode*> body;

	ModuleNode()
			: ASTNode(AstKind::Module) {
	}
	ModuleNode(std::vector<ASTNode*> body)
			: ASTNode(AstKind::Module), body(body) {
	}
	~ModuleNode() {
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

class ArrayExpression : public ASTNode {
public:
	std::vector<ASTNode*> elements;

	ArrayExpression(std::vector<ASTNode*> elements)
			: ASTNode(AstKind::ArrayExpression), elements(elements) {
	}
	~ArrayExpression() {
	}
};

class NewExpression : public ASTNode {
public:
	std::unique_ptr<ASTNode> callee;
	std::vector<ASTNode*>    arguments;

	NewExpression(ASTNode* callee, std::vector<ASTNode*> arguments)
			: ASTNode(AstKind::NewExpression), callee(callee), arguments(arguments) {
	}
	~NewExpression() {
	}
};

class CallExpression : public ASTNode {
public:
	std::shared_ptr<ASTNode> callee;
	std::vector<ASTNode*>    arguments;

	CallExpression(std::shared_ptr<ASTNode> callee, std::vector<ASTNode*> arguments)
			: ASTNode(AstKind::CallExpression), callee(callee), arguments(arguments) {
	}
	~CallExpression() {
	}
};

enum class BinaryOperator {
	Plus,
	Minus,
	Mult,
	Div,
	BitwiseAnd,
	BitwiseOr,
};

class BinaryExpression : public ASTNode {
public:
	BinaryOperator           op;
	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;

	BinaryExpression(BinaryOperator op, ASTNode* left, ASTNode* right)
			: ASTNode(AstKind::BinaryExpression), op(op), left(left), right(right) {
	}
	~BinaryExpression() {
	}
};

class UnaryExpression : public ASTNode {
public:
	enum class UnaryOperator {
		Minus,
	};
	UnaryOperator            op;
	bool                     prefix;
	std::unique_ptr<ASTNode> argument;

	UnaryExpression(UnaryOperator op, bool prefix, ASTNode* argument)
			: ASTNode(AstKind::UnaryExpression), op(op), prefix(prefix), argument(argument) {
	}
	~UnaryExpression() {
	}
};

class UpdateExpression : public ASTNode {
public:
	enum class UpdateOperator {
		Increment,
		Decrement,
	};
	UpdateOperator           op;
	bool                     prefix;
	std::unique_ptr<ASTNode> argument;

	UpdateExpression(UpdateOperator op, bool prefix, ASTNode* argument)
			: ASTNode(AstKind::UpdateExpression), op(op), prefix(prefix), argument(argument) {
	}
	~UpdateExpression() {
	}
};

// Statement

class BlockStatement : public ASTNode {
public:
	std::vector<ASTNode*> body;

	BlockStatement(std::vector<ASTNode*> body)
			: ASTNode(AstKind::BlockStatement), body(body) {
	}
	~BlockStatement() {
	}
};

// Type

enum class VariableType {
	i32,
	i64
};

class VariableDeclaration : public ASTNode {
public:
	Identifier   id;
	VariableType vartype;
	std::string  init;

	VariableDeclaration(Identifier id, VariableType vartype, std::string init)
			: ASTNode(AstKind::VariableDeclaration), id(id), vartype(vartype), init(init) {
	}
	~VariableDeclaration() {
	}
};

class FunctionType : public ASTNode {
public:
	std::vector<VariableDeclaration> Params;
	std::vector<VariableType>        Results;

	FunctionType(std::vector<VariableDeclaration> params, std::vector<VariableType> results)
			: ASTNode(AstKind::FunctionType), Params(params), Results(results) {
	}
	~FunctionType() {
	}
};

// Declaration

class FunctionStatement : public ASTNode {
public:
	Identifier     id;
	FunctionType   signature;
	BlockStatement body;
	FunctionStatement(Identifier id, FunctionType signature, BlockStatement body)
			: ASTNode(AstKind::FunctionDeclaration), id(id), signature(signature), body(body) {
	}
	~FunctionStatement() {
	}
};

} // namespace internal
} // namespace dp
