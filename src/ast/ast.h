#pragma once
#include "common.h"

#include "ast/type.h"
#include "utils/error.h"

namespace dp {
namespace internal {

class ASTNode {
public:
	ASTNode(const Location& loc = Location())
			: loc(loc) {
	}

	std::string toString() const;
	Location    loc;
};

class Identifier {
public:
	std::string name;

	Identifier(const std::string& name)
			: name(name) {
	}

	std::string toString() const {
		return "Identifier";
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

	std::string toString() const {
		return "Module";
	}

	Identifier      id;
	StatementVector stmts;
};

typedef std::unique_ptr<Module> ModulePtr;

// Statement

enum class StatementKind {
	// local(let) binding
	Local,
	// Function definition
	Function,
	// Expression without trailing semi-colon
	Expression,
	// Expression with trailing semi-colon
	SemiExpression,
	// Just a trailing semi-colon
	Empty
};

class Statement : public ASTNode {
public:
	Statement()          = delete;
	virtual ~Statement() = default;

	StatementKind kind() const {
		return kind_;
	}

	std::string toString() const {
		return "Statement";
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

	std::string toString() const {
		return "StatementMixin";
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

	std::string toString() const {
		return "ExpressionStatement";
	}

	ExpressionPtr expr;
};

class SemiExpressionStatement : public StatementMixin<StatementKind::SemiExpression> {
public:
	SemiExpressionStatement(const Location& loc = Location())
			: StatementMixin<StatementKind::SemiExpression>(loc) {
	}

	std::string toString() const {
		return "SemiExpressionStatement";
	}

	ExpressionPtr expr;
};

class EmptyStatement : public StatementMixin<StatementKind::Empty> {
public:
	EmptyStatement(const Location& loc = Location())
			: StatementMixin<StatementKind::Empty>(loc) {
	}

	std::string toString() const {
		return "EmptyStatement";
	}

	ExpressionPtr expr;
};

class LocalStatement : public StatementMixin<StatementKind::Local> {
public:
	LocalStatement(std::string name, const Location& loc = Location())
			: StatementMixin<StatementKind::Local>(loc), id(name), typ(nullptr) {
	}

	std::string toString() const {
		return "LocalStatement";
	}

	Identifier                  id;
	Type*                       typ;
	std::unique_ptr<Expression> init;
};

class BlockExpression;

class Param {
public:
	Param(Identifier id)
			: id(id), typ(nullptr) {
	}
	Identifier id;
	Type*      typ;
};

typedef std::vector<Param> ParamVector;

class FunctionStatement : public StatementMixin<StatementKind::Function> {
public:
	FunctionStatement(std::string name, const Location& loc = Location())
			: StatementMixin<StatementKind::Function>(loc),
				id(name),
				typ(nullptr),
				isPublic(false) {
	}

	std::string toString() const {
		return "FunctionStatement";
	}

	Identifier                       id;
	FunctionType*                    typ;
	std::unique_ptr<BlockExpression> body;
	ParamVector                      params;
	bool                             isPublic;
};

// Expression

enum class ExpressionKind {
	Array,
	Binary,
	Block,
	Break,
	Call,
	Continue,
	For,
	If,
	Literal,
	Match,
	New,
	Path,
	Return,
	Unary,
	Update,
	While,
};

class Expression : public ASTNode {
public:
	Expression()          = delete;
	virtual ~Expression() = default;

	ExpressionKind kind() const {
		return kind_;
	}

	std::string toString() const {
		return "Expression";
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

	std::string toString() const {
		return "ExpressionMixin";
	}
};

enum class BinaryOperator {
	Plus,
	Minus,
	Mult,
	Div,
	BitwiseAnd,
	BitwiseOr,
	Eq,
	Neq,
	GT,
	GE,
	LT,
	LE,
};

class BinaryExpression : public ExpressionMixin<ExpressionKind::Binary> {
public:
	BinaryExpression(BinaryOperator op, const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Binary>(loc), op(op) {
	}

	std::string toString() const {
		return "BinaryExpression";
	}

	BinaryOperator op;
	ExpressionPtr  left;
	ExpressionPtr  right;
};

class CallExpression : public ExpressionMixin<ExpressionKind::Call> {
public:
	CallExpression(const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Call>(loc) {
	}

	std::string toString() const {
		return "CallExpression";
	}

	ExpressionPtr    receiver;
	ExpressionPtr    method;
	ExpressionVector params;
};

class LiteralExpression : public ExpressionMixin<ExpressionKind::Literal> {
public:
	LiteralExpression(int32_t value, const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Literal>(loc), i32val(value), typ(LiteralExpression::Typ::I32) {
	}

	LiteralExpression(std::string value, const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Literal>(loc), strval(value), typ(LiteralExpression::Typ::String) {
	}

	LiteralExpression(int64_t value, const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Literal>(loc), i64val(value), typ(LiteralExpression::Typ::I64) {
	}

	LiteralExpression(double value, const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Literal>(loc), f64val(value), typ(LiteralExpression::Typ::F64) {
	}

	~LiteralExpression() {
	}

	std::string toString() const {
		return "LiteralExpression";
	}

	enum Typ {
		I32,
		I64,
		F32,
		F64,
		String
	};

	Typ typ;

	union {
		int32_t     i32val;
		int64_t     i64val;
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

	std::string toString() const {
		return "PathExpression";
	}

	Identifier id;
};

class BlockExpression : public ExpressionMixin<ExpressionKind::Block> {
public:
	BlockExpression(const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Block>(loc) {
	}

	std::string toString() const {
		return "BlockExpression";
	}

	StatementVector stmts;
};

// Like Expression, but Bool type
typedef Expression ConditionExpression;
// BlockExpresson or IfExpression
typedef Expression ElseExpression;

class IfExpression : public ExpressionMixin<ExpressionKind::If> {
public:
	IfExpression(const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::If>(loc) {
	}

	std::string toString() const {
		return "IfExpression";
	}

	std::unique_ptr<ConditionExpression> condition;
	std::unique_ptr<BlockExpression>     then_branch;
	std::unique_ptr<ElseExpression>      else_branch;
};

class WhileExpression : public ExpressionMixin<ExpressionKind::While> {
	WhileExpression(const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::While>(loc) {
	}

	std::string toString() const {
		return "WhileExpression";
	}

	std::unique_ptr<ConditionExpression> condition;
	std::unique_ptr<BlockExpression>     body;
};

// class ForExpression : public ExpressionMixin<ExpressionKind::For> {
// 	ForExpression(const Location& loc = Location())
// 			: ExpressionMixin<ExpressionKind::For>(loc) {
// 	}

// 	std::string toString() const {
// 		return "ForExpression";
// 	}

// 	ExpressionPtr                   pattern;
// 	ExpressionPtr                   range;
// 	std::unique_ptr<BlockExpression> body;
// };

class BreakExpression : public ExpressionMixin<ExpressionKind::Break> {
	BreakExpression(const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Break>(loc) {
	}

	std::string toString() const {
		return "BreakExpression";
	}

	ExpressionPtr value;
};

class ContinueExpression : public ExpressionMixin<ExpressionKind::Continue> {
	ContinueExpression(const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Continue>(loc) {
	}

	std::string toString() const {
		return "ContinueExpression";
	}
};

class ReturnExpression : public ExpressionMixin<ExpressionKind::Return> {
	ReturnExpression(const Location& loc = Location())
			: ExpressionMixin<ExpressionKind::Return>(loc) {
	}

	std::string toString() const {
		return "ReturnExpression";
	}

	ExpressionPtr value;
};

} // namespace internal
} // namespace dp
