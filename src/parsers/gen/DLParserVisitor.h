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


// Generated from F:/Orga/deepLang\DLParser.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "DLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by DLParser.
 */
class PARSERS_PUBLIC_TYPE DLParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by DLParser.
   */
    virtual antlrcpp::Any visitExp(DLParser::ExpContext *context) = 0;

    virtual antlrcpp::Any visitArrayExp(DLParser::ArrayExpContext *context) = 0;

    virtual antlrcpp::Any visitArrayAccessExp(DLParser::ArrayAccessExpContext *context) = 0;

    virtual antlrcpp::Any visitArrayPatternMatchExp(DLParser::ArrayPatternMatchExpContext *context) = 0;

    virtual antlrcpp::Any visitCallExp(DLParser::CallExpContext *context) = 0;

    virtual antlrcpp::Any visitPointExp(DLParser::PointExpContext *context) = 0;

    virtual antlrcpp::Any visitOpExp(DLParser::OpExpContext *context) = 0;

    virtual antlrcpp::Any visitAryOp(DLParser::AryOpContext *context) = 0;

    virtual antlrcpp::Any visitUnAryOp(DLParser::UnAryOpContext *context) = 0;

    virtual antlrcpp::Any visitNewExp(DLParser::NewExpContext *context) = 0;

    virtual antlrcpp::Any visitExpList(DLParser::ExpListContext *context) = 0;

    virtual antlrcpp::Any visitStatement(DLParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitCompoundBlock(DLParser::CompoundBlockContext *context) = 0;

    virtual antlrcpp::Any visitBlockList(DLParser::BlockListContext *context) = 0;

    virtual antlrcpp::Any visitJumpStatement(DLParser::JumpStatementContext *context) = 0;

    virtual antlrcpp::Any visitType(DLParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitFunctionType(DLParser::FunctionTypeContext *context) = 0;

    virtual antlrcpp::Any visitRefType(DLParser::RefTypeContext *context) = 0;

    virtual antlrcpp::Any visitDecl(DLParser::DeclContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDecl(DLParser::FunctionDeclContext *context) = 0;

    virtual antlrcpp::Any visitSignature(DLParser::SignatureContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDef(DLParser::FunctionDefContext *context) = 0;

    virtual antlrcpp::Any visitParamList(DLParser::ParamListContext *context) = 0;

    virtual antlrcpp::Any visitVarDecl(DLParser::VarDeclContext *context) = 0;

    virtual antlrcpp::Any visitClassDecl(DLParser::ClassDeclContext *context) = 0;

    virtual antlrcpp::Any visitClassHead(DLParser::ClassHeadContext *context) = 0;

    virtual antlrcpp::Any visitClassBody(DLParser::ClassBodyContext *context) = 0;

    virtual antlrcpp::Any visitConstructor(DLParser::ConstructorContext *context) = 0;

    virtual antlrcpp::Any visitAccessSpecifier(DLParser::AccessSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitInterfaceList(DLParser::InterfaceListContext *context) = 0;

    virtual antlrcpp::Any visitInterfaceDecl(DLParser::InterfaceDeclContext *context) = 0;

    virtual antlrcpp::Any visitInterfaceHead(DLParser::InterfaceHeadContext *context) = 0;

    virtual antlrcpp::Any visitInterfaceBody(DLParser::InterfaceBodyContext *context) = 0;

    virtual antlrcpp::Any visitProgram(DLParser::ProgramContext *context) = 0;


};

