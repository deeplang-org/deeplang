/*
 * Copyright (c) 2018, 2019, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2.0,
 * as published by the Free Software Foundation.
 *
 * This program is also distributed with certain software (including
 * but not limited to OpenSSL) that is licensed under separate terms, as
 * designated in a particular file or component or in included license
 * documentation. The authors of MySQL hereby grant you an additional
 * permission to link the program and your derivative works with the
 * separately licensed software that they have included with MySQL.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License, version 2.0, for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */


// Generated from src/parsing/DLParser.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "DLParserListener.h"


/**
 * This class provides an empty implementation of DLParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  DLParserBaseListener : public DLParserListener {
public:

  virtual void enterAryOp(DLParser::AryOpContext * /*ctx*/) override { }
  virtual void exitAryOp(DLParser::AryOpContext * /*ctx*/) override { }

  virtual void enterExpressionList(DLParser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(DLParser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(DLParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(DLParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterBlockExpression(DLParser::BlockExpressionContext * /*ctx*/) override { }
  virtual void exitBlockExpression(DLParser::BlockExpressionContext * /*ctx*/) override { }

  virtual void enterUnblockExpression(DLParser::UnblockExpressionContext * /*ctx*/) override { }
  virtual void exitUnblockExpression(DLParser::UnblockExpressionContext * /*ctx*/) override { }

  virtual void enterTupleType(DLParser::TupleTypeContext * /*ctx*/) override { }
  virtual void exitTupleType(DLParser::TupleTypeContext * /*ctx*/) override { }

  virtual void enterType(DLParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(DLParser::TypeContext * /*ctx*/) override { }

  virtual void enterVariableDecl(DLParser::VariableDeclContext * /*ctx*/) override { }
  virtual void exitVariableDecl(DLParser::VariableDeclContext * /*ctx*/) override { }

  virtual void enterParam(DLParser::ParamContext * /*ctx*/) override { }
  virtual void exitParam(DLParser::ParamContext * /*ctx*/) override { }

  virtual void enterParamList(DLParser::ParamListContext * /*ctx*/) override { }
  virtual void exitParamList(DLParser::ParamListContext * /*ctx*/) override { }

  virtual void enterFunctionDecl(DLParser::FunctionDeclContext * /*ctx*/) override { }
  virtual void exitFunctionDecl(DLParser::FunctionDeclContext * /*ctx*/) override { }

  virtual void enterDecl(DLParser::DeclContext * /*ctx*/) override { }
  virtual void exitDecl(DLParser::DeclContext * /*ctx*/) override { }

  virtual void enterCondition(DLParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(DLParser::ConditionContext * /*ctx*/) override { }

  virtual void enterConditionElem(DLParser::ConditionElemContext * /*ctx*/) override { }
  virtual void exitConditionElem(DLParser::ConditionElemContext * /*ctx*/) override { }

  virtual void enterConditionStmt(DLParser::ConditionStmtContext * /*ctx*/) override { }
  virtual void exitConditionStmt(DLParser::ConditionStmtContext * /*ctx*/) override { }

  virtual void enterStatement(DLParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(DLParser::StatementContext * /*ctx*/) override { }

  virtual void enterStatements(DLParser::StatementsContext * /*ctx*/) override { }
  virtual void exitStatements(DLParser::StatementsContext * /*ctx*/) override { }

  virtual void enterModule(DLParser::ModuleContext * /*ctx*/) override { }
  virtual void exitModule(DLParser::ModuleContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

