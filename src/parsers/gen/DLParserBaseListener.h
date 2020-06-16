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
#include "DLParserListener.h"


/**
 * This class provides an empty implementation of DLParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class PARSERS_PUBLIC_TYPE DLParserBaseListener : public DLParserListener {
public:

  virtual void enterExp(DLParser::ExpContext * /*ctx*/) override { }
  virtual void exitExp(DLParser::ExpContext * /*ctx*/) override { }

  virtual void enterArrayExp(DLParser::ArrayExpContext * /*ctx*/) override { }
  virtual void exitArrayExp(DLParser::ArrayExpContext * /*ctx*/) override { }

  virtual void enterArrayAccessExp(DLParser::ArrayAccessExpContext * /*ctx*/) override { }
  virtual void exitArrayAccessExp(DLParser::ArrayAccessExpContext * /*ctx*/) override { }

  virtual void enterArrayPatternMatchExp(DLParser::ArrayPatternMatchExpContext * /*ctx*/) override { }
  virtual void exitArrayPatternMatchExp(DLParser::ArrayPatternMatchExpContext * /*ctx*/) override { }

  virtual void enterCallExp(DLParser::CallExpContext * /*ctx*/) override { }
  virtual void exitCallExp(DLParser::CallExpContext * /*ctx*/) override { }

  virtual void enterPointExp(DLParser::PointExpContext * /*ctx*/) override { }
  virtual void exitPointExp(DLParser::PointExpContext * /*ctx*/) override { }

  virtual void enterOpExp(DLParser::OpExpContext * /*ctx*/) override { }
  virtual void exitOpExp(DLParser::OpExpContext * /*ctx*/) override { }

  virtual void enterAryOp(DLParser::AryOpContext * /*ctx*/) override { }
  virtual void exitAryOp(DLParser::AryOpContext * /*ctx*/) override { }

  virtual void enterUnAryOp(DLParser::UnAryOpContext * /*ctx*/) override { }
  virtual void exitUnAryOp(DLParser::UnAryOpContext * /*ctx*/) override { }

  virtual void enterNewExp(DLParser::NewExpContext * /*ctx*/) override { }
  virtual void exitNewExp(DLParser::NewExpContext * /*ctx*/) override { }

  virtual void enterExpList(DLParser::ExpListContext * /*ctx*/) override { }
  virtual void exitExpList(DLParser::ExpListContext * /*ctx*/) override { }

  virtual void enterStatement(DLParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(DLParser::StatementContext * /*ctx*/) override { }

  virtual void enterCompoundBlock(DLParser::CompoundBlockContext * /*ctx*/) override { }
  virtual void exitCompoundBlock(DLParser::CompoundBlockContext * /*ctx*/) override { }

  virtual void enterBlockList(DLParser::BlockListContext * /*ctx*/) override { }
  virtual void exitBlockList(DLParser::BlockListContext * /*ctx*/) override { }

  virtual void enterJumpStatement(DLParser::JumpStatementContext * /*ctx*/) override { }
  virtual void exitJumpStatement(DLParser::JumpStatementContext * /*ctx*/) override { }

  virtual void enterType(DLParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(DLParser::TypeContext * /*ctx*/) override { }

  virtual void enterFunctionType(DLParser::FunctionTypeContext * /*ctx*/) override { }
  virtual void exitFunctionType(DLParser::FunctionTypeContext * /*ctx*/) override { }

  virtual void enterRefType(DLParser::RefTypeContext * /*ctx*/) override { }
  virtual void exitRefType(DLParser::RefTypeContext * /*ctx*/) override { }

  virtual void enterDecl(DLParser::DeclContext * /*ctx*/) override { }
  virtual void exitDecl(DLParser::DeclContext * /*ctx*/) override { }

  virtual void enterFunctionDecl(DLParser::FunctionDeclContext * /*ctx*/) override { }
  virtual void exitFunctionDecl(DLParser::FunctionDeclContext * /*ctx*/) override { }

  virtual void enterSignature(DLParser::SignatureContext * /*ctx*/) override { }
  virtual void exitSignature(DLParser::SignatureContext * /*ctx*/) override { }

  virtual void enterFunctionDef(DLParser::FunctionDefContext * /*ctx*/) override { }
  virtual void exitFunctionDef(DLParser::FunctionDefContext * /*ctx*/) override { }

  virtual void enterParamList(DLParser::ParamListContext * /*ctx*/) override { }
  virtual void exitParamList(DLParser::ParamListContext * /*ctx*/) override { }

  virtual void enterVarDecl(DLParser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(DLParser::VarDeclContext * /*ctx*/) override { }

  virtual void enterClassDecl(DLParser::ClassDeclContext * /*ctx*/) override { }
  virtual void exitClassDecl(DLParser::ClassDeclContext * /*ctx*/) override { }

  virtual void enterClassHead(DLParser::ClassHeadContext * /*ctx*/) override { }
  virtual void exitClassHead(DLParser::ClassHeadContext * /*ctx*/) override { }

  virtual void enterClassBody(DLParser::ClassBodyContext * /*ctx*/) override { }
  virtual void exitClassBody(DLParser::ClassBodyContext * /*ctx*/) override { }

  virtual void enterConstructor(DLParser::ConstructorContext * /*ctx*/) override { }
  virtual void exitConstructor(DLParser::ConstructorContext * /*ctx*/) override { }

  virtual void enterAccessSpecifier(DLParser::AccessSpecifierContext * /*ctx*/) override { }
  virtual void exitAccessSpecifier(DLParser::AccessSpecifierContext * /*ctx*/) override { }

  virtual void enterInterfaceList(DLParser::InterfaceListContext * /*ctx*/) override { }
  virtual void exitInterfaceList(DLParser::InterfaceListContext * /*ctx*/) override { }

  virtual void enterInterfaceDecl(DLParser::InterfaceDeclContext * /*ctx*/) override { }
  virtual void exitInterfaceDecl(DLParser::InterfaceDeclContext * /*ctx*/) override { }

  virtual void enterInterfaceHead(DLParser::InterfaceHeadContext * /*ctx*/) override { }
  virtual void exitInterfaceHead(DLParser::InterfaceHeadContext * /*ctx*/) override { }

  virtual void enterInterfaceBody(DLParser::InterfaceBodyContext * /*ctx*/) override { }
  virtual void exitInterfaceBody(DLParser::InterfaceBodyContext * /*ctx*/) override { }

  virtual void enterProgram(DLParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(DLParser::ProgramContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

