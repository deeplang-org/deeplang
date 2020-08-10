#include <vector>
#include <string>
#include <memory>

namespace dp {
namespace internal {
	// TODO: visitor pattern
enum class BinaryOperator {
	Plus,
	Minus,
	Mult,
	Div,
	BitwiseAnd,
	BitwiseOr,
};

enum class UnaryOperator {
	Minus,

};

enum class UpdateOperator {
	Increment,
	Decrement,
};


enum class NodeType {
	Program,
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

enum class VariableType {
	i32,
	i64
};

class ASTNode {
public:
	NodeType type;
	ASTNode(NodeType type) : type(type) {}
	~ASTNode() {}

	void setType(NodeType newType);
	NodeType retType();
};

class ProgramNode : public ASTNode {
public:
	std::vector<ASTNode*> body;
	ProgramNode() : ASTNode(NodeType::Program) {}
	ProgramNode(std::vector<ASTNode*> body) : 
		ASTNode(NodeType::Program), body(body) {}
	~ProgramNode() {}
};

class Identifier : public ASTNode {
public:
	std::string name;
	Identifier(std::string name) :
		ASTNode(NodeType::Identifier), name(name) {}
	~Identifier() {}
};

class Literal : public ASTNode {
public:
	double value;
	std::string raw;
	Literal(double value, std::string raw) :
		ASTNode(NodeType::Literal), value(value), raw(raw) {}
	~Literal() {}
};

class ArrayExpression : public ASTNode {
public:
	std::vector<ASTNode*> elements;
	ArrayExpression(std::vector<ASTNode*> elements) :
		ASTNode(NodeType::ArrayExpression), elements(elements) {}
	~ArrayExpression() {}
};

class NewExpression : public ASTNode {
public:
	std::unique_ptr<ASTNode> callee;
	std::vector<ASTNode*> arguments;
	NewExpression(ASTNode* callee, std::vector<ASTNode*> arguments) :
		ASTNode(NodeType::NewExpression), callee(callee), arguments(arguments) {}
	~NewExpression() {}
};

class CallExpression : public ASTNode {
public:
	std::shared_ptr<ASTNode> callee;
	std::vector<ASTNode*> arguments;
	CallExpression(std::shared_ptr<ASTNode> callee, std::vector<ASTNode*> arguments) :
		ASTNode(NodeType::CallExpression), callee(callee), arguments(arguments) {}
	~CallExpression() {}
};

class BinaryExpression : public ASTNode {
public:
	BinaryOperator op;
	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;
	BinaryExpression(BinaryOperator op, ASTNode* left, ASTNode* right) :
		ASTNode(NodeType::BinaryExpression), op(op), left(left), right(right) {}
	~BinaryExpression() {}
};

class UnaryExpression : public ASTNode {
public:
	UnaryOperator op;
	bool prefix;
	std::unique_ptr<ASTNode> argument;
	UnaryExpression(UnaryOperator op, bool prefix, ASTNode* argument) :
		ASTNode(NodeType::UnaryExpression), op(op), prefix(prefix), argument(argument) {}
	~UnaryExpression() {}
};

class UpdateExpression : public ASTNode {
public:
	UpdateOperator op;
	bool prefix;
	std::unique_ptr<ASTNode> argument;
	UpdateExpression(UpdateOperator op, bool prefix, ASTNode* argument) :
		ASTNode(NodeType::UpdateExpression), op(op), prefix(prefix), argument(argument) {}
	~UpdateExpression() {}
};

// Statement

class BlockStatement : public ASTNode {
public:
	std::vector<ASTNode*> body;
	BlockStatement(std::vector<ASTNode*> body) :
		ASTNode(NodeType::BlockStatement), body(body) {}
	~BlockStatement() {}
};

// Type

class FunctionType : public ASTNode {
public:
	std::vector<Identifier*> params;
	std::vector<ASTNode*> results;
	FunctionType(std::vector<Identifier*> params, std::vector<ASTNode*> results) :
		ASTNode(NodeType::FunctionType), params(params), results(results) {}
	~FunctionType() {}
};

// Declaration

class FunctionDeclaration : public ASTNode {
public:
	std::unique_ptr<Identifier> id;
	std::unique_ptr<FunctionType> signature;
	std::unique_ptr<BlockStatement> body;
	FunctionDeclaration(Identifier* id, FunctionType* signature, BlockStatement* body) :
		ASTNode(NodeType::FunctionDeclaration), id(id), signature(signature), body(body) {}
	~FunctionDeclaration() {}
};

class VariableDeclaration : public ASTNode {
public:
	std::unique_ptr<Identifier> id;
	VariableType vartype;
	std::string init;
	VariableDeclaration(Identifier* id, VariableType vartype, std::string init) :
		ASTNode(NodeType::VariableDeclaration), id(id), vartype(vartype), init(init) {}
	~VariableDeclaration() {}
};




} // inernal namespace 
} // dp namespace




