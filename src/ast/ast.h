#pragma once
#include "common.h"

#include "ast/type.h"

namespace dp {
namespace internal {

struct Location {
	std::string  fileName;
	unsigned int line;
	unsigned int firstColumn;
	unsigned int lastColumn;
};

class ASTNode {
public:
	ASTNode(const Location& loc = Location())
			: loc(loc) {
	}
	~ASTNode() {
	}
	Location loc;
};

class Identifier {
public:
	std::string name;

	Identifier(const std::string& name)
			: name(name) {
	}
	~Identifier() {
	}
};

class Statement;
typedef std::unique_ptr<Statement> StatementPtr;
typedef std::vector<StatementPtr>  StatementVector;

// Module

class Module : public ASTNode {
public:
	Module(std::string name, const Location& loc = Location())
			: ASTNode(loc), id(name) {
	}
	~Module() {
	}

	Identifier      id;
	StatementVector stmts;
};

typedef std::unique_ptr<Module> ModulePtr;

// Statement

enum class StatementKind {
	VariableDeclaration,
	FunctionDeclaration,
	Expression
};

class Statement : public ASTNode {
public:
	Statement()          = delete;
	virtual ~Statement() = default;

	StatementKind kind() const {
		return kind_;
	}

protected:
	explicit Statement(StatementKind kind, const Location& loc = Location())
			: ASTNode(loc), kind_(kind) {
	}

	StatementKind kind_;
};

template <StatementKind Kind>
class StatementMixin : public Statement {
public:
	static bool classof(const Statement* expr) {
		return expr->kind() == Kind;
	}

	explicit StatementMixin(const Location& loc = Location())
			: Statement(Kind, loc) {
	}
};

class Expression;
typedef std::unique_ptr<Expression> ExpressionPtr;
typedef std::vector<ExpressionPtr>  ExpressionVector;

class ExpressionStatement : public StatementMixin<StatementKind::Expression> {
public:
	ExpressionStatement(const Location& loc = Location())
			: StatementMixin<StatementKind::Expression>(loc) {
	}

	ExpressionPtr expr;
};

class VariableDeclaration : public StatementMixin<StatementKind::VariableDeclaration> {
public:
	VariableDeclaration(std::string name, const Location& loc = Location())
			: StatementMixin<StatementKind::VariableDeclaration>(loc), id(name) {
	}
	~VariableDeclaration() {
	}

	Identifier                  id;
	std::unique_ptr<Type>       vartype;
	std::unique_ptr<Expression> init;
};

class BlockExpession;

class FunctionDeclaration : public StatementMixin<StatementKind::FunctionDeclaration> {
public:
	FunctionDeclaration(std::string name, const Location& loc = Location())
			: StatementMixin<StatementKind::FunctionDeclaration>(loc), id(name), isPublic(true) {
	}
	~FunctionDeclaration() {
	}

	Identifier                      id;
	std::unique_ptr<FunctionType>   signature;
	std::unique_ptr<BlockExpession> body;
	bool                            isPublic;
};

// Expression

enum class ExpressionKind {
	Array,
	Binary,
	Block,
	Call,
	Literal,
	New,
	Path,
	Unary,
	Update,
};

class Expression : public ASTNode {
public:
	Expression()          = delete;
	virtual ~Expression() = default;

	ExpressionKind kind() const {
		return kind_;
	}

protected:
	explicit Expression(ExpressionKind kind, const Location& loc = Location())
			: ASTNode(loc), kind_(kind) {
	}

	ExpressionKind kind_;
};

template <ExpressionKind Kind>
class ExpressionMixin : public Expression {
public:
	static bool classof(const Expression* expr) {
		return expr->kind() == Kind;
	}

	explicit ExpressionMixin(const Location& loc = Location())
			: Expression(Kind, loc) {
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

class BinaryExpression : public ExpressionMixin<ExpressionKind::Binary> {
public:
	BinaryExpression(BinaryOperator op, const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Binary>(loc), op(op) {
	}

	BinaryOperator op;
	ExpressionPtr  left;
	ExpressionPtr  right;
};

class LiteralExpression : public ExpressionMixin<ExpressionKind::Literal> {
public:
	LiteralExpression(int value, const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Literal>(loc), i32val(value) {
	}
	~LiteralExpression() {
	}

	union {
		int         i32val;
		long        i64val;
		float       f32val;
		double      f64val;
		std::string strval;
	};
};

class PathExpression : public ExpressionMixin<ExpressionKind::Path> {
public:
	PathExpression(std::string name, const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Path>(loc), id(name) {
	}

	Identifier id;
};

class BlockExpession : public ExpressionMixin<ExpressionKind::Block> {
public:
	BlockExpession(const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Block>(loc) {
	}

	StatementVector stmts;
};

} // namespace internal
} // namespace dp
