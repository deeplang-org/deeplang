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


#include "DLParserListener.h"
#include "DLParserVisitor.h"

#include "DLParser.h"




using namespace antlrcpp;
using namespace antlr4;

DLParser::DLParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

DLParser::~DLParser() {
  delete _interpreter;
}

std::string DLParser::getGrammarFileName() const {
  return "DLParser.g4";
}

const std::vector<std::string>& DLParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& DLParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ExpContext ------------------------------------------------------------------

DLParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::ExpContext::CONST() {
  return getToken(DLParser::CONST, 0);
}

DLParser::ExpPostContext* DLParser::ExpContext::expPost() {
  return getRuleContext<DLParser::ExpPostContext>(0);
}

tree::TerminalNode* DLParser::ExpContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::ExpContext::QUOTED_STRING() {
  return getToken(DLParser::QUOTED_STRING, 0);
}

tree::TerminalNode* DLParser::ExpContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

DLParser::ExpContext* DLParser::ExpContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}

tree::TerminalNode* DLParser::ExpContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}

DLParser::UnAryOpContext* DLParser::ExpContext::unAryOp() {
  return getRuleContext<DLParser::UnAryOpContext>(0);
}

DLParser::NewExpContext* DLParser::ExpContext::newExp() {
  return getRuleContext<DLParser::NewExpContext>(0);
}


size_t DLParser::ExpContext::getRuleIndex() const {
  return DLParser::RuleExp;
}

void DLParser::ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExp(this);
}

void DLParser::ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExp(this);
}


antlrcpp::Any DLParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ExpContext* DLParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 0, DLParser::RuleExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(78);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(60);
        match(DLParser::CONST);
        setState(61);
        expPost();
        break;
      }

      case DLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(62);
        match(DLParser::IDENTIFIER);
        setState(63);
        expPost();
        break;
      }

      case DLParser::QUOTED_STRING: {
        enterOuterAlt(_localctx, 3);
        setState(64);
        match(DLParser::QUOTED_STRING);
        setState(65);
        expPost();
        break;
      }

      case DLParser::OPEN_PAR_SYMBOL: {
        enterOuterAlt(_localctx, 4);
        setState(66);
        match(DLParser::OPEN_PAR_SYMBOL);
        setState(67);
        exp();
        setState(68);
        match(DLParser::CLOSE_PAR_SYMBOL);
        setState(69);
        expPost();
        break;
      }

      case DLParser::LOGICAL_NOT_OPERATOR:
      case DLParser::BITWISE_NOT_OPERATOR:
      case DLParser::BITWISE_AND_OPERATOR: {
        enterOuterAlt(_localctx, 5);
        setState(71);
        unAryOp();
        setState(72);
        exp();
        setState(73);
        expPost();
        break;
      }

      case DLParser::NEW_SYMBOL: {
        enterOuterAlt(_localctx, 6);
        setState(75);
        newExp();
        setState(76);
        expPost();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpPostContext ------------------------------------------------------------------

DLParser::ExpPostContext::ExpPostContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::ExpPostContext::OPEN_SQUARE_SYMBOL() {
  return getToken(DLParser::OPEN_SQUARE_SYMBOL, 0);
}

DLParser::ExpListContext* DLParser::ExpPostContext::expList() {
  return getRuleContext<DLParser::ExpListContext>(0);
}

tree::TerminalNode* DLParser::ExpPostContext::CLOSE_SQUARE_SYMBOL() {
  return getToken(DLParser::CLOSE_SQUARE_SYMBOL, 0);
}

DLParser::ExpPostContext* DLParser::ExpPostContext::expPost() {
  return getRuleContext<DLParser::ExpPostContext>(0);
}

DLParser::ExpContext* DLParser::ExpPostContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}

tree::TerminalNode* DLParser::ExpPostContext::AT_SIGN_SYMBOL() {
  return getToken(DLParser::AT_SIGN_SYMBOL, 0);
}

tree::TerminalNode* DLParser::ExpPostContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::ExpPostContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

tree::TerminalNode* DLParser::ExpPostContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}

tree::TerminalNode* DLParser::ExpPostContext::DOT_SYMBOL() {
  return getToken(DLParser::DOT_SYMBOL, 0);
}

DLParser::AryOpContext* DLParser::ExpPostContext::aryOp() {
  return getRuleContext<DLParser::AryOpContext>(0);
}


size_t DLParser::ExpPostContext::getRuleIndex() const {
  return DLParser::RuleExpPost;
}

void DLParser::ExpPostContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpPost(this);
}

void DLParser::ExpPostContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpPost(this);
}


antlrcpp::Any DLParser::ExpPostContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitExpPost(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ExpPostContext* DLParser::expPost() {
  ExpPostContext *_localctx = _tracker.createInstance<ExpPostContext>(_ctx, getState());
  enterRule(_localctx, 2, DLParser::RuleExpPost);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(116);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(80);
      match(DLParser::OPEN_SQUARE_SYMBOL);
      setState(81);
      expList();
      setState(82);
      match(DLParser::CLOSE_SQUARE_SYMBOL);
      setState(83);
      expPost();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(85);
      match(DLParser::OPEN_SQUARE_SYMBOL);
      setState(86);
      match(DLParser::CLOSE_SQUARE_SYMBOL);
      setState(87);
      expPost();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(88);
      match(DLParser::OPEN_SQUARE_SYMBOL);
      setState(89);
      exp();
      setState(90);
      match(DLParser::CLOSE_SQUARE_SYMBOL);
      setState(91);
      expPost();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(93);
      match(DLParser::AT_SIGN_SYMBOL);
      setState(94);
      match(DLParser::IDENTIFIER);
      setState(95);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(96);
      expList();
      setState(97);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(98);
      expPost();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(100);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(101);
      expList();
      setState(102);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(103);
      expPost();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(105);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(106);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(107);
      expPost();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(108);
      match(DLParser::DOT_SYMBOL);
      setState(109);
      match(DLParser::IDENTIFIER);
      setState(110);
      expPost();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(111);
      aryOp();
      setState(112);
      exp();
      setState(113);
      expPost();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);

      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AryOpContext ------------------------------------------------------------------

DLParser::AryOpContext::AryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::AryOpContext::PLUS_OPERATOR() {
  return getToken(DLParser::PLUS_OPERATOR, 0);
}

tree::TerminalNode* DLParser::AryOpContext::MINUS_OPERATOR() {
  return getToken(DLParser::MINUS_OPERATOR, 0);
}

tree::TerminalNode* DLParser::AryOpContext::MULT_OPERATOR() {
  return getToken(DLParser::MULT_OPERATOR, 0);
}

tree::TerminalNode* DLParser::AryOpContext::DIV_OPERATOR() {
  return getToken(DLParser::DIV_OPERATOR, 0);
}

tree::TerminalNode* DLParser::AryOpContext::MOD_OPERATOR() {
  return getToken(DLParser::MOD_OPERATOR, 0);
}

tree::TerminalNode* DLParser::AryOpContext::ASSIGN_OPERATOR() {
  return getToken(DLParser::ASSIGN_OPERATOR, 0);
}

tree::TerminalNode* DLParser::AryOpContext::EQUAL_OPERATOR() {
  return getToken(DLParser::EQUAL_OPERATOR, 0);
}

tree::TerminalNode* DLParser::AryOpContext::LOGICAL_AND_OPERATOR() {
  return getToken(DLParser::LOGICAL_AND_OPERATOR, 0);
}

tree::TerminalNode* DLParser::AryOpContext::LOGICAL_OR_OPERATOR() {
  return getToken(DLParser::LOGICAL_OR_OPERATOR, 0);
}


size_t DLParser::AryOpContext::getRuleIndex() const {
  return DLParser::RuleAryOp;
}

void DLParser::AryOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAryOp(this);
}

void DLParser::AryOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAryOp(this);
}


