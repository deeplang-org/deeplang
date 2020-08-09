
namespace dp {
namespace internal {
	// TODO: visitor pattern?

class ASTNode {
	std::string type;
public:
	ASTNode(std::string type) : type(type) {}
	~ASTNode() {}

	void setType(std::string newType);
	std::string retType();
}

class ProgramNode : public ASTNode {
	std::vector<std::unique_ptr<ASTNode>> body;
public:
	ProgramNode() : ASTNode("Program") {}
	ProgramNode(std::vector<std::unique_ptr<ASTNode>> body) : 
		ASTNode("Program"), body(body) {}
	~ProgramNode() {}
}

class Identifier : public ASTNode {
	std::string name;
public:
	Identifier(std::string name) :
		ASTNode("Identifier"), name(name) {}
	~Identifier() {}
}

class Literal : public ASTNode {
	std::double value;
	std::string raw;
public:
	Literal(std::double value, std::string raw) :
		ASTNode("Literal"), value(value), raw(raw) {}
	~Literal() {}
}

class ArrayExpression : public ASTNode {
	std::vector<std::unique_ptr<ASTNode>> elements;
public:
	Identifier(std::vector<std::unique_ptr<ASTNode>> elements) :
		ASTNode("ArrayExpression"), elements(elements) {}
	~Identifier() {}
}

class NewExpression : public ASTNode {
	std::unique_ptr<ASTNode> callee;
	std::vector<std::unique_ptr<ASTNode>> arguments;
public:
	NewExpression(std::unique_ptr<ASTNode> callee, std::vector<std::unique_ptr<ASTNode>> arguments) :
		ASTNode("NewExpression"), callee(callee), arguments(arguments) {}
	~NewExpression() {}
}

class CallExpression : public ASTNode {
	std::shared_ptr<ASTNode> callee;
	std::vector<std::unique_ptr<ASTNode>> arguments;
public:
	CallExpression(std::shared_ptr<ASTNode> callee, std::vector<std::unique_ptr<ASTNode>> arguments) :
		ASTNode("CallExpression"), callee(callee), arguments(arguments) {}
	~CallExpression() {}
}

class BinaryExpression : public ASTNode {
	std::string op;
	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;
public:
	BinaryExpression(std::string op, std::unique_ptr<ASTNode> left,	std::unique_ptr<ASTNode> right) :
		ASTNode("BinaryExpression"), op(op), left(left), right(right) {}
	~BinaryExpression() {}
}

class UnaryExpression : public ASTNode {
	std::string op;
	bool prefix;
	std::unique_ptr<ASTNode> argument;
public:
	UnaryExpression(std::string op, bool prefix, std::unique_ptr<ASTNode> argument) :
		ASTNode("UnaryExpression"), op(op), prefix(prefix), argument(argument) {}
	~UnaryExpression() {}
}

class UpdateExpression : public ASTNode {
	std::string op;
	bool prefix;
	std::unique_ptr<ASTNode> argument;
public:
	UpdateExpression(std::string op, bool prefix, std::unique_ptr<ASTNode> argument) :
		ASTNode("UpdateExpression"), op(op), prefix(prefix), argument(argument) {}
	~UpdateExpression() {}
}

// Statement

class BlockStatement : public ASTNode {
	std::vector<std::unique_ptr<ASTNode>> body;
public:
	BlockStatement(std::vector<std::unique_ptr<ASTNode>> body) :
		ASTNode("BlockStatement"), body(body) {}
	~BlockStatement() {}
}

// Type

class FunctionType : public ASTNode {
	std::vector<std::unique_ptr<Identifier>> params;
	std::vector<std::unique_ptr<ASTNode>> results;
public:
	FunctionType(std::vector<std::unique_ptr<Identifier>> params, std::vector<std::unique_ptr<ASTNode>> results) :
		ASTNode("FunctionType"), params(params), results(results) {}
	~FunctionType() {}
}

// Declaration

class FunctionDeclaration : public ASTNode {
	std::unique_ptr<Identifier> id;
	std::unique_ptr<FunctionType> signature;
	std::unique_ptr<BlockStatement> body;
public:
	FunctionDeclaration(std::unique_ptr<Identifier> id, std::unique_ptr<FunctionType> signature, std::unique_ptr<BlockStatement> body) :
		ASTNode("FunctionDeclaration"), id(id), signature(signature), body(body) {}
	~FunctionDeclaration() {}
}

class VariableDeclaration : public ASTNode {
	std::unique_ptr<Identifier> id;
	std::string vartype;
	std::string init;
public:
	VariableDeclaration(std::unique_ptr<Identifier> id, std::string vartype, std::string init) :
		ASTNode("VariableDeclaration"), id(id), vartype(vartype), init(init) {}
	~VariableDeclaration() {}
}




} // inernal namespace 
} // dp namespace




