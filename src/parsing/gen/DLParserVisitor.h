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
 * This class defines an abstract visitor for a parse tree
 * produced by DLParser.
 */
class  DLParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by DLParser.
   */
    virtual antlrcpp::Any visitAryOp(DLParser::AryOpContext *context) = 0;

    virtual antlrcpp::Any visitExpressionList(DLParser::ExpressionListContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(DLParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitBlockExpression(DLParser::BlockExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnblockExpression(DLParser::UnblockExpressionContext *context) = 0;

    virtual antlrcpp::Any visitIfExpression(DLParser::IfExpressionContext *context) = 0;

    virtual antlrcpp::Any visitConditionElem(DLParser::ConditionElemContext *context) = 0;

    virtual antlrcpp::Any visitTupleType(DLParser::TupleTypeContext *context) = 0;

    virtual antlrcpp::Any visitType(DLParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitVariableDecl(DLParser::VariableDeclContext *context) = 0;

    virtual antlrcpp::Any visitParam(DLParser::ParamContext *context) = 0;

    virtual antlrcpp::Any visitParamList(DLParser::ParamListContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDecl(DLParser::FunctionDeclContext *context) = 0;

    virtual antlrcpp::Any visitDecl(DLParser::DeclContext *context) = 0;

    virtual antlrcpp::Any visitStatement(DLParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitStatements(DLParser::StatementsContext *context) = 0;

    virtual antlrcpp::Any visitModule(DLParser::ModuleContext *context) = 0;


};

