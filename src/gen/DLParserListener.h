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


// Generated from DLParser.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "DLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by DLParser.
 */
class  DLParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterExp(DLParser::ExpContext *ctx) = 0;
  virtual void exitExp(DLParser::ExpContext *ctx) = 0;

  virtual void enterExpPost(DLParser::ExpPostContext *ctx) = 0;
  virtual void exitExpPost(DLParser::ExpPostContext *ctx) = 0;

  virtual void enterAryOp(DLParser::AryOpContext *ctx) = 0;
  virtual void exitAryOp(DLParser::AryOpContext *ctx) = 0;

  virtual void enterUnAryOp(DLParser::UnAryOpContext *ctx) = 0;
  virtual void exitUnAryOp(DLParser::UnAryOpContext *ctx) = 0;

  virtual void enterNewExp(DLParser::NewExpContext *ctx) = 0;
  virtual void exitNewExp(DLParser::NewExpContext *ctx) = 0;

  virtual void enterExpList(DLParser::ExpListContext *ctx) = 0;
  virtual void exitExpList(DLParser::ExpListContext *ctx) = 0;

  virtual void enterStatement(DLParser::StatementContext *ctx) = 0;
  virtual void exitStatement(DLParser::StatementContext *ctx) = 0;

  virtual void enterCompoundBlock(DLParser::CompoundBlockContext *ctx) = 0;
  virtual void exitCompoundBlock(DLParser::CompoundBlockContext *ctx) = 0;

  virtual void enterBlockList(DLParser::BlockListContext *ctx) = 0;
  virtual void exitBlockList(DLParser::BlockListContext *ctx) = 0;

  virtual void enterJumpStatement(DLParser::JumpStatementContext *ctx) = 0;
  virtual void exitJumpStatement(DLParser::JumpStatementContext *ctx) = 0;

  virtual void enterType(DLParser::TypeContext *ctx) = 0;
  virtual void exitType(DLParser::TypeContext *ctx) = 0;

  virtual void enterTypeTail(DLParser::TypeTailContext *ctx) = 0;
  virtual void exitTypeTail(DLParser::TypeTailContext *ctx) = 0;

  virtual void enterFunctionType(DLParser::FunctionTypeContext *ctx) = 0;
  virtual void exitFunctionType(DLParser::FunctionTypeContext *ctx) = 0;

  virtual void enterRefType(DLParser::RefTypeContext *ctx) = 0;
  virtual void exitRefType(DLParser::RefTypeContext *ctx) = 0;

  virtual void enterDecl(DLParser::DeclContext *ctx) = 0;
  virtual void exitDecl(DLParser::DeclContext *ctx) = 0;

  virtual void enterFunctionDecl(DLParser::FunctionDeclContext *ctx) = 0;
  virtual void exitFunctionDecl(DLParser::FunctionDeclContext *ctx) = 0;

  virtual void enterSignature(DLParser::SignatureContext *ctx) = 0;
  virtual void exitSignature(DLParser::SignatureContext *ctx) = 0;

  virtual void enterFunctionDef(DLParser::FunctionDefContext *ctx) = 0;
  virtual void exitFunctionDef(DLParser::FunctionDefContext *ctx) = 0;

  virtual void enterParamList(DLParser::ParamListContext *ctx) = 0;
  virtual void exitParamList(DLParser::ParamListContext *ctx) = 0;

  virtual void enterVarDecl(DLParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(DLParser::VarDeclContext *ctx) = 0;

  virtual void enterClassDecl(DLParser::ClassDeclContext *ctx) = 0;
  virtual void exitClassDecl(DLParser::ClassDeclContext *ctx) = 0;

  virtual void enterClassHead(DLParser::ClassHeadContext *ctx) = 0;
  virtual void exitClassHead(DLParser::ClassHeadContext *ctx) = 0;

  virtual void enterClassBody(DLParser::ClassBodyContext *ctx) = 0;
  virtual void exitClassBody(DLParser::ClassBodyContext *ctx) = 0;

  virtual void enterConstructor(DLParser::ConstructorContext *ctx) = 0;
  virtual void exitConstructor(DLParser::ConstructorContext *ctx) = 0;

  virtual void enterAccessSpecifier(DLParser::AccessSpecifierContext *ctx) = 0;
  virtual void exitAccessSpecifier(DLParser::AccessSpecifierContext *ctx) = 0;

  virtual void enterInterfaceList(DLParser::InterfaceListContext *ctx) = 0;
  virtual void exitInterfaceList(DLParser::InterfaceListContext *ctx) = 0;

  virtual void enterInterfaceDecl(DLParser::InterfaceDeclContext *ctx) = 0;
  virtual void exitInterfaceDecl(DLParser::InterfaceDeclContext *ctx) = 0;

  virtual void enterInterfaceHead(DLParser::InterfaceHeadContext *ctx) = 0;
  virtual void exitInterfaceHead(DLParser::InterfaceHeadContext *ctx) = 0;

  virtual void enterInterfaceBody(DLParser::InterfaceBodyContext *ctx) = 0;
  virtual void exitInterfaceBody(DLParser::InterfaceBodyContext *ctx) = 0;

  virtual void enterProgram(DLParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(DLParser::ProgramContext *ctx) = 0;


};

