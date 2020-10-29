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
#include "DLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by DLParser.
 */
class  DLParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterAryOp(DLParser::AryOpContext *ctx) = 0;
  virtual void exitAryOp(DLParser::AryOpContext *ctx) = 0;

  virtual void enterExpressionList(DLParser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(DLParser::ExpressionListContext *ctx) = 0;

  virtual void enterExpressionStatement(DLParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(DLParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterBlockExpression(DLParser::BlockExpressionContext *ctx) = 0;
  virtual void exitBlockExpression(DLParser::BlockExpressionContext *ctx) = 0;

  virtual void enterUnblockExpression(DLParser::UnblockExpressionContext *ctx) = 0;
  virtual void exitUnblockExpression(DLParser::UnblockExpressionContext *ctx) = 0;

  virtual void enterTupleType(DLParser::TupleTypeContext *ctx) = 0;
  virtual void exitTupleType(DLParser::TupleTypeContext *ctx) = 0;

  virtual void enterType(DLParser::TypeContext *ctx) = 0;
  virtual void exitType(DLParser::TypeContext *ctx) = 0;

  virtual void enterVariableDecl(DLParser::VariableDeclContext *ctx) = 0;
  virtual void exitVariableDecl(DLParser::VariableDeclContext *ctx) = 0;

  virtual void enterParam(DLParser::ParamContext *ctx) = 0;
  virtual void exitParam(DLParser::ParamContext *ctx) = 0;

  virtual void enterParamList(DLParser::ParamListContext *ctx) = 0;
  virtual void exitParamList(DLParser::ParamListContext *ctx) = 0;

  virtual void enterFunctionDecl(DLParser::FunctionDeclContext *ctx) = 0;
  virtual void exitFunctionDecl(DLParser::FunctionDeclContext *ctx) = 0;

  virtual void enterDecl(DLParser::DeclContext *ctx) = 0;
  virtual void exitDecl(DLParser::DeclContext *ctx) = 0;

  virtual void enterStatement(DLParser::StatementContext *ctx) = 0;
  virtual void exitStatement(DLParser::StatementContext *ctx) = 0;

  virtual void enterStatements(DLParser::StatementsContext *ctx) = 0;
  virtual void exitStatements(DLParser::StatementsContext *ctx) = 0;

  virtual void enterModule(DLParser::ModuleContext *ctx) = 0;
  virtual void exitModule(DLParser::ModuleContext *ctx) = 0;


};

