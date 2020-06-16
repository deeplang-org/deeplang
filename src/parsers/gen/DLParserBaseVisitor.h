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
#include "DLParserVisitor.h"


/**
 * This class provides an empty implementation of DLParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class PARSERS_PUBLIC_TYPE DLParserBaseVisitor : public DLParserVisitor {
public:

  virtual antlrcpp::Any visitExp(DLParser::ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayExp(DLParser::ArrayExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayAccessExp(DLParser::ArrayAccessExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayPatternMatchExp(DLParser::ArrayPatternMatchExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCallExp(DLParser::CallExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPointExp(DLParser::PointExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOpExp(DLParser::OpExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAryOp(DLParser::AryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnAryOp(DLParser::UnAryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNewExp(DLParser::NewExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpList(DLParser::ExpListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(DLParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompoundBlock(DLParser::CompoundBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlockList(DLParser::BlockListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitJumpStatement(DLParser::JumpStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(DLParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionType(DLParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRefType(DLParser::RefTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecl(DLParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDecl(DLParser::FunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSignature(DLParser::SignatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDef(DLParser::FunctionDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParamList(DLParser::ParamListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDecl(DLParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassDecl(DLParser::ClassDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassHead(DLParser::ClassHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassBody(DLParser::ClassBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstructor(DLParser::ConstructorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAccessSpecifier(DLParser::AccessSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterfaceList(DLParser::InterfaceListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterfaceDecl(DLParser::InterfaceDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterfaceHead(DLParser::InterfaceHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterfaceBody(DLParser::InterfaceBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProgram(DLParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }


};

