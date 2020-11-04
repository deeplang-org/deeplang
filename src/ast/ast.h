#pragma once
#include "../common.h"
#include "type.h"
#include "../utils/error.h"

namespace dp {
    namespace internal {

        /******************************************* ASTNode***************/
        class ASTNode {
            public:
                ASTNode(const Location& loc = Location()) 
                    : loc(loc) {}
                ~ASTNode() {}
                std::string toString() const;
                Location loc;
        };

        class Identifier {
            public:
                Identifier(const std::string& name)
                    : name(name) {}
                ~Identifier() {}
                std::string toString() const {
                    return "Identifier";
                }
                std::string name;
        };



        /******************************************* Statement ***************/
        enum class StatementKind {
            VariableDeclaration,
            FunctionDeclaration,
            ExpressionStatement,
        };

        class Statement : public ASTNode {
            public:
                Statement() = delete;
                virtual ~Statement() = default;

                StatementKind kind() const {
                    return kind_;
                }

                std::string toString() const {
                    return "Statement";
                }

            protected:
                explicit Statement(StatementKind kind, const Location& loc = Location())
                    : ASTNode(loc), kind_(kind) {}

                StatementKind kind_;
        };
        typedef std::unique_ptr<Statement> StatementPtr;
        typedef std::vector<StatementPtr>  StatementVector;

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
                        : Statement(Kind, loc) {}
            };

        class Expression;
        typedef std::unique_ptr<Expression> ExpressionPtr;
        typedef std::vector<ExpressionPtr>  ExpressionVector;
        enum class ExpressionStatementKind {
            Normal,
            Condition,

        };

        class ExpressionStatement : public StatementMixin<StatementKind::ExpressionStatement> {
            public:
                ExpressionStatement(ExpressionStatementKind kind = ExpressionStatementKind::Normal, const Location& loc = Location()) 
                    : StatementMixin<StatementKind::ExpressionStatement>(loc), esKind(kind){}

                //ExpressionStatement() = delete;
                std::string toString() const {
                    return "ExpressionStatement";
                }
                ExpressionPtr expr;
                ExpressionStatementKind esKind;
        };

        class VariableDeclaration : public StatementMixin<StatementKind::VariableDeclaration> {
            public:
                VariableDeclaration(std::string name, const Location& loc = Location())
                    : StatementMixin<StatementKind::VariableDeclaration>(loc), id(name) {
                    }
                ~VariableDeclaration() {
                }

                std::string toString() const {
                    return "VariableDeclaration";
                }

                Identifier                  id;
                std::unique_ptr<Type>       vartype;
                std::unique_ptr<Expression> init;
        };

        class Param {
            public:
                Param(Identifier id)
                    : id(id) {
                    }
                Identifier            id;
                std::unique_ptr<Type> typ;
        };

        typedef std::unique_ptr<Param> ParamPtr;
        typedef std::vector<ParamPtr>  ParamVector;

        class FunctionDeclaration : public StatementMixin<StatementKind::FunctionDeclaration> {
            public:
                FunctionDeclaration(std::string name, const Location& loc = Location())
                    : StatementMixin<StatementKind::FunctionDeclaration>(loc), id(name), isPublic(true) {
                    }
                ~FunctionDeclaration() {
                }

                std::string toString() const {
                    return "FunctionDeclaration";
                }

                Identifier                           id;
                std::unique_ptr<FunctionType>        signature;
                std::unique_ptr<ExpressionStatement> body;
                ParamVector                          params;
                bool                                 isPublic;
        };



        /******************************************* ExpressionStatement***************/


        template<ExpressionStatementKind esKind>
            class ExpressionStmtMixin : public ExpressionStatement{
                public:
                    explicit ExpressionStmtMixin(const Location& loc = Location())
                        : ExpressionStatement(esKind, loc){}

                    bool isclassof(const ExpressionStatement* es) {
                        return (es->esKind ==  esKind); 
                    } 
                    std::string toString() {
                        return "ExpressionStmtMixin"; 
                    }
            };

        

        struct ConditionElem;
        class ConditionExStmt : public ExpressionStmtMixin<ExpressionStatementKind::Condition>{
            public:
                 ConditionExStmt(const Location &loc = Location())  
                    : ExpressionStmtMixin<ExpressionStatementKind::Condition>(loc){}       

            ConditionElem* cond = nullptr;
            ExpressionPtr lcond;
        };
        struct  ConditionElem
        {
            ConditionExStmt* lexpressionstmt;  // if part 
            ExpressionPtr rcond;
            ConditionExStmt* rexpressionstmt;   // else part


            ConditionElem* condElem;

        };       


        /******************************************* Expression***************/

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

            Equal,  // ==
            NE,     // !=
            GT,     // >
            GE,     // >=
            LE,     // <=
            LT,     // <
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

        class BlockExpession : public ExpressionMixin<ExpressionKind::Block> {
            public:
                BlockExpession(const Location& loc = Location())
                    : ExpressionMixin<ExpressionKind::Block>(loc) {
                    }

                std::string toString() const {
                    return "BlockExpession";
                }

                StatementVector stmts;
        };



        /******************************************* Module***************/
        class Module : public ASTNode {
            public:
                Module(std::string name, const Location& loc = Location())
                    : ASTNode(loc), id(name) {
                    }
                ~Module() {
                }

                std::string toString() const {
                    return "Module";
                }

                Identifier      id;
                StatementVector stmts;
        };
        typedef std::unique_ptr<Module> ModulePtr;


    } 
} 