antlrcpp::Any DLParser::AryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitAryOp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::AryOpContext* DLParser::aryOp() {
  AryOpContext *_localctx = _tracker.createInstance<AryOpContext>(_ctx, getState());
  enterRule(_localctx, 4, DLParser::RuleAryOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    _la = _input->LA(1);
    if (!(((((_la - 383) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 383)) & ((1ULL << (DLParser::ASSIGN_OPERATOR - 383))
      | (1ULL << (DLParser::EQUAL_OPERATOR - 383))
      | (1ULL << (DLParser::PLUS_OPERATOR - 383))
      | (1ULL << (DLParser::MINUS_OPERATOR - 383))
      | (1ULL << (DLParser::MULT_OPERATOR - 383))
      | (1ULL << (DLParser::DIV_OPERATOR - 383))
      | (1ULL << (DLParser::MOD_OPERATOR - 383))
      | (1ULL << (DLParser::LOGICAL_AND_OPERATOR - 383))
      | (1ULL << (DLParser::LOGICAL_OR_OPERATOR - 383)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnAryOpContext ------------------------------------------------------------------

DLParser::UnAryOpContext::UnAryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::UnAryOpContext::BITWISE_AND_OPERATOR() {
  return getToken(DLParser::BITWISE_AND_OPERATOR, 0);
}

tree::TerminalNode* DLParser::UnAryOpContext::LOGICAL_NOT_OPERATOR() {
  return getToken(DLParser::LOGICAL_NOT_OPERATOR, 0);
}

tree::TerminalNode* DLParser::UnAryOpContext::BITWISE_NOT_OPERATOR() {
  return getToken(DLParser::BITWISE_NOT_OPERATOR, 0);
}


size_t DLParser::UnAryOpContext::getRuleIndex() const {
  return DLParser::RuleUnAryOp;
}

void DLParser::UnAryOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnAryOp(this);
}

void DLParser::UnAryOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnAryOp(this);
}


antlrcpp::Any DLParser::UnAryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitUnAryOp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::UnAryOpContext* DLParser::unAryOp() {
  UnAryOpContext *_localctx = _tracker.createInstance<UnAryOpContext>(_ctx, getState());
  enterRule(_localctx, 6, DLParser::RuleUnAryOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    _la = _input->LA(1);
    if (!(((((_la - 396) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 396)) & ((1ULL << (DLParser::LOGICAL_NOT_OPERATOR - 396))
      | (1ULL << (DLParser::BITWISE_NOT_OPERATOR - 396))
      | (1ULL << (DLParser::BITWISE_AND_OPERATOR - 396)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NewExpContext ------------------------------------------------------------------

DLParser::NewExpContext::NewExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::NewExpContext::NEW_SYMBOL() {
  return getToken(DLParser::NEW_SYMBOL, 0);
}

tree::TerminalNode* DLParser::NewExpContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::NewExpContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

tree::TerminalNode* DLParser::NewExpContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}

DLParser::ExpListContext* DLParser::NewExpContext::expList() {
  return getRuleContext<DLParser::ExpListContext>(0);
}


size_t DLParser::NewExpContext::getRuleIndex() const {
  return DLParser::RuleNewExp;
}

void DLParser::NewExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNewExp(this);
}

void DLParser::NewExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNewExp(this);
}


antlrcpp::Any DLParser::NewExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitNewExp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::NewExpContext* DLParser::newExp() {
  NewExpContext *_localctx = _tracker.createInstance<NewExpContext>(_ctx, getState());
  enterRule(_localctx, 8, DLParser::RuleNewExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(132);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(122);
      match(DLParser::NEW_SYMBOL);
      setState(123);
      match(DLParser::IDENTIFIER);
      setState(124);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(125);
      match(DLParser::CLOSE_PAR_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(126);
      match(DLParser::NEW_SYMBOL);
      setState(127);
      match(DLParser::IDENTIFIER);
      setState(128);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(129);
      expList();
      setState(130);
      match(DLParser::CLOSE_PAR_SYMBOL);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpListContext ------------------------------------------------------------------

DLParser::ExpListContext::ExpListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::ExpContext* DLParser::ExpListContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}

tree::TerminalNode* DLParser::ExpListContext::COMMA_SYMBOL() {
  return getToken(DLParser::COMMA_SYMBOL, 0);
}

DLParser::ExpListContext* DLParser::ExpListContext::expList() {
  return getRuleContext<DLParser::ExpListContext>(0);
}


size_t DLParser::ExpListContext::getRuleIndex() const {
  return DLParser::RuleExpList;
}

void DLParser::ExpListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpList(this);
}

void DLParser::ExpListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpList(this);
}


antlrcpp::Any DLParser::ExpListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitExpList(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ExpListContext* DLParser::expList() {
  ExpListContext *_localctx = _tracker.createInstance<ExpListContext>(_ctx, getState());
  enterRule(_localctx, 10, DLParser::RuleExpList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(139);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(134);
      exp();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(135);
      exp();
      setState(136);
      match(DLParser::COMMA_SYMBOL);
      setState(137);
      expList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

DLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::StatementContext::IF_SYMBOL() {
  return getToken(DLParser::IF_SYMBOL, 0);
}

tree::TerminalNode* DLParser::StatementContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

std::vector<DLParser::ExpContext *> DLParser::StatementContext::exp() {
  return getRuleContexts<DLParser::ExpContext>();
}

DLParser::ExpContext* DLParser::StatementContext::exp(size_t i) {
  return getRuleContext<DLParser::ExpContext>(i);
}

tree::TerminalNode* DLParser::StatementContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}

std::vector<DLParser::CompoundBlockContext *> DLParser::StatementContext::compoundBlock() {
  return getRuleContexts<DLParser::CompoundBlockContext>();
}

DLParser::CompoundBlockContext* DLParser::StatementContext::compoundBlock(size_t i) {
  return getRuleContext<DLParser::CompoundBlockContext>(i);
}

tree::TerminalNode* DLParser::StatementContext::ELSE_SYMBOL() {
  return getToken(DLParser::ELSE_SYMBOL, 0);
}

tree::TerminalNode* DLParser::StatementContext::FOR_SYMBOL() {
  return getToken(DLParser::FOR_SYMBOL, 0);
}

std::vector<tree::TerminalNode *> DLParser::StatementContext::SEMICOLON_SYMBOL() {
  return getTokens(DLParser::SEMICOLON_SYMBOL);
}

tree::TerminalNode* DLParser::StatementContext::SEMICOLON_SYMBOL(size_t i) {
  return getToken(DLParser::SEMICOLON_SYMBOL, i);
}

DLParser::JumpStatementContext* DLParser::StatementContext::jumpStatement() {
  return getRuleContext<DLParser::JumpStatementContext>(0);
}


size_t DLParser::StatementContext::getRuleIndex() const {
  return DLParser::RuleStatement;
}

void DLParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void DLParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


antlrcpp::Any DLParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

DLParser::StatementContext* DLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 12, DLParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(166);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(141);
      match(DLParser::IF_SYMBOL);
      setState(142);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(143);
      exp();
      setState(144);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(145);
      compoundBlock();
      setState(146);
      match(DLParser::ELSE_SYMBOL);
      setState(147);
      compoundBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(149);
      match(DLParser::IF_SYMBOL);
      setState(150);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(151);
      exp();
      setState(152);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(153);
      compoundBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(155);
      match(DLParser::FOR_SYMBOL);
      setState(156);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(157);
      compoundBlock();
      setState(158);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(159);
      exp();
      setState(160);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(161);
      exp();
      setState(162);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(163);
      compoundBlock();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(165);
      jumpStatement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompoundBlockContext ------------------------------------------------------------------

DLParser::CompoundBlockContext::CompoundBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::CompoundBlockContext::OPEN_CURLY_SYMBOL() {
  return getToken(DLParser::OPEN_CURLY_SYMBOL, 0);
}

tree::TerminalNode* DLParser::CompoundBlockContext::CLOSE_CURLY_SYMBOL() {
  return getToken(DLParser::CLOSE_CURLY_SYMBOL, 0);
}

DLParser::BlockListContext* DLParser::CompoundBlockContext::blockList() {
  return getRuleContext<DLParser::BlockListContext>(0);
}


size_t DLParser::CompoundBlockContext::getRuleIndex() const {
  return DLParser::RuleCompoundBlock;
}

void DLParser::CompoundBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompoundBlock(this);
}

void DLParser::CompoundBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompoundBlock(this);
}


antlrcpp::Any DLParser::CompoundBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitCompoundBlock(this);
  else
    return visitor->visitChildren(this);
}

DLParser::CompoundBlockContext* DLParser::compoundBlock() {
  CompoundBlockContext *_localctx = _tracker.createInstance<CompoundBlockContext>(_ctx, getState());
  enterRule(_localctx, 14, DLParser::RuleCompoundBlock);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(174);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(168);
      match(DLParser::OPEN_CURLY_SYMBOL);
      setState(169);
      match(DLParser::CLOSE_CURLY_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(170);
      match(DLParser::OPEN_CURLY_SYMBOL);
      setState(171);
      blockList();
      setState(172);
      match(DLParser::CLOSE_CURLY_SYMBOL);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockListContext ------------------------------------------------------------------

DLParser::BlockListContext::BlockListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::StatementContext* DLParser::BlockListContext::statement() {
  return getRuleContext<DLParser::StatementContext>(0);
}

tree::TerminalNode* DLParser::BlockListContext::SEMICOLON_SYMBOL() {
  return getToken(DLParser::SEMICOLON_SYMBOL, 0);
}

DLParser::BlockListContext* DLParser::BlockListContext::blockList() {
  return getRuleContext<DLParser::BlockListContext>(0);
}

DLParser::ExpContext* DLParser::BlockListContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}

DLParser::DeclContext* DLParser::BlockListContext::decl() {
  return getRuleContext<DLParser::DeclContext>(0);
}


size_t DLParser::BlockListContext::getRuleIndex() const {
  return DLParser::RuleBlockList;
}

void DLParser::BlockListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockList(this);
}

void DLParser::BlockListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockList(this);
}


antlrcpp::Any DLParser::BlockListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitBlockList(this);
  else
    return visitor->visitChildren(this);
}

DLParser::BlockListContext* DLParser::blockList() {
  BlockListContext *_localctx = _tracker.createInstance<BlockListContext>(_ctx, getState());
  enterRule(_localctx, 16, DLParser::RuleBlockList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(197);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(176);
      statement();
      setState(177);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(179);
      statement();
      setState(180);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(181);
      blockList();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(183);
      exp();
      setState(184);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(186);
      exp();
      setState(187);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(188);
      blockList();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(190);
      decl();
      setState(191);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(193);
      decl();
      setState(194);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(195);
      blockList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JumpStatementContext ------------------------------------------------------------------

DLParser::JumpStatementContext::JumpStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::JumpStatementContext::BREAK_SYMBOL() {
  return getToken(DLParser::BREAK_SYMBOL, 0);
}

tree::TerminalNode* DLParser::JumpStatementContext::RETURN_SYMBOL() {
  return getToken(DLParser::RETURN_SYMBOL, 0);
}

DLParser::ExpContext* DLParser::JumpStatementContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}


size_t DLParser::JumpStatementContext::getRuleIndex() const {
  return DLParser::RuleJumpStatement;
}

void DLParser::JumpStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJumpStatement(this);
}

void DLParser::JumpStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJumpStatement(this);
}


antlrcpp::Any DLParser::JumpStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitJumpStatement(this);
  else
    return visitor->visitChildren(this);
}

DLParser::JumpStatementContext* DLParser::jumpStatement() {
  JumpStatementContext *_localctx = _tracker.createInstance<JumpStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, DLParser::RuleJumpStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(203);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(199);
      match(DLParser::BREAK_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(200);
      match(DLParser::RETURN_SYMBOL);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(201);
      match(DLParser::RETURN_SYMBOL);
      setState(202);
      exp();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

DLParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::TypeContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

DLParser::TypeTailContext* DLParser::TypeContext::typeTail() {
  return getRuleContext<DLParser::TypeTailContext>(0);
}

DLParser::RefTypeContext* DLParser::TypeContext::refType() {
  return getRuleContext<DLParser::RefTypeContext>(0);
}


size_t DLParser::TypeContext::getRuleIndex() const {
  return DLParser::RuleType;
}

void DLParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void DLParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


antlrcpp::Any DLParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

DLParser::TypeContext* DLParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 20, DLParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(205);
        match(DLParser::IDENTIFIER);
        setState(206);
        typeTail();
        break;
      }

      case DLParser::BITWISE_AND_OPERATOR: {
        enterOuterAlt(_localctx, 2);
        setState(207);
        refType();
        setState(208);
        typeTail();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeTailContext ------------------------------------------------------------------

DLParser::TypeTailContext::TypeTailContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::TypeTailContext::COMMA_SYMBOL() {
  return getToken(DLParser::COMMA_SYMBOL, 0);
}

DLParser::TypeTailContext* DLParser::TypeTailContext::typeTail() {
  return getRuleContext<DLParser::TypeTailContext>(0);
}

tree::TerminalNode* DLParser::TypeTailContext::JSON_SEPARATOR_SYMBOL() {
  return getToken(DLParser::JSON_SEPARATOR_SYMBOL, 0);
}


size_t DLParser::TypeTailContext::getRuleIndex() const {
  return DLParser::RuleTypeTail;
}

void DLParser::TypeTailContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeTail(this);
}

void DLParser::TypeTailContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeTail(this);
}


antlrcpp::Any DLParser::TypeTailContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitTypeTail(this);
  else
    return visitor->visitChildren(this);
}

DLParser::TypeTailContext* DLParser::typeTail() {
  TypeTailContext *_localctx = _tracker.createInstance<TypeTailContext>(_ctx, getState());
  enterRule(_localctx, 22, DLParser::RuleTypeTail);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(216);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::COMMA_SYMBOL: {
        enterOuterAlt(_localctx, 1);
        setState(212);
        match(DLParser::COMMA_SYMBOL);
        setState(213);
        typeTail();
        break;
      }

      case DLParser::JSON_SEPARATOR_SYMBOL: {
        enterOuterAlt(_localctx, 2);
        setState(214);
        match(DLParser::JSON_SEPARATOR_SYMBOL);
        setState(215);
        typeTail();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeContext ------------------------------------------------------------------

DLParser::FunctionTypeContext::FunctionTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DLParser::TypeContext *> DLParser::FunctionTypeContext::type() {
  return getRuleContexts<DLParser::TypeContext>();
}

DLParser::TypeContext* DLParser::FunctionTypeContext::type(size_t i) {
  return getRuleContext<DLParser::TypeContext>(i);
}

tree::TerminalNode* DLParser::FunctionTypeContext::JSON_SEPARATOR_SYMBOL() {
  return getToken(DLParser::JSON_SEPARATOR_SYMBOL, 0);
}


size_t DLParser::FunctionTypeContext::getRuleIndex() const {
  return DLParser::RuleFunctionType;
}

void DLParser::FunctionTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionType(this);
}

void DLParser::FunctionTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionType(this);
}


antlrcpp::Any DLParser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}

DLParser::FunctionTypeContext* DLParser::functionType() {
  FunctionTypeContext *_localctx = _tracker.createInstance<FunctionTypeContext>(_ctx, getState());
  enterRule(_localctx, 24, DLParser::RuleFunctionType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    type();
    setState(219);
    match(DLParser::JSON_SEPARATOR_SYMBOL);
    setState(220);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RefTypeContext ------------------------------------------------------------------

DLParser::RefTypeContext::RefTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::RefTypeContext::BITWISE_AND_OPERATOR() {
  return getToken(DLParser::BITWISE_AND_OPERATOR, 0);
}

DLParser::TypeContext* DLParser::RefTypeContext::type() {
  return getRuleContext<DLParser::TypeContext>(0);
}

tree::TerminalNode* DLParser::RefTypeContext::MUT_SYMBOL() {
  return getToken(DLParser::MUT_SYMBOL, 0);
}


size_t DLParser::RefTypeContext::getRuleIndex() const {
  return DLParser::RuleRefType;
}

void DLParser::RefTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRefType(this);
}

void DLParser::RefTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRefType(this);
}


antlrcpp::Any DLParser::RefTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitRefType(this);
  else
    return visitor->visitChildren(this);
}

DLParser::RefTypeContext* DLParser::refType() {
  RefTypeContext *_localctx = _tracker.createInstance<RefTypeContext>(_ctx, getState());
  enterRule(_localctx, 26, DLParser::RuleRefType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(227);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(222);
      match(DLParser::BITWISE_AND_OPERATOR);
      setState(223);
      type();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(224);
      match(DLParser::BITWISE_AND_OPERATOR);
      setState(225);
      match(DLParser::MUT_SYMBOL);
      setState(226);
      type();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

DLParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::FunctionDeclContext* DLParser::DeclContext::functionDecl() {
  return getRuleContext<DLParser::FunctionDeclContext>(0);
}

DLParser::VarDeclContext* DLParser::DeclContext::varDecl() {
  return getRuleContext<DLParser::VarDeclContext>(0);
}

DLParser::ClassDeclContext* DLParser::DeclContext::classDecl() {
  return getRuleContext<DLParser::ClassDeclContext>(0);
}

DLParser::InterfaceDeclContext* DLParser::DeclContext::interfaceDecl() {
  return getRuleContext<DLParser::InterfaceDeclContext>(0);
}


size_t DLParser::DeclContext::getRuleIndex() const {
  return DLParser::RuleDecl;
}

void DLParser::DeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecl(this);
}

void DLParser::DeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecl(this);
}


antlrcpp::Any DLParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

DLParser::DeclContext* DLParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 28, DLParser::RuleDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(233);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::SEMICOLON_SYMBOL:
      case DLParser::FUN_SYMBOL:
      case DLParser::SIG_SYMBOL: {
        enterOuterAlt(_localctx, 1);
        setState(229);
        functionDecl();
        break;
      }

      case DLParser::LETMUT_SYMBOL:
      case DLParser::LET_SYMBOL: {
        enterOuterAlt(_localctx, 2);
        setState(230);
        varDecl();
        break;
      }

      case DLParser::CLASS_SYMBOL: {
        enterOuterAlt(_localctx, 3);
        setState(231);
        classDecl();
        break;
      }

      case DLParser::INTERFACE_SYMBOL: {
        enterOuterAlt(_localctx, 4);
        setState(232);
        interfaceDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclContext ------------------------------------------------------------------

DLParser::FunctionDeclContext::FunctionDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::SignatureContext* DLParser::FunctionDeclContext::signature() {
  return getRuleContext<DLParser::SignatureContext>(0);
}

DLParser::FunctionDefContext* DLParser::FunctionDeclContext::functionDef() {
  return getRuleContext<DLParser::FunctionDefContext>(0);
}


size_t DLParser::FunctionDeclContext::getRuleIndex() const {
  return DLParser::RuleFunctionDecl;
}

void DLParser::FunctionDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDecl(this);
}

void DLParser::FunctionDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDecl(this);
}


antlrcpp::Any DLParser::FunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}

DLParser::FunctionDeclContext* DLParser::functionDecl() {
  FunctionDeclContext *_localctx = _tracker.createInstance<FunctionDeclContext>(_ctx, getState());
  enterRule(_localctx, 30, DLParser::RuleFunctionDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(239);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(235);
      signature();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(236);
      signature();
      setState(237);
      functionDef();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SignatureContext ------------------------------------------------------------------

DLParser::SignatureContext::SignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::SignatureContext::SIG_SYMBOL() {
  return getToken(DLParser::SIG_SYMBOL, 0);
}

tree::TerminalNode* DLParser::SignatureContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::SignatureContext::ALIAS_SYMBOL() {
  return getToken(DLParser::ALIAS_SYMBOL, 0);
}

DLParser::TypeContext* DLParser::SignatureContext::type() {
  return getRuleContext<DLParser::TypeContext>(0);
}


size_t DLParser::SignatureContext::getRuleIndex() const {
  return DLParser::RuleSignature;
}

void DLParser::SignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignature(this);
}

void DLParser::SignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignature(this);
}


antlrcpp::Any DLParser::SignatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitSignature(this);
  else
    return visitor->visitChildren(this);
}

DLParser::SignatureContext* DLParser::signature() {
  SignatureContext *_localctx = _tracker.createInstance<SignatureContext>(_ctx, getState());
  enterRule(_localctx, 32, DLParser::RuleSignature);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(246);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::SEMICOLON_SYMBOL:
      case DLParser::FUN_SYMBOL: {
        enterOuterAlt(_localctx, 1);

        break;
      }

      case DLParser::SIG_SYMBOL: {
        enterOuterAlt(_localctx, 2);
        setState(242);
        match(DLParser::SIG_SYMBOL);
        setState(243);
        match(DLParser::IDENTIFIER);
        setState(244);
        match(DLParser::ALIAS_SYMBOL);
        setState(245);
        type();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefContext ------------------------------------------------------------------

DLParser::FunctionDefContext::FunctionDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::FunctionDefContext::FUN_SYMBOL() {
  return getToken(DLParser::FUN_SYMBOL, 0);
}

tree::TerminalNode* DLParser::FunctionDefContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::FunctionDefContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

tree::TerminalNode* DLParser::FunctionDefContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}

DLParser::CompoundBlockContext* DLParser::FunctionDefContext::compoundBlock() {
  return getRuleContext<DLParser::CompoundBlockContext>(0);
}

DLParser::ParamListContext* DLParser::FunctionDefContext::paramList() {
  return getRuleContext<DLParser::ParamListContext>(0);
}


size_t DLParser::FunctionDefContext::getRuleIndex() const {
  return DLParser::RuleFunctionDef;
}

void DLParser::FunctionDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDef(this);
}

void DLParser::FunctionDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDef(this);
}


antlrcpp::Any DLParser::FunctionDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDef(this);
  else
    return visitor->visitChildren(this);
}

DLParser::FunctionDefContext* DLParser::functionDef() {
  FunctionDefContext *_localctx = _tracker.createInstance<FunctionDefContext>(_ctx, getState());
  enterRule(_localctx, 34, DLParser::RuleFunctionDef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(260);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(248);
      match(DLParser::FUN_SYMBOL);
      setState(249);
      match(DLParser::IDENTIFIER);
      setState(250);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(251);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(252);
      compoundBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(253);
      match(DLParser::FUN_SYMBOL);
      setState(254);
      match(DLParser::IDENTIFIER);
      setState(255);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(256);
      paramList();
      setState(257);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(258);
      compoundBlock();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamListContext ------------------------------------------------------------------

DLParser::ParamListContext::ParamListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::ParamListContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::ParamListContext::COMMA_SYMBOL() {
  return getToken(DLParser::COMMA_SYMBOL, 0);
}

DLParser::ParamListContext* DLParser::ParamListContext::paramList() {
  return getRuleContext<DLParser::ParamListContext>(0);
}


size_t DLParser::ParamListContext::getRuleIndex() const {
  return DLParser::RuleParamList;
}

void DLParser::ParamListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParamList(this);
}

void DLParser::ParamListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParamList(this);
}


antlrcpp::Any DLParser::ParamListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitParamList(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ParamListContext* DLParser::paramList() {
  ParamListContext *_localctx = _tracker.createInstance<ParamListContext>(_ctx, getState());
  enterRule(_localctx, 36, DLParser::RuleParamList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(266);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(262);
      match(DLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(263);
      match(DLParser::IDENTIFIER);
      setState(264);
      match(DLParser::COMMA_SYMBOL);
      setState(265);
      paramList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

DLParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::VarDeclContext::LET_SYMBOL() {
  return getToken(DLParser::LET_SYMBOL, 0);
}

tree::TerminalNode* DLParser::VarDeclContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::VarDeclContext::COLON_SYMBOL() {
  return getToken(DLParser::COLON_SYMBOL, 0);
}

DLParser::TypeContext* DLParser::VarDeclContext::type() {
  return getRuleContext<DLParser::TypeContext>(0);
}

tree::TerminalNode* DLParser::VarDeclContext::EQUAL_OPERATOR() {
  return getToken(DLParser::EQUAL_OPERATOR, 0);
}

DLParser::ExpContext* DLParser::VarDeclContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}

tree::TerminalNode* DLParser::VarDeclContext::LETMUT_SYMBOL() {
  return getToken(DLParser::LETMUT_SYMBOL, 0);
}


size_t DLParser::VarDeclContext::getRuleIndex() const {
  return DLParser::RuleVarDecl;
}

void DLParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void DLParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}


antlrcpp::Any DLParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

DLParser::VarDeclContext* DLParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 38, DLParser::RuleVarDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(290);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(268);
      match(DLParser::LET_SYMBOL);
      setState(269);
      match(DLParser::IDENTIFIER);
      setState(270);
      match(DLParser::COLON_SYMBOL);
      setState(271);
      type();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(272);
      match(DLParser::LET_SYMBOL);
      setState(273);
      match(DLParser::IDENTIFIER);
      setState(274);
      match(DLParser::COLON_SYMBOL);
      setState(275);
      type();
      setState(276);
      match(DLParser::EQUAL_OPERATOR);
      setState(277);
      exp();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(279);
      match(DLParser::LETMUT_SYMBOL);
      setState(280);
      match(DLParser::IDENTIFIER);
      setState(281);
      match(DLParser::COLON_SYMBOL);
      setState(282);
      type();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(283);
      match(DLParser::LETMUT_SYMBOL);
      setState(284);
      match(DLParser::IDENTIFIER);
      setState(285);
      match(DLParser::COLON_SYMBOL);
      setState(286);
      type();
      setState(287);
      match(DLParser::EQUAL_OPERATOR);
      setState(288);
      exp();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclContext ------------------------------------------------------------------

DLParser::ClassDeclContext::ClassDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::ClassHeadContext* DLParser::ClassDeclContext::classHead() {
  return getRuleContext<DLParser::ClassHeadContext>(0);
}

tree::TerminalNode* DLParser::ClassDeclContext::OPEN_CURLY_SYMBOL() {
  return getToken(DLParser::OPEN_CURLY_SYMBOL, 0);
}

DLParser::ClassBodyContext* DLParser::ClassDeclContext::classBody() {
  return getRuleContext<DLParser::ClassBodyContext>(0);
}

tree::TerminalNode* DLParser::ClassDeclContext::CLOSE_CURLY_SYMBOL() {
  return getToken(DLParser::CLOSE_CURLY_SYMBOL, 0);
}


size_t DLParser::ClassDeclContext::getRuleIndex() const {
  return DLParser::RuleClassDecl;
}

void DLParser::ClassDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDecl(this);
}

void DLParser::ClassDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDecl(this);
}


antlrcpp::Any DLParser::ClassDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitClassDecl(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ClassDeclContext* DLParser::classDecl() {
  ClassDeclContext *_localctx = _tracker.createInstance<ClassDeclContext>(_ctx, getState());
  enterRule(_localctx, 40, DLParser::RuleClassDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    classHead();
    setState(293);
    match(DLParser::OPEN_CURLY_SYMBOL);
    setState(294);
    classBody();
    setState(295);
    match(DLParser::CLOSE_CURLY_SYMBOL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassHeadContext ------------------------------------------------------------------

DLParser::ClassHeadContext::ClassHeadContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::ClassHeadContext::CLASS_SYMBOL() {
  return getToken(DLParser::CLASS_SYMBOL, 0);
}

std::vector<tree::TerminalNode *> DLParser::ClassHeadContext::IDENTIFIER() {
  return getTokens(DLParser::IDENTIFIER);
}

tree::TerminalNode* DLParser::ClassHeadContext::IDENTIFIER(size_t i) {
  return getToken(DLParser::IDENTIFIER, i);
}

tree::TerminalNode* DLParser::ClassHeadContext::EXTENDS_SYMBOL() {
  return getToken(DLParser::EXTENDS_SYMBOL, 0);
}

tree::TerminalNode* DLParser::ClassHeadContext::IMPL_SYMBOL() {
  return getToken(DLParser::IMPL_SYMBOL, 0);
}

DLParser::InterfaceListContext* DLParser::ClassHeadContext::interfaceList() {
  return getRuleContext<DLParser::InterfaceListContext>(0);
}


size_t DLParser::ClassHeadContext::getRuleIndex() const {
  return DLParser::RuleClassHead;
}

void DLParser::ClassHeadContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassHead(this);
}

void DLParser::ClassHeadContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassHead(this);
}


antlrcpp::Any DLParser::ClassHeadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitClassHead(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ClassHeadContext* DLParser::classHead() {
  ClassHeadContext *_localctx = _tracker.createInstance<ClassHeadContext>(_ctx, getState());
  enterRule(_localctx, 42, DLParser::RuleClassHead);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(313);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(297);
      match(DLParser::CLASS_SYMBOL);
      setState(298);
      match(DLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(299);
      match(DLParser::CLASS_SYMBOL);
      setState(300);
      match(DLParser::IDENTIFIER);
      setState(301);
      match(DLParser::EXTENDS_SYMBOL);
      setState(302);
      match(DLParser::IDENTIFIER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(303);
      match(DLParser::CLASS_SYMBOL);
      setState(304);
      match(DLParser::IDENTIFIER);
      setState(305);
      match(DLParser::IMPL_SYMBOL);
      setState(306);
      interfaceList();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(307);
      match(DLParser::CLASS_SYMBOL);
      setState(308);
      match(DLParser::IDENTIFIER);
      setState(309);
      match(DLParser::EXTENDS_SYMBOL);
      setState(310);
      match(DLParser::IDENTIFIER);
      setState(311);
      match(DLParser::IMPL_SYMBOL);
      setState(312);
      interfaceList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassBodyContext ------------------------------------------------------------------

DLParser::ClassBodyContext::ClassBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::AccessSpecifierContext* DLParser::ClassBodyContext::accessSpecifier() {
  return getRuleContext<DLParser::AccessSpecifierContext>(0);
}

DLParser::DeclContext* DLParser::ClassBodyContext::decl() {
  return getRuleContext<DLParser::DeclContext>(0);
}

tree::TerminalNode* DLParser::ClassBodyContext::SEMICOLON_SYMBOL() {
  return getToken(DLParser::SEMICOLON_SYMBOL, 0);
}

DLParser::ClassBodyContext* DLParser::ClassBodyContext::classBody() {
  return getRuleContext<DLParser::ClassBodyContext>(0);
}

DLParser::ConstructorContext* DLParser::ClassBodyContext::constructor() {
  return getRuleContext<DLParser::ConstructorContext>(0);
}


size_t DLParser::ClassBodyContext::getRuleIndex() const {
  return DLParser::RuleClassBody;
}

void DLParser::ClassBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassBody(this);
}

void DLParser::ClassBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassBody(this);
}


antlrcpp::Any DLParser::ClassBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitClassBody(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ClassBodyContext* DLParser::classBody() {
  ClassBodyContext *_localctx = _tracker.createInstance<ClassBodyContext>(_ctx, getState());
  enterRule(_localctx, 44, DLParser::RuleClassBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(331);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(315);
      accessSpecifier();
      setState(316);
      decl();
      setState(317);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(319);
      accessSpecifier();
      setState(320);
      decl();
      setState(321);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(322);
      classBody();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(324);
      constructor();
      setState(325);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(327);
      constructor();
      setState(328);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(329);
      classBody();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructorContext ------------------------------------------------------------------

DLParser::ConstructorContext::ConstructorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::ConstructorContext::CONSTRUCTOR_SYMBOL() {
  return getToken(DLParser::CONSTRUCTOR_SYMBOL, 0);
}

tree::TerminalNode* DLParser::ConstructorContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

DLParser::ParamListContext* DLParser::ConstructorContext::paramList() {
  return getRuleContext<DLParser::ParamListContext>(0);
}

tree::TerminalNode* DLParser::ConstructorContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}

DLParser::CompoundBlockContext* DLParser::ConstructorContext::compoundBlock() {
  return getRuleContext<DLParser::CompoundBlockContext>(0);
}


size_t DLParser::ConstructorContext::getRuleIndex() const {
  return DLParser::RuleConstructor;
}

void DLParser::ConstructorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstructor(this);
}

void DLParser::ConstructorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstructor(this);
}


antlrcpp::Any DLParser::ConstructorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitConstructor(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ConstructorContext* DLParser::constructor() {
  ConstructorContext *_localctx = _tracker.createInstance<ConstructorContext>(_ctx, getState());
  enterRule(_localctx, 46, DLParser::RuleConstructor);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(343);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(333);
      match(DLParser::CONSTRUCTOR_SYMBOL);
      setState(334);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(335);
      paramList();
      setState(336);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(337);
      compoundBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(339);
      match(DLParser::CONSTRUCTOR_SYMBOL);
      setState(340);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(341);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(342);
      compoundBlock();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccessSpecifierContext ------------------------------------------------------------------

DLParser::AccessSpecifierContext::AccessSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::AccessSpecifierContext::PRIVATE_SYMBOL() {
  return getToken(DLParser::PRIVATE_SYMBOL, 0);
}

tree::TerminalNode* DLParser::AccessSpecifierContext::PUBLIC_SYMBOL() {
  return getToken(DLParser::PUBLIC_SYMBOL, 0);
}


size_t DLParser::AccessSpecifierContext::getRuleIndex() const {
  return DLParser::RuleAccessSpecifier;
}

void DLParser::AccessSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAccessSpecifier(this);
}

void DLParser::AccessSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAccessSpecifier(this);
}


antlrcpp::Any DLParser::AccessSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitAccessSpecifier(this);
  else
    return visitor->visitChildren(this);
}

DLParser::AccessSpecifierContext* DLParser::accessSpecifier() {
  AccessSpecifierContext *_localctx = _tracker.createInstance<AccessSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 48, DLParser::RuleAccessSpecifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(345);
    _la = _input->LA(1);
    if (!(_la == DLParser::PUBLIC_SYMBOL

    || _la == DLParser::PRIVATE_SYMBOL)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceListContext ------------------------------------------------------------------

DLParser::InterfaceListContext::InterfaceListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::InterfaceListContext::INTERFACE_SYMBOL() {
  return getToken(DLParser::INTERFACE_SYMBOL, 0);
}

tree::TerminalNode* DLParser::InterfaceListContext::COMMA_SYMBOL() {
  return getToken(DLParser::COMMA_SYMBOL, 0);
}

DLParser::InterfaceListContext* DLParser::InterfaceListContext::interfaceList() {
  return getRuleContext<DLParser::InterfaceListContext>(0);
}


size_t DLParser::InterfaceListContext::getRuleIndex() const {
  return DLParser::RuleInterfaceList;
}

void DLParser::InterfaceListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceList(this);
}

void DLParser::InterfaceListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceList(this);
}


antlrcpp::Any DLParser::InterfaceListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitInterfaceList(this);
  else
    return visitor->visitChildren(this);
}

DLParser::InterfaceListContext* DLParser::interfaceList() {
  InterfaceListContext *_localctx = _tracker.createInstance<InterfaceListContext>(_ctx, getState());
  enterRule(_localctx, 50, DLParser::RuleInterfaceList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(351);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(347);
      match(DLParser::INTERFACE_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(348);
      match(DLParser::INTERFACE_SYMBOL);
      setState(349);
      match(DLParser::COMMA_SYMBOL);
      setState(350);
      interfaceList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceDeclContext ------------------------------------------------------------------

DLParser::InterfaceDeclContext::InterfaceDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::InterfaceHeadContext* DLParser::InterfaceDeclContext::interfaceHead() {
  return getRuleContext<DLParser::InterfaceHeadContext>(0);
}

tree::TerminalNode* DLParser::InterfaceDeclContext::OPEN_CURLY_SYMBOL() {
  return getToken(DLParser::OPEN_CURLY_SYMBOL, 0);
}

DLParser::InterfaceBodyContext* DLParser::InterfaceDeclContext::interfaceBody() {
  return getRuleContext<DLParser::InterfaceBodyContext>(0);
}

tree::TerminalNode* DLParser::InterfaceDeclContext::CLOSE_CURLY_SYMBOL() {
  return getToken(DLParser::CLOSE_CURLY_SYMBOL, 0);
}


size_t DLParser::InterfaceDeclContext::getRuleIndex() const {
  return DLParser::RuleInterfaceDecl;
}

void DLParser::InterfaceDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceDecl(this);
}

void DLParser::InterfaceDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceDecl(this);
}


antlrcpp::Any DLParser::InterfaceDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitInterfaceDecl(this);
  else
    return visitor->visitChildren(this);
}

DLParser::InterfaceDeclContext* DLParser::interfaceDecl() {
  InterfaceDeclContext *_localctx = _tracker.createInstance<InterfaceDeclContext>(_ctx, getState());
  enterRule(_localctx, 52, DLParser::RuleInterfaceDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(353);
    interfaceHead();
    setState(354);
    match(DLParser::OPEN_CURLY_SYMBOL);
    setState(355);
    interfaceBody();
    setState(356);
    match(DLParser::CLOSE_CURLY_SYMBOL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceHeadContext ------------------------------------------------------------------

DLParser::InterfaceHeadContext::InterfaceHeadContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::InterfaceHeadContext::INTERFACE_SYMBOL() {
  return getToken(DLParser::INTERFACE_SYMBOL, 0);
}

std::vector<tree::TerminalNode *> DLParser::InterfaceHeadContext::IDENTIFIER() {
  return getTokens(DLParser::IDENTIFIER);
}

tree::TerminalNode* DLParser::InterfaceHeadContext::IDENTIFIER(size_t i) {
  return getToken(DLParser::IDENTIFIER, i);
}

tree::TerminalNode* DLParser::InterfaceHeadContext::EXTENDS_SYMBOL() {
  return getToken(DLParser::EXTENDS_SYMBOL, 0);
}


size_t DLParser::InterfaceHeadContext::getRuleIndex() const {
  return DLParser::RuleInterfaceHead;
}

void DLParser::InterfaceHeadContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceHead(this);
}

void DLParser::InterfaceHeadContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceHead(this);
}


antlrcpp::Any DLParser::InterfaceHeadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitInterfaceHead(this);
  else
    return visitor->visitChildren(this);
}

DLParser::InterfaceHeadContext* DLParser::interfaceHead() {
  InterfaceHeadContext *_localctx = _tracker.createInstance<InterfaceHeadContext>(_ctx, getState());
  enterRule(_localctx, 54, DLParser::RuleInterfaceHead);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(364);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(358);
      match(DLParser::INTERFACE_SYMBOL);
      setState(359);
      match(DLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(360);
      match(DLParser::INTERFACE_SYMBOL);
      setState(361);
      match(DLParser::IDENTIFIER);
      setState(362);
      match(DLParser::EXTENDS_SYMBOL);
      setState(363);
      match(DLParser::IDENTIFIER);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceBodyContext ------------------------------------------------------------------

DLParser::InterfaceBodyContext::InterfaceBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::DeclContext* DLParser::InterfaceBodyContext::decl() {
  return getRuleContext<DLParser::DeclContext>(0);
}

tree::TerminalNode* DLParser::InterfaceBodyContext::SEMICOLON_SYMBOL() {
  return getToken(DLParser::SEMICOLON_SYMBOL, 0);
}

DLParser::InterfaceBodyContext* DLParser::InterfaceBodyContext::interfaceBody() {
  return getRuleContext<DLParser::InterfaceBodyContext>(0);
}


size_t DLParser::InterfaceBodyContext::getRuleIndex() const {
  return DLParser::RuleInterfaceBody;
}

void DLParser::InterfaceBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceBody(this);
}

void DLParser::InterfaceBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceBody(this);
}


antlrcpp::Any DLParser::InterfaceBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitInterfaceBody(this);
  else
    return visitor->visitChildren(this);
}

DLParser::InterfaceBodyContext* DLParser::interfaceBody() {
  InterfaceBodyContext *_localctx = _tracker.createInstance<InterfaceBodyContext>(_ctx, getState());
  enterRule(_localctx, 56, DLParser::RuleInterfaceBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(373);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(366);
      decl();
      setState(367);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(369);
      decl();
      setState(370);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(371);
      interfaceBody();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgramContext ------------------------------------------------------------------

DLParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::DeclContext* DLParser::ProgramContext::decl() {
  return getRuleContext<DLParser::DeclContext>(0);
}

tree::TerminalNode* DLParser::ProgramContext::SEMICOLON_SYMBOL() {
  return getToken(DLParser::SEMICOLON_SYMBOL, 0);
}

DLParser::ProgramContext* DLParser::ProgramContext::program() {
  return getRuleContext<DLParser::ProgramContext>(0);
}


size_t DLParser::ProgramContext::getRuleIndex() const {
  return DLParser::RuleProgram;
}

void DLParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void DLParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any DLParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ProgramContext* DLParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 58, DLParser::RuleProgram);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(382);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(375);
      decl();
      setState(376);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(378);
      decl();
      setState(379);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(380);
      program();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> DLParser::_decisionToDFA;
atn::PredictionContextCache DLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN DLParser::_atn;
std::vector<uint16_t> DLParser::_serializedATN;

std::vector<std::string> DLParser::_ruleNames = {
  "exp", "expPost", "aryOp", "unAryOp", "newExp", "expList", "statement", 
  "compoundBlock", "blockList", "jumpStatement", "type", "typeTail", "functionType", 
  "refType", "decl", "functionDecl", "signature", "functionDef", "paramList", 
  "varDecl", "classDecl", "classHead", "classBody", "constructor", "accessSpecifier", 
  "interfaceList", "interfaceDecl", "interfaceHead", "interfaceBody", "program"
};

std::vector<std::string> DLParser::_literalNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "'=='", "'='", "'>='", "'>'", "'<='", "'<'", "'!='", 
  "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "'!'", "'~'", "'&&'", "'&'", 
  "'||'", "'|'", "'.'", "','", "';'", "':'", "'('", "')'", "'{'", "'}'", 
  "'['", "']'", "'::'", "'->'", "'=>'", "'@'", "'?'", "'$'", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "'<>'"
};

std::vector<std::string> DLParser::_symbolicNames = {
  "", "ACCOUNT_SYMBOL", "ASCII_SYMBOL", "ALWAYS_SYMBOL", "BACKUP_SYMBOL", 
  "BEGIN_SYMBOL", "BYTE_SYMBOL", "CACHE_SYMBOL", "CHARSET_SYMBOL", "CHECKSUM_SYMBOL", 
  "CLOSE_SYMBOL", "COMMENT_SYMBOL", "COMMIT_SYMBOL", "CONTAINS_SYMBOL", 
  "DEALLOCATE_SYMBOL", "DO_SYMBOL", "END_SYMBOL", "EXECUTE_SYMBOL", "FLUSH_SYMBOL", 
  "FOLLOWS_SYMBOL", "FORMAT_SYMBOL", "GROUP_REPLICATION_SYMBOL", "HANDLER_SYMBOL", 
  "HELP_SYMBOL", "HOST_SYMBOL", "INSTALL_SYMBOL", "LANGUAGE_SYMBOL", "NO_SYMBOL", 
  "OPEN_SYMBOL", "OPTIONS_SYMBOL", "OWNER_SYMBOL", "PARSER_SYMBOL", "PARTITION_SYMBOL", 
  "PORT_SYMBOL", "PRECEDES_SYMBOL", "PREPARE_SYMBOL", "REMOVE_SYMBOL", "REPAIR_SYMBOL", 
  "RESET_SYMBOL", "RESTORE_SYMBOL", "ROLLBACK_SYMBOL", "SAVEPOINT_SYMBOL", 
  "SECURITY_SYMBOL", "SERVER_SYMBOL", "SIGNED_SYMBOL", "SLAVE_SYMBOL", "SOCKET_SYMBOL", 
  "SONAME_SYMBOL", "START_SYMBOL", "STOP_SYMBOL", "TRUNCATE_SYMBOL", "UNICODE_SYMBOL", 
  "UNINSTALL_SYMBOL", "UPGRADE_SYMBOL", "WRAPPER_SYMBOL", "XA_SYMBOL", "SHUTDOWN_SYMBOL", 
  "ACTION_SYMBOL", "ADDDATE_SYMBOL", "AFTER_SYMBOL", "AGAINST_SYMBOL", "AGGREGATE_SYMBOL", 
  "ALGORITHM_SYMBOL", "ANALYZE_SYMBOL", "ANY_SYMBOL", "AT_SYMBOL", "AUTHORS_SYMBOL", 
  "AUTO_INCREMENT_SYMBOL", "AUTOEXTEND_SIZE_SYMBOL", "AVG_ROW_LENGTH_SYMBOL", 
  "AVG_SYMBOL", "BINLOG_SYMBOL", "BIT_SYMBOL", "BLOCK_SYMBOL", "BOOL_SYMBOL", 
  "BOOLEAN_SYMBOL", "BTREE_SYMBOL", "CASCADED_SYMBOL", "CATALOG_NAME_SYMBOL", 
  "CHAIN_SYMBOL", "CHANGED_SYMBOL", "CHANNEL_SYMBOL", "CIPHER_SYMBOL", "CLIENT_SYMBOL", 
  "CLASS_ORIGIN_SYMBOL", "COALESCE_SYMBOL", "CODE_SYMBOL", "COLLATION_SYMBOL", 
  "COLUMN_NAME_SYMBOL", "COLUMN_FORMAT_SYMBOL", "COLUMNS_SYMBOL", "COMMITTED_SYMBOL", 
  "COMPACT_SYMBOL", "COMPLETION_SYMBOL", "COMPRESSED_SYMBOL", "COMPRESSION_SYMBOL", 
  "ENCRYPTION_SYMBOL", "CONCURRENT_SYMBOL", "CONNECTION_SYMBOL", "CONSISTENT_SYMBOL", 
  "CONSTRAINT_CATALOG_SYMBOL", "CONSTRAINT_SCHEMA_SYMBOL", "CONSTRAINT_NAME_SYMBOL", 
  "CONTEXT_SYMBOL", "CONTRIBUTORS_SYMBOL", "CPU_SYMBOL", "CUBE_SYMBOL", 
  "CURRENT_SYMBOL", "CURSOR_NAME_SYMBOL", "DATA_SYMBOL", "DATAFILE_SYMBOL", 
  "DATETIME_SYMBOL", "DATE_SYMBOL", "DAY_SYMBOL", "DEFAULT_AUTH_SYMBOL", 
  "DEFINER_SYMBOL", "DELAY_KEY_WRITE_SYMBOL", "DES_KEY_FILE_SYMBOL", "DIAGNOSTICS_SYMBOL", 
  "DIRECTORY_SYMBOL", "DISABLE_SYMBOL", "DISCARD_SYMBOL", "DISK_SYMBOL", 
  "DUMPFILE_SYMBOL", "DUPLICATE_SYMBOL", "DYNAMIC_SYMBOL", "ENDS_SYMBOL", 
  "ENUM_SYMBOL", "ENGINE_SYMBOL", "ENGINES_SYMBOL", "ERROR_SYMBOL", "ERRORS_SYMBOL", 
  "ESCAPE_SYMBOL", "EVENT_SYMBOL", "EVENTS_SYMBOL", "EVERY_SYMBOL", "EXPANSION_SYMBOL", 
  "EXPORT_SYMBOL", "EXTENDED_SYMBOL", "EXTENT_SIZE_SYMBOL", "FAULTS_SYMBOL", 
  "FAST_SYMBOL", "FOUND_SYMBOL", "ENABLE_SYMBOL", "FULL_SYMBOL", "FILE_SYMBOL", 
  "FILE_BLOCK_SIZE_SYMBOL", "FILTER_SYMBOL", "FIRST_SYMBOL", "FIXED_SYMBOL", 
  "GENERAL_SYMBOL", "GEOMETRY_SYMBOL", "GEOMETRYCOLLECTION_SYMBOL", "GET_FORMAT_SYMBOL", 
  "GRANTS_SYMBOL", "GLOBAL_SYMBOL", "HASH_SYMBOL", "HOSTS_SYMBOL", "HOUR_SYMBOL", 
  "IDENTIFIED_SYMBOL", "IGNORE_SERVER_IDS_SYMBOL", "INVOKER_SYMBOL", "IMPORT_SYMBOL", 
  "INDEXES_SYMBOL", "INITIAL_SIZE_SYMBOL", "INSTANCE_SYMBOL", "INNODB_SYMBOL", 
  "IO_SYMBOL", "IPC_SYMBOL", "ISOLATION_SYMBOL", "ISSUER_SYMBOL", "INSERT_METHOD_SYMBOL", 
  "JSON_SYMBOL", "KEY_BLOCK_SIZE_SYMBOL", "LAST_SYMBOL", "LEAVES_SYMBOL", 
  "LESS_SYMBOL", "LEVEL_SYMBOL", "LINESTRING_SYMBOL", "LIST_SYMBOL", "LOCAL_SYMBOL", 
  "LOCKS_SYMBOL", "LOGFILE_SYMBOL", "LOGS_SYMBOL", "MAX_ROWS_SYMBOL", "MASTER_SYMBOL", 
  "MASTER_HEARTBEAT_PERIOD_SYMBOL", "MASTER_HOST_SYMBOL", "MASTER_PORT_SYMBOL", 
  "MASTER_LOG_FILE_SYMBOL", "MASTER_LOG_POS_SYMBOL", "MASTER_USER_SYMBOL", 
  "MASTER_PASSWORD_SYMBOL", "MASTER_SERVER_ID_SYMBOL", "MASTER_CONNECT_RETRY_SYMBOL", 
  "MASTER_RETRY_COUNT_SYMBOL", "MASTER_DELAY_SYMBOL", "MASTER_SSL_SYMBOL", 
  "MASTER_SSL_CA_SYMBOL", "MASTER_SSL_CAPATH_SYMBOL", "MASTER_TLS_VERSION_SYMBOL", 
  "MASTER_SSL_CERT_SYMBOL", "MASTER_SSL_CIPHER_SYMBOL", "MASTER_SSL_CRL_SYMBOL", 
  "MASTER_SSL_CRLPATH_SYMBOL", "MASTER_SSL_KEY_SYMBOL", "MASTER_AUTO_POSITION_SYMBOL", 
  "MAX_CONNECTIONS_PER_HOUR_SYMBOL", "MAX_QUERIES_PER_HOUR_SYMBOL", "MAX_STATEMENT_TIME_SYMBOL", 
  "MAX_SIZE_SYMBOL", "MAX_UPDATES_PER_HOUR_SYMBOL", "MAX_USER_CONNECTIONS_SYMBOL", 
  "MEDIUM_SYMBOL", "MEMORY_SYMBOL", "MERGE_SYMBOL", "MESSAGE_TEXT_SYMBOL", 
  "MICROSECOND_SYMBOL", "MIGRATE_SYMBOL", "MINUTE_SYMBOL", "MIN_ROWS_SYMBOL", 
  "MODIFY_SYMBOL", "MODE_SYMBOL", "MONTH_SYMBOL", "MULTILINESTRING_SYMBOL", 
  "MULTIPOINT_SYMBOL", "MULTIPOLYGON_SYMBOL", "MUTEX_SYMBOL", "MYSQL_ERRNO_SYMBOL", 
  "NAME_SYMBOL", "NAMES_SYMBOL", "NATIONAL_SYMBOL", "NCHAR_SYMBOL", "NDBCLUSTER_SYMBOL", 
  "NEVER_SYMBOL", "NEXT_SYMBOL", "NEW_SYMBOL", "NO_WAIT_SYMBOL", "NODEGROUP_SYMBOL", 
  "NONE_SYMBOL", "NUMBER_SYMBOL", "NVARCHAR_SYMBOL", "OFFSET_SYMBOL", "OLD_PASSWORD_SYMBOL", 
  "ONE_SHOT_SYMBOL", "ONE_SYMBOL", "PACK_KEYS_SYMBOL", "PAGE_SYMBOL", "PARTIAL_SYMBOL", 
  "PARTITIONING_SYMBOL", "PARTITIONS_SYMBOL", "PASSWORD_SYMBOL", "PHASE_SYMBOL", 
  "PLUGIN_DIR_SYMBOL", "PLUGIN_SYMBOL", "PLUGINS_SYMBOL", "POINT_SYMBOL", 
  "POLYGON_SYMBOL", "PRESERVE_SYMBOL", "PREV_SYMBOL", "PRIVILEGES_SYMBOL", 
  "PROCESS_SYMBOL", "PROCESSLIST_SYMBOL", "PROFILE_SYMBOL", "PROFILES_SYMBOL", 
  "PROXY_SYMBOL", "QUARTER_SYMBOL", "QUERY_SYMBOL", "QUICK_SYMBOL", "READ_ONLY_SYMBOL", 
  "REBUILD_SYMBOL", "RECOVER_SYMBOL", "REDO_BUFFER_SIZE_SYMBOL", "REDOFILE_SYMBOL", 
  "REDUNDANT_SYMBOL", "RELAY_SYMBOL", "RELAYLOG_SYMBOL", "RELAY_LOG_FILE_SYMBOL", 
  "RELAY_LOG_POS_SYMBOL", "RELAY_THREAD_SYMBOL", "RELOAD_SYMBOL", "REORGANIZE_SYMBOL", 
  "REPEATABLE_SYMBOL", "REPLICATION_SYMBOL", "REPLICATE_DO_DB_SYMBOL", "REPLICATE_IGNORE_DB_SYMBOL", 
  "REPLICATE_DO_TABLE_SYMBOL", "REPLICATE_IGNORE_TABLE_SYMBOL", "REPLICATE_WILD_DO_TABLE_SYMBOL", 
  "REPLICATE_WILD_IGNORE_TABLE_SYMBOL", "REPLICATE_REWRITE_DB_SYMBOL", "RESUME_SYMBOL", 
  "RETURNED_SQLSTATE_SYMBOL", "RETURNS_SYMBOL", "REVERSE_SYMBOL", "ROLLUP_SYMBOL", 
  "ROTATE_SYMBOL", "ROUTINE_SYMBOL", "ROWS_SYMBOL", "ROW_COUNT_SYMBOL", 
  "ROW_FORMAT_SYMBOL", "ROW_SYMBOL", "RTREE_SYMBOL", "SCHEDULE_SYMBOL", 
  "SCHEMA_NAME_SYMBOL", "SECOND_SYMBOL", "SERIAL_SYMBOL", "SERIALIZABLE_SYMBOL", 
  "SESSION_SYMBOL", "SIMPLE_SYMBOL", "SHARE_SYMBOL", "SLOW_SYMBOL", "SNAPSHOT_SYMBOL", 
  "SOUNDS_SYMBOL", "SOURCE_SYMBOL", "SQL_AFTER_GTIDS_SYMBOL", "SQL_AFTER_MTS_GAPS_SYMBOL", 
  "SQL_BEFORE_GTIDS_SYMBOL", "SQL_CACHE_SYMBOL", "SQL_BUFFER_RESULT_SYMBOL", 
  "SQL_NO_CACHE_SYMBOL", "SQL_THREAD_SYMBOL", "STACKED_SYMBOL", "STARTS_SYMBOL", 
  "STATS_AUTO_RECALC_SYMBOL", "STATS_PERSISTENT_SYMBOL", "STATS_SAMPLE_PAGES_SYMBOL", 
  "STATUS_SYMBOL", "STORAGE_SYMBOL", "STRING_SYMBOL", "SUBCLASS_ORIGIN_SYMBOL", 
  "SUBDATE_SYMBOL", "SUBJECT_SYMBOL", "SUBPARTITION_SYMBOL", "SUBPARTITIONS_SYMBOL", 
  "SUPER_SYMBOL", "SUSPEND_SYMBOL", "SWAPS_SYMBOL", "SWITCHES_SYMBOL", "TABLE_NAME_SYMBOL", 
  "TABLES_SYMBOL", "TABLE_CHECKSUM_SYMBOL", "TABLESPACE_SYMBOL", "TEMPORARY_SYMBOL", 
  "TEMPTABLE_SYMBOL", "TEXT_SYMBOL", "THAN_SYMBOL", "TRANSACTION_SYMBOL", 
  "TRIGGERS_SYMBOL", "TIMESTAMP_SYMBOL", "TIMESTAMP_ADD_SYMBOL", "TIMESTAMP_DIFF_SYMBOL", 
  "TIME_SYMBOL", "TYPES_SYMBOL", "TYPE_SYMBOL", "UDF_RETURNS_SYMBOL", "FUNCTION_SYMBOL", 
  "UNCOMMITTED_SYMBOL", "UNDEFINED_SYMBOL", "UNDO_BUFFER_SIZE_SYMBOL", "UNDOFILE_SYMBOL", 
  "UNKNOWN_SYMBOL", "UNTIL_SYMBOL", "USER_RESOURCES_SYMBOL", "USER_SYMBOL", 
  "USE_FRM_SYMBOL", "VARIABLES_SYMBOL", "VIEW_SYMBOL", "VALUE_SYMBOL", "WARNINGS_SYMBOL", 
  "WAIT_SYMBOL", "WEEK_SYMBOL", "WORK_SYMBOL", "WEIGHT_STRING_SYMBOL", "X509_SYMBOL", 
  "XID_SYMBOL", "XML_SYMBOL", "YEAR_SYMBOL", "NOT2_SYMBOL", "CONCAT_PIPES_SYMBOL", 
  "INT_NUMBER", "LONG_NUMBER", "ULONGLONG_NUMBER", "ASSIGN_OPERATOR", "EQUAL_OPERATOR", 
  "GREATER_OR_EQUAL_OPERATOR", "GREATER_THAN_OPERATOR", "LESS_OR_EQUAL_OPERATOR", 
  "LESS_THAN_OPERATOR", "NOT_EQUAL_OPERATOR", "PLUS_OPERATOR", "MINUS_OPERATOR", 
  "MULT_OPERATOR", "DIV_OPERATOR", "MOD_OPERATOR", "BITWISE_XOR_OPERATOR", 
  "LOGICAL_NOT_OPERATOR", "BITWISE_NOT_OPERATOR", "LOGICAL_AND_OPERATOR", 
  "BITWISE_AND_OPERATOR", "LOGICAL_OR_OPERATOR", "BITWISE_OR_OPERATOR", 
  "DOT_SYMBOL", "COMMA_SYMBOL", "SEMICOLON_SYMBOL", "COLON_SYMBOL", "OPEN_PAR_SYMBOL", 
  "CLOSE_PAR_SYMBOL", "OPEN_CURLY_SYMBOL", "CLOSE_CURLY_SYMBOL", "OPEN_SQUARE_SYMBOL", 
  "CLOSE_SQUARE_SYMBOL", "ALIAS_SYMBOL", "JSON_SEPARATOR_SYMBOL", "SEPARATOR_SYMBOL", 
  "AT_SIGN_SYMBOL", "PARAM_MARKER", "DOLLAR_SYMBOL", "CONST", "INTEGERCONST", 
  "DECIMAL_NUMBER", "FLOAT_NUMBER", "LETMUT_SYMBOL", "LET_SYMBOL", "FUN_SYMBOL", 
  "CLASS_SYMBOL", "INTERFACE_SYMBOL", "EXTENDS_SYMBOL", "IMPL_SYMBOL", "PUBLIC_SYMBOL", 
  "PRIVATE_SYMBOL", "IF_SYMBOL", "THEN_SYMBOL", "ELSE_SYMBOL", "SWITCH_SYMBOL", 
  "CASE_SYMBOL", "FOR_SYMBOL", "WHILE_SYMBOL", "LOOP_SYMBOL", "PROP_SYMBOL", 
  "THIS_SYMBOL", "BREAK_SYMBOL", "RETURN_SYMBOL", "MUT_SYMBOL", "SIG_SYMBOL", 
  "CONSTRUCTOR_SYMBOL", "WHITESPACE", "IDENTIFIER", "QUOTED_STRING", "BLOCK_COMMENT", 
  "SLASHSLASH_COMMET", "NOT_EQUAL2_OPERATOR"
};

dfa::Vocabulary DLParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> DLParser::_tokenNames;

DLParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x1c5, 0x183, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x51, 
    0xa, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x77, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x87, 0xa, 0x6, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x8e, 0xa, 
    0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0xa9, 0xa, 0x8, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 
    0xb1, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x5, 0xa, 0xc8, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x5, 0xb, 0xce, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x5, 0xc, 0xd5, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x5, 0xd, 0xdb, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xe6, 
    0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xec, 
    0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0xf2, 
    0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 
    0x12, 0xf9, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x5, 0x13, 0x107, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x5, 0x14, 0x10d, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 
    0x15, 0x125, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x13c, 0xa, 0x17, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x14e, 0xa, 0x18, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x15a, 0xa, 0x19, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x162, 
    0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 
    0x16f, 0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x178, 0xa, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x181, 
    0xa, 0x1f, 0x3, 0x1f, 0x2, 0x2, 0x20, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 
    0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 
    0x2, 0x5, 0x6, 0x2, 0x181, 0x182, 0x188, 0x18c, 0x190, 0x190, 0x192, 
    0x192, 0x4, 0x2, 0x18e, 0x18f, 0x191, 0x191, 0x3, 0x2, 0x1af, 0x1b0, 
    0x2, 0x196, 0x2, 0x50, 0x3, 0x2, 0x2, 0x2, 0x4, 0x76, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x78, 0x3, 0x2, 0x2, 0x2, 0x8, 0x7a, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x86, 0x3, 0x2, 0x2, 0x2, 0xc, 0x8d, 0x3, 0x2, 0x2, 0x2, 0xe, 0xa8, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0xb0, 0x3, 0x2, 0x2, 0x2, 0x12, 0xc7, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x16, 0xd4, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0xda, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xdc, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xeb, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0xf1, 0x3, 0x2, 0x2, 0x2, 0x22, 0xf8, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x106, 0x3, 0x2, 0x2, 0x2, 0x26, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x28, 0x124, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0x126, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x13b, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x30, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x34, 0x161, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x163, 0x3, 0x2, 0x2, 0x2, 0x38, 0x16e, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0x177, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x180, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x3f, 0x7, 0x1a4, 0x2, 0x2, 0x3f, 0x51, 0x5, 0x4, 0x3, 0x2, 0x40, 0x41, 
    0x7, 0x1c1, 0x2, 0x2, 0x41, 0x51, 0x5, 0x4, 0x3, 0x2, 0x42, 0x43, 0x7, 
    0x1c2, 0x2, 0x2, 0x43, 0x51, 0x5, 0x4, 0x3, 0x2, 0x44, 0x45, 0x7, 0x198, 
    0x2, 0x2, 0x45, 0x46, 0x5, 0x2, 0x2, 0x2, 0x46, 0x47, 0x7, 0x199, 0x2, 
    0x2, 0x47, 0x48, 0x5, 0x4, 0x3, 0x2, 0x48, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x49, 0x4a, 0x5, 0x8, 0x5, 0x2, 0x4a, 0x4b, 0x5, 0x2, 0x2, 0x2, 0x4b, 
    0x4c, 0x5, 0x4, 0x3, 0x2, 0x4c, 0x51, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 
    0x5, 0xa, 0x6, 0x2, 0x4e, 0x4f, 0x5, 0x4, 0x3, 0x2, 0x4f, 0x51, 0x3, 
    0x2, 0x2, 0x2, 0x50, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x40, 0x3, 0x2, 
    0x2, 0x2, 0x50, 0x42, 0x3, 0x2, 0x2, 0x2, 0x50, 0x44, 0x3, 0x2, 0x2, 
    0x2, 0x50, 0x49, 0x3, 0x2, 0x2, 0x2, 0x50, 0x4d, 0x3, 0x2, 0x2, 0x2, 
    0x51, 0x3, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 0x19c, 0x2, 0x2, 0x53, 
    0x54, 0x5, 0xc, 0x7, 0x2, 0x54, 0x55, 0x7, 0x19d, 0x2, 0x2, 0x55, 0x56, 
    0x5, 0x4, 0x3, 0x2, 0x56, 0x77, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x7, 
    0x19c, 0x2, 0x2, 0x58, 0x59, 0x7, 0x19d, 0x2, 0x2, 0x59, 0x77, 0x5, 
    0x4, 0x3, 0x2, 0x5a, 0x5b, 0x7, 0x19c, 0x2, 0x2, 0x5b, 0x5c, 0x5, 0x2, 
    0x2, 0x2, 0x5c, 0x5d, 0x7, 0x19d, 0x2, 0x2, 0x5d, 0x5e, 0x5, 0x4, 0x3, 
    0x2, 0x5e, 0x77, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x60, 0x7, 0x1a1, 0x2, 0x2, 
    0x60, 0x61, 0x7, 0x1c1, 0x2, 0x2, 0x61, 0x62, 0x7, 0x198, 0x2, 0x2, 
    0x62, 0x63, 0x5, 0xc, 0x7, 0x2, 0x63, 0x64, 0x7, 0x199, 0x2, 0x2, 0x64, 
    0x65, 0x5, 0x4, 0x3, 0x2, 0x65, 0x77, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 
    0x7, 0x198, 0x2, 0x2, 0x67, 0x68, 0x5, 0xc, 0x7, 0x2, 0x68, 0x69, 0x7, 
    0x199, 0x2, 0x2, 0x69, 0x6a, 0x5, 0x4, 0x3, 0x2, 0x6a, 0x77, 0x3, 0x2, 
    0x2, 0x2, 0x6b, 0x6c, 0x7, 0x198, 0x2, 0x2, 0x6c, 0x6d, 0x7, 0x199, 
    0x2, 0x2, 0x6d, 0x77, 0x5, 0x4, 0x3, 0x2, 0x6e, 0x6f, 0x7, 0x194, 0x2, 
    0x2, 0x6f, 0x70, 0x7, 0x1c1, 0x2, 0x2, 0x70, 0x77, 0x5, 0x4, 0x3, 0x2, 
    0x71, 0x72, 0x5, 0x6, 0x4, 0x2, 0x72, 0x73, 0x5, 0x2, 0x2, 0x2, 0x73, 
    0x74, 0x5, 0x4, 0x3, 0x2, 0x74, 0x77, 0x3, 0x2, 0x2, 0x2, 0x75, 0x77, 
    0x3, 0x2, 0x2, 0x2, 0x76, 0x52, 0x3, 0x2, 0x2, 0x2, 0x76, 0x57, 0x3, 
    0x2, 0x2, 0x2, 0x76, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x76, 0x5f, 0x3, 0x2, 
    0x2, 0x2, 0x76, 0x66, 0x3, 0x2, 0x2, 0x2, 0x76, 0x6b, 0x3, 0x2, 0x2, 
    0x2, 0x76, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x76, 0x71, 0x3, 0x2, 0x2, 0x2, 
    0x76, 0x75, 0x3, 0x2, 0x2, 0x2, 0x77, 0x5, 0x3, 0x2, 0x2, 0x2, 0x78, 
    0x79, 0x9, 0x2, 0x2, 0x2, 0x79, 0x7, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 
    0x9, 0x3, 0x2, 0x2, 0x7b, 0x9, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x7, 
    0xee, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x1c1, 0x2, 0x2, 0x7e, 0x7f, 0x7, 0x198, 
    0x2, 0x2, 0x7f, 0x87, 0x7, 0x199, 0x2, 0x2, 0x80, 0x81, 0x7, 0xee, 0x2, 
    0x2, 0x81, 0x82, 0x7, 0x1c1, 0x2, 0x2, 0x82, 0x83, 0x7, 0x198, 0x2, 
    0x2, 0x83, 0x84, 0x5, 0xc, 0x7, 0x2, 0x84, 0x85, 0x7, 0x199, 0x2, 0x2, 
    0x85, 0x87, 0x3, 0x2, 0x2, 0x2, 0x86, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x86, 
    0x80, 0x3, 0x2, 0x2, 0x2, 0x87, 0xb, 0x3, 0x2, 0x2, 0x2, 0x88, 0x8e, 
    0x5, 0x2, 0x2, 0x2, 0x89, 0x8a, 0x5, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x7, 
    0x195, 0x2, 0x2, 0x8b, 0x8c, 0x5, 0xc, 0x7, 0x2, 0x8c, 0x8e, 0x3, 0x2, 
    0x2, 0x2, 0x8d, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x89, 0x3, 0x2, 0x2, 
    0x2, 0x8e, 0xd, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x90, 0x7, 0x1b1, 0x2, 0x2, 
    0x90, 0x91, 0x7, 0x198, 0x2, 0x2, 0x91, 0x92, 0x5, 0x2, 0x2, 0x2, 0x92, 
    0x93, 0x7, 0x199, 0x2, 0x2, 0x93, 0x94, 0x5, 0x10, 0x9, 0x2, 0x94, 0x95, 
    0x7, 0x1b3, 0x2, 0x2, 0x95, 0x96, 0x5, 0x10, 0x9, 0x2, 0x96, 0xa9, 0x3, 
    0x2, 0x2, 0x2, 0x97, 0x98, 0x7, 0x1b1, 0x2, 0x2, 0x98, 0x99, 0x7, 0x198, 
    0x2, 0x2, 0x99, 0x9a, 0x5, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x199, 0x2, 
    0x2, 0x9b, 0x9c, 0x5, 0x10, 0x9, 0x2, 0x9c, 0xa9, 0x3, 0x2, 0x2, 0x2, 
    0x9d, 0x9e, 0x7, 0x1b6, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x198, 0x2, 0x2, 
    0x9f, 0xa0, 0x5, 0x10, 0x9, 0x2, 0xa0, 0xa1, 0x7, 0x196, 0x2, 0x2, 0xa1, 
    0xa2, 0x5, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x196, 0x2, 0x2, 0xa3, 0xa4, 
    0x5, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0x199, 0x2, 0x2, 0xa5, 0xa6, 0x5, 
    0x10, 0x9, 0x2, 0xa6, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa9, 0x5, 0x14, 
    0xb, 0x2, 0xa8, 0x8f, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x97, 0x3, 0x2, 0x2, 
    0x2, 0xa8, 0x9d, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa7, 0x3, 0x2, 0x2, 0x2, 
    0xa9, 0xf, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x19a, 0x2, 0x2, 0xab, 
    0xb1, 0x7, 0x19b, 0x2, 0x2, 0xac, 0xad, 0x7, 0x19a, 0x2, 0x2, 0xad, 
    0xae, 0x5, 0x12, 0xa, 0x2, 0xae, 0xaf, 0x7, 0x19b, 0x2, 0x2, 0xaf, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0xb0, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xac, 0x3, 
    0x2, 0x2, 0x2, 0xb1, 0x11, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x5, 0xe, 
    0x8, 0x2, 0xb3, 0xb4, 0x7, 0x196, 0x2, 0x2, 0xb4, 0xc8, 0x3, 0x2, 0x2, 
    0x2, 0xb5, 0xb6, 0x5, 0xe, 0x8, 0x2, 0xb6, 0xb7, 0x7, 0x196, 0x2, 0x2, 
    0xb7, 0xb8, 0x5, 0x12, 0xa, 0x2, 0xb8, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xb9, 
    0xba, 0x5, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x196, 0x2, 0x2, 0xbb, 0xc8, 
    0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x5, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x7, 
    0x196, 0x2, 0x2, 0xbe, 0xbf, 0x5, 0x12, 0xa, 0x2, 0xbf, 0xc8, 0x3, 0x2, 
    0x2, 0x2, 0xc0, 0xc1, 0x5, 0x1e, 0x10, 0x2, 0xc1, 0xc2, 0x7, 0x196, 
    0x2, 0x2, 0xc2, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 0x5, 0x1e, 0x10, 
    0x2, 0xc4, 0xc5, 0x7, 0x196, 0x2, 0x2, 0xc5, 0xc6, 0x5, 0x12, 0xa, 0x2, 
    0xc6, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xc7, 
    0xb5, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xbc, 
    0x3, 0x2, 0x2, 0x2, 0xc7, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc3, 0x3, 
    0x2, 0x2, 0x2, 0xc8, 0x13, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xce, 0x7, 0x1bb, 
    0x2, 0x2, 0xca, 0xce, 0x7, 0x1bc, 0x2, 0x2, 0xcb, 0xcc, 0x7, 0x1bc, 
    0x2, 0x2, 0xcc, 0xce, 0x5, 0x2, 0x2, 0x2, 0xcd, 0xc9, 0x3, 0x2, 0x2, 
    0x2, 0xcd, 0xca, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 
    0xce, 0x15, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xd0, 0x7, 0x1c1, 0x2, 0x2, 0xd0, 
    0xd5, 0x5, 0x18, 0xd, 0x2, 0xd1, 0xd2, 0x5, 0x1c, 0xf, 0x2, 0xd2, 0xd3, 
    0x5, 0x18, 0xd, 0x2, 0xd3, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xcf, 0x3, 
    0x2, 0x2, 0x2, 0xd4, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd5, 0x17, 0x3, 0x2, 
    0x2, 0x2, 0xd6, 0xd7, 0x7, 0x195, 0x2, 0x2, 0xd7, 0xdb, 0x5, 0x18, 0xd, 
    0x2, 0xd8, 0xd9, 0x7, 0x19f, 0x2, 0x2, 0xd9, 0xdb, 0x5, 0x18, 0xd, 0x2, 
    0xda, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xda, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xdb, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdd, 0x5, 0x16, 0xc, 0x2, 0xdd, 0xde, 
    0x7, 0x19f, 0x2, 0x2, 0xde, 0xdf, 0x5, 0x16, 0xc, 0x2, 0xdf, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0xe0, 0xe1, 0x7, 0x191, 0x2, 0x2, 0xe1, 0xe6, 0x5, 0x16, 
    0xc, 0x2, 0xe2, 0xe3, 0x7, 0x191, 0x2, 0x2, 0xe3, 0xe4, 0x7, 0x1bd, 
    0x2, 0x2, 0xe4, 0xe6, 0x5, 0x16, 0xc, 0x2, 0xe5, 0xe0, 0x3, 0x2, 0x2, 
    0x2, 0xe5, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe6, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0xe7, 0xec, 0x5, 0x20, 0x11, 0x2, 0xe8, 0xec, 0x5, 0x28, 0x15, 0x2, 
    0xe9, 0xec, 0x5, 0x2a, 0x16, 0x2, 0xea, 0xec, 0x5, 0x36, 0x1c, 0x2, 
    0xeb, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xeb, 
    0xe9, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xea, 0x3, 0x2, 0x2, 0x2, 0xec, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0xed, 0xf2, 0x5, 0x22, 0x12, 0x2, 0xee, 0xef, 0x5, 
    0x22, 0x12, 0x2, 0xef, 0xf0, 0x5, 0x24, 0x13, 0x2, 0xf0, 0xf2, 0x3, 
    0x2, 0x2, 0x2, 0xf1, 0xed, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xee, 0x3, 0x2, 
    0x2, 0x2, 0xf2, 0x21, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xf9, 0x3, 0x2, 0x2, 
    0x2, 0xf4, 0xf5, 0x7, 0x1be, 0x2, 0x2, 0xf5, 0xf6, 0x7, 0x1c1, 0x2, 
    0x2, 0xf6, 0xf7, 0x7, 0x19e, 0x2, 0x2, 0xf7, 0xf9, 0x5, 0x16, 0xc, 0x2, 
    0xf8, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xf9, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 0x7, 0x1aa, 0x2, 0x2, 0xfb, 0xfc, 
    0x7, 0x1c1, 0x2, 0x2, 0xfc, 0xfd, 0x7, 0x198, 0x2, 0x2, 0xfd, 0xfe, 
    0x7, 0x199, 0x2, 0x2, 0xfe, 0x107, 0x5, 0x10, 0x9, 0x2, 0xff, 0x100, 
    0x7, 0x1aa, 0x2, 0x2, 0x100, 0x101, 0x7, 0x1c1, 0x2, 0x2, 0x101, 0x102, 
    0x7, 0x198, 0x2, 0x2, 0x102, 0x103, 0x5, 0x26, 0x14, 0x2, 0x103, 0x104, 
    0x7, 0x199, 0x2, 0x2, 0x104, 0x105, 0x5, 0x10, 0x9, 0x2, 0x105, 0x107, 
    0x3, 0x2, 0x2, 0x2, 0x106, 0xfa, 0x3, 0x2, 0x2, 0x2, 0x106, 0xff, 0x3, 
    0x2, 0x2, 0x2, 0x107, 0x25, 0x3, 0x2, 0x2, 0x2, 0x108, 0x10d, 0x7, 0x1c1, 
    0x2, 0x2, 0x109, 0x10a, 0x7, 0x1c1, 0x2, 0x2, 0x10a, 0x10b, 0x7, 0x195, 
    0x2, 0x2, 0x10b, 0x10d, 0x5, 0x26, 0x14, 0x2, 0x10c, 0x108, 0x3, 0x2, 
    0x2, 0x2, 0x10c, 0x109, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x27, 0x3, 0x2, 0x2, 
    0x2, 0x10e, 0x10f, 0x7, 0x1a9, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x1c1, 0x2, 
    0x2, 0x110, 0x111, 0x7, 0x197, 0x2, 0x2, 0x111, 0x125, 0x5, 0x16, 0xc, 
    0x2, 0x112, 0x113, 0x7, 0x1a9, 0x2, 0x2, 0x113, 0x114, 0x7, 0x1c1, 0x2, 
    0x2, 0x114, 0x115, 0x7, 0x197, 0x2, 0x2, 0x115, 0x116, 0x5, 0x16, 0xc, 
    0x2, 0x116, 0x117, 0x7, 0x182, 0x2, 0x2, 0x117, 0x118, 0x5, 0x2, 0x2, 
    0x2, 0x118, 0x125, 0x3, 0x2, 0x2, 0x2, 0x119, 0x11a, 0x7, 0x1a8, 0x2, 
    0x2, 0x11a, 0x11b, 0x7, 0x1c1, 0x2, 0x2, 0x11b, 0x11c, 0x7, 0x197, 0x2, 
    0x2, 0x11c, 0x125, 0x5, 0x16, 0xc, 0x2, 0x11d, 0x11e, 0x7, 0x1a8, 0x2, 
    0x2, 0x11e, 0x11f, 0x7, 0x1c1, 0x2, 0x2, 0x11f, 0x120, 0x7, 0x197, 0x2, 
    0x2, 0x120, 0x121, 0x5, 0x16, 0xc, 0x2, 0x121, 0x122, 0x7, 0x182, 0x2, 
    0x2, 0x122, 0x123, 0x5, 0x2, 0x2, 0x2, 0x123, 0x125, 0x3, 0x2, 0x2, 
    0x2, 0x124, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x124, 0x112, 0x3, 0x2, 0x2, 
    0x2, 0x124, 0x119, 0x3, 0x2, 0x2, 0x2, 0x124, 0x11d, 0x3, 0x2, 0x2, 
    0x2, 0x125, 0x29, 0x3, 0x2, 0x2, 0x2, 0x126, 0x127, 0x5, 0x2c, 0x17, 
    0x2, 0x127, 0x128, 0x7, 0x19a, 0x2, 0x2, 0x128, 0x129, 0x5, 0x2e, 0x18, 
    0x2, 0x129, 0x12a, 0x7, 0x19b, 0x2, 0x2, 0x12a, 0x2b, 0x3, 0x2, 0x2, 
    0x2, 0x12b, 0x12c, 0x7, 0x1ab, 0x2, 0x2, 0x12c, 0x13c, 0x7, 0x1c1, 0x2, 
    0x2, 0x12d, 0x12e, 0x7, 0x1ab, 0x2, 0x2, 0x12e, 0x12f, 0x7, 0x1c1, 0x2, 
    0x2, 0x12f, 0x130, 0x7, 0x1ad, 0x2, 0x2, 0x130, 0x13c, 0x7, 0x1c1, 0x2, 
    0x2, 0x131, 0x132, 0x7, 0x1ab, 0x2, 0x2, 0x132, 0x133, 0x7, 0x1c1, 0x2, 
    0x2, 0x133, 0x134, 0x7, 0x1ae, 0x2, 0x2, 0x134, 0x13c, 0x5, 0x34, 0x1b, 
    0x2, 0x135, 0x136, 0x7, 0x1ab, 0x2, 0x2, 0x136, 0x137, 0x7, 0x1c1, 0x2, 
    0x2, 0x137, 0x138, 0x7, 0x1ad, 0x2, 0x2, 0x138, 0x139, 0x7, 0x1c1, 0x2, 
    0x2, 0x139, 0x13a, 0x7, 0x1ae, 0x2, 0x2, 0x13a, 0x13c, 0x5, 0x34, 0x1b, 
    0x2, 0x13b, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x12d, 0x3, 0x2, 0x2, 
    0x2, 0x13b, 0x131, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x135, 0x3, 0x2, 0x2, 
    0x2, 0x13c, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13e, 0x5, 0x32, 0x1a, 
    0x2, 0x13e, 0x13f, 0x5, 0x1e, 0x10, 0x2, 0x13f, 0x140, 0x7, 0x196, 0x2, 
    0x2, 0x140, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x141, 0x142, 0x5, 0x32, 0x1a, 
    0x2, 0x142, 0x143, 0x5, 0x1e, 0x10, 0x2, 0x143, 0x144, 0x7, 0x196, 0x2, 
    0x2, 0x144, 0x145, 0x5, 0x2e, 0x18, 0x2, 0x145, 0x14e, 0x3, 0x2, 0x2, 
    0x2, 0x146, 0x147, 0x5, 0x30, 0x19, 0x2, 0x147, 0x148, 0x7, 0x196, 0x2, 
    0x2, 0x148, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14a, 0x5, 0x30, 0x19, 
    0x2, 0x14a, 0x14b, 0x7, 0x196, 0x2, 0x2, 0x14b, 0x14c, 0x5, 0x2e, 0x18, 
    0x2, 0x14c, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x13d, 0x3, 0x2, 0x2, 
    0x2, 0x14d, 0x141, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x146, 0x3, 0x2, 0x2, 
    0x2, 0x14d, 0x149, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x2f, 0x3, 0x2, 0x2, 0x2, 
    0x14f, 0x150, 0x7, 0x1bf, 0x2, 0x2, 0x150, 0x151, 0x7, 0x198, 0x2, 0x2, 
    0x151, 0x152, 0x5, 0x26, 0x14, 0x2, 0x152, 0x153, 0x7, 0x199, 0x2, 0x2, 
    0x153, 0x154, 0x5, 0x10, 0x9, 0x2, 0x154, 0x15a, 0x3, 0x2, 0x2, 0x2, 
    0x155, 0x156, 0x7, 0x1bf, 0x2, 0x2, 0x156, 0x157, 0x7, 0x198, 0x2, 0x2, 
    0x157, 0x158, 0x7, 0x199, 0x2, 0x2, 0x158, 0x15a, 0x5, 0x10, 0x9, 0x2, 
    0x159, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x159, 0x155, 0x3, 0x2, 0x2, 0x2, 
    0x15a, 0x31, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15c, 0x9, 0x4, 0x2, 0x2, 0x15c, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x162, 0x7, 0x1ac, 0x2, 0x2, 0x15e, 
    0x15f, 0x7, 0x1ac, 0x2, 0x2, 0x15f, 0x160, 0x7, 0x195, 0x2, 0x2, 0x160, 
    0x162, 0x5, 0x34, 0x1b, 0x2, 0x161, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x161, 
    0x15e, 0x3, 0x2, 0x2, 0x2, 0x162, 0x35, 0x3, 0x2, 0x2, 0x2, 0x163, 0x164, 
    0x5, 0x38, 0x1d, 0x2, 0x164, 0x165, 0x7, 0x19a, 0x2, 0x2, 0x165, 0x166, 
    0x5, 0x3a, 0x1e, 0x2, 0x166, 0x167, 0x7, 0x19b, 0x2, 0x2, 0x167, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x7, 0x1ac, 0x2, 0x2, 0x169, 0x16f, 
    0x7, 0x1c1, 0x2, 0x2, 0x16a, 0x16b, 0x7, 0x1ac, 0x2, 0x2, 0x16b, 0x16c, 
    0x7, 0x1c1, 0x2, 0x2, 0x16c, 0x16d, 0x7, 0x1ad, 0x2, 0x2, 0x16d, 0x16f, 
    0x7, 0x1c1, 0x2, 0x2, 0x16e, 0x168, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x16a, 
    0x3, 0x2, 0x2, 0x2, 0x16f, 0x39, 0x3, 0x2, 0x2, 0x2, 0x170, 0x171, 0x5, 
    0x1e, 0x10, 0x2, 0x171, 0x172, 0x7, 0x196, 0x2, 0x2, 0x172, 0x178, 0x3, 
    0x2, 0x2, 0x2, 0x173, 0x174, 0x5, 0x1e, 0x10, 0x2, 0x174, 0x175, 0x7, 
    0x196, 0x2, 0x2, 0x175, 0x176, 0x5, 0x3a, 0x1e, 0x2, 0x176, 0x178, 0x3, 
    0x2, 0x2, 0x2, 0x177, 0x170, 0x3, 0x2, 0x2, 0x2, 0x177, 0x173, 0x3, 
    0x2, 0x2, 0x2, 0x178, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x179, 0x17a, 0x5, 0x1e, 
    0x10, 0x2, 0x17a, 0x17b, 0x7, 0x196, 0x2, 0x2, 0x17b, 0x181, 0x3, 0x2, 
    0x2, 0x2, 0x17c, 0x17d, 0x5, 0x1e, 0x10, 0x2, 0x17d, 0x17e, 0x7, 0x196, 
    0x2, 0x2, 0x17e, 0x17f, 0x5, 0x3c, 0x1f, 0x2, 0x17f, 0x181, 0x3, 0x2, 
    0x2, 0x2, 0x180, 0x179, 0x3, 0x2, 0x2, 0x2, 0x180, 0x17c, 0x3, 0x2, 
    0x2, 0x2, 0x181, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x50, 0x76, 0x86, 0x8d, 
    0xa8, 0xb0, 0xc7, 0xcd, 0xd4, 0xda, 0xe5, 0xeb, 0xf1, 0xf8, 0x106, 0x10c, 
    0x124, 0x13b, 0x14d, 0x159, 0x161, 0x16e, 0x177, 0x180, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

DLParser::Initializer DLParser::_init;
