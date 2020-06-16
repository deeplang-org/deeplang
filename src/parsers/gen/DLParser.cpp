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


#include "DLParserListener.h"
#include "DLParserVisitor.h"

#include "DLParser.h"


#include "MySQLBaseRecognizer.h"


using namespace antlrcpp;
using namespace antlr4;

DLParser::DLParser(TokenStream *input) : DLBaseRecognizer(input) {
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
    setState(75);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(68);
        match(DLParser::CONST);
        break;
      }

      case DLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(69);
        match(DLParser::IDENTIFIER);
        break;
      }

      case DLParser::QUOTED_STRING: {
        enterOuterAlt(_localctx, 3);
        setState(70);
        match(DLParser::QUOTED_STRING);
        break;
      }

      case DLParser::OPEN_PAR_SYMBOL: {
        enterOuterAlt(_localctx, 4);
        setState(71);
        match(DLParser::OPEN_PAR_SYMBOL);
        setState(72);
        exp();
        setState(73);
        match(DLParser::CLOSE_PAR_SYMBOL);
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

//----------------- ArrayExpContext ------------------------------------------------------------------

DLParser::ArrayExpContext::ArrayExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::ArrayExpContext::OPEN_SQUARE_SYMBOL() {
  return getToken(DLParser::OPEN_SQUARE_SYMBOL, 0);
}

tree::TerminalNode* DLParser::ArrayExpContext::CLOSE_SQUARE_SYMBOL() {
  return getToken(DLParser::CLOSE_SQUARE_SYMBOL, 0);
}

DLParser::ExpListContext* DLParser::ArrayExpContext::expList() {
  return getRuleContext<DLParser::ExpListContext>(0);
}

DLParser::ArrayAccessExpContext* DLParser::ArrayExpContext::arrayAccessExp() {
  return getRuleContext<DLParser::ArrayAccessExpContext>(0);
}

DLParser::ArrayPatternMatchExpContext* DLParser::ArrayExpContext::arrayPatternMatchExp() {
  return getRuleContext<DLParser::ArrayPatternMatchExpContext>(0);
}


size_t DLParser::ArrayExpContext::getRuleIndex() const {
  return DLParser::RuleArrayExp;
}

void DLParser::ArrayExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayExp(this);
}

void DLParser::ArrayExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayExp(this);
}


antlrcpp::Any DLParser::ArrayExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitArrayExp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ArrayExpContext* DLParser::arrayExp() {
  ArrayExpContext *_localctx = _tracker.createInstance<ArrayExpContext>(_ctx, getState());
  enterRule(_localctx, 2, DLParser::RuleArrayExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(85);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(77);
      match(DLParser::OPEN_SQUARE_SYMBOL);
      setState(78);
      match(DLParser::CLOSE_SQUARE_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(79);
      match(DLParser::OPEN_SQUARE_SYMBOL);
      setState(80);
      expList();
      setState(81);
      match(DLParser::CLOSE_SQUARE_SYMBOL);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(83);
      arrayAccessExp();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(84);
      arrayPatternMatchExp();
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

//----------------- ArrayAccessExpContext ------------------------------------------------------------------

DLParser::ArrayAccessExpContext::ArrayAccessExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DLParser::ExpContext *> DLParser::ArrayAccessExpContext::exp() {
  return getRuleContexts<DLParser::ExpContext>();
}

DLParser::ExpContext* DLParser::ArrayAccessExpContext::exp(size_t i) {
  return getRuleContext<DLParser::ExpContext>(i);
}

tree::TerminalNode* DLParser::ArrayAccessExpContext::OPEN_SQUARE_SYMBOL() {
  return getToken(DLParser::OPEN_SQUARE_SYMBOL, 0);
}

tree::TerminalNode* DLParser::ArrayAccessExpContext::CLOSE_SQUARE_SYMBOL() {
  return getToken(DLParser::CLOSE_SQUARE_SYMBOL, 0);
}


size_t DLParser::ArrayAccessExpContext::getRuleIndex() const {
  return DLParser::RuleArrayAccessExp;
}

void DLParser::ArrayAccessExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayAccessExp(this);
}

void DLParser::ArrayAccessExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayAccessExp(this);
}


antlrcpp::Any DLParser::ArrayAccessExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitArrayAccessExp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ArrayAccessExpContext* DLParser::arrayAccessExp() {
  ArrayAccessExpContext *_localctx = _tracker.createInstance<ArrayAccessExpContext>(_ctx, getState());
  enterRule(_localctx, 4, DLParser::RuleArrayAccessExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    exp();
    setState(88);
    match(DLParser::OPEN_SQUARE_SYMBOL);
    setState(89);
    exp();
    setState(90);
    match(DLParser::CLOSE_SQUARE_SYMBOL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayPatternMatchExpContext ------------------------------------------------------------------

DLParser::ArrayPatternMatchExpContext::ArrayPatternMatchExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::ExpContext* DLParser::ArrayPatternMatchExpContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}

tree::TerminalNode* DLParser::ArrayPatternMatchExpContext::AT_SIGN_SYMBOL() {
  return getToken(DLParser::AT_SIGN_SYMBOL, 0);
}

tree::TerminalNode* DLParser::ArrayPatternMatchExpContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::ArrayPatternMatchExpContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

DLParser::ExpListContext* DLParser::ArrayPatternMatchExpContext::expList() {
  return getRuleContext<DLParser::ExpListContext>(0);
}

tree::TerminalNode* DLParser::ArrayPatternMatchExpContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}


size_t DLParser::ArrayPatternMatchExpContext::getRuleIndex() const {
  return DLParser::RuleArrayPatternMatchExp;
}

void DLParser::ArrayPatternMatchExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayPatternMatchExp(this);
}

void DLParser::ArrayPatternMatchExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayPatternMatchExp(this);
}


antlrcpp::Any DLParser::ArrayPatternMatchExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitArrayPatternMatchExp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ArrayPatternMatchExpContext* DLParser::arrayPatternMatchExp() {
  ArrayPatternMatchExpContext *_localctx = _tracker.createInstance<ArrayPatternMatchExpContext>(_ctx, getState());
  enterRule(_localctx, 6, DLParser::RuleArrayPatternMatchExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    exp();
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
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallExpContext ------------------------------------------------------------------

DLParser::CallExpContext::CallExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::ExpContext* DLParser::CallExpContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}

tree::TerminalNode* DLParser::CallExpContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

tree::TerminalNode* DLParser::CallExpContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}

DLParser::ExpListContext* DLParser::CallExpContext::expList() {
  return getRuleContext<DLParser::ExpListContext>(0);
}


size_t DLParser::CallExpContext::getRuleIndex() const {
  return DLParser::RuleCallExp;
}

void DLParser::CallExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallExp(this);
}

void DLParser::CallExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallExp(this);
}


antlrcpp::Any DLParser::CallExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitCallExp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::CallExpContext* DLParser::callExp() {
  CallExpContext *_localctx = _tracker.createInstance<CallExpContext>(_ctx, getState());
  enterRule(_localctx, 8, DLParser::RuleCallExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(108);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(99);
      exp();
      setState(100);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(101);
      match(DLParser::CLOSE_PAR_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(103);
      exp();
      setState(104);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(105);
      expList();
      setState(106);
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

//----------------- PointExpContext ------------------------------------------------------------------

DLParser::PointExpContext::PointExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::ExpContext* DLParser::PointExpContext::exp() {
  return getRuleContext<DLParser::ExpContext>(0);
}

tree::TerminalNode* DLParser::PointExpContext::DOT_SYMBOL() {
  return getToken(DLParser::DOT_SYMBOL, 0);
}

tree::TerminalNode* DLParser::PointExpContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}


size_t DLParser::PointExpContext::getRuleIndex() const {
  return DLParser::RulePointExp;
}

void DLParser::PointExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPointExp(this);
}

void DLParser::PointExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPointExp(this);
}


antlrcpp::Any DLParser::PointExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitPointExp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::PointExpContext* DLParser::pointExp() {
  PointExpContext *_localctx = _tracker.createInstance<PointExpContext>(_ctx, getState());
  enterRule(_localctx, 10, DLParser::RulePointExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    exp();
    setState(111);
    match(DLParser::DOT_SYMBOL);
    setState(112);
    match(DLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OpExpContext ------------------------------------------------------------------

DLParser::OpExpContext::OpExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DLParser::ExpContext *> DLParser::OpExpContext::exp() {
  return getRuleContexts<DLParser::ExpContext>();
}

DLParser::ExpContext* DLParser::OpExpContext::exp(size_t i) {
  return getRuleContext<DLParser::ExpContext>(i);
}

DLParser::AryOpContext* DLParser::OpExpContext::aryOp() {
  return getRuleContext<DLParser::AryOpContext>(0);
}

DLParser::UnAryOpContext* DLParser::OpExpContext::unAryOp() {
  return getRuleContext<DLParser::UnAryOpContext>(0);
}


size_t DLParser::OpExpContext::getRuleIndex() const {
  return DLParser::RuleOpExp;
}

void DLParser::OpExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpExp(this);
}

void DLParser::OpExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpExp(this);
}


antlrcpp::Any DLParser::OpExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitOpExp(this);
  else
    return visitor->visitChildren(this);
}

DLParser::OpExpContext* DLParser::opExp() {
  OpExpContext *_localctx = _tracker.createInstance<OpExpContext>(_ctx, getState());
  enterRule(_localctx, 12, DLParser::RuleOpExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::CONST:
      case DLParser::IDENTIFIER:
      case DLParser::QUOTED_STRING:
      case DLParser::OPEN_PAR_SYMBOL: {
        enterOuterAlt(_localctx, 1);
        setState(114);
        exp();
        setState(115);
        aryOp();
        setState(116);
        exp();
        break;
      }

      case DLParser::BITWISE_AND_OPERATOR:
      case DLParser::LOGICAL_NOT_OPERATOR:
      case DLParser::BITWISE_NOT_OPERATOR: {
        enterOuterAlt(_localctx, 2);
        setState(118);
        unAryOp();
        setState(119);
        exp();
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
  enterRule(_localctx, 14, DLParser::RuleAryOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    _la = _input->LA(1);
    if (!(((((_la - 387) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 387)) & ((1ULL << (DLParser::PLUS_OPERATOR - 387))
      | (1ULL << (DLParser::MINUS_OPERATOR - 387))
      | (1ULL << (DLParser::MULT_OPERATOR - 387))
      | (1ULL << (DLParser::DIV_OPERATOR - 387))
      | (1ULL << (DLParser::MOD_OPERATOR - 387))
      | (1ULL << (DLParser::ASSIGN_OPERATOR - 387))
      | (1ULL << (DLParser::EQUAL_OPERATOR - 387))
      | (1ULL << (DLParser::LOGICAL_AND_OPERATOR - 387))
      | (1ULL << (DLParser::LOGICAL_OR_OPERATOR - 387)))) != 0))) {
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
  enterRule(_localctx, 16, DLParser::RuleUnAryOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    _la = _input->LA(1);
    if (!(((((_la - 396) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 396)) & ((1ULL << (DLParser::BITWISE_AND_OPERATOR - 396))
      | (1ULL << (DLParser::LOGICAL_NOT_OPERATOR - 396))
      | (1ULL << (DLParser::BITWISE_NOT_OPERATOR - 396)))) != 0))) {
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
  enterRule(_localctx, 18, DLParser::RuleNewExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(137);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(127);
      match(DLParser::NEW_SYMBOL);
      setState(128);
      match(DLParser::IDENTIFIER);
      setState(129);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(130);
      match(DLParser::CLOSE_PAR_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(131);
      match(DLParser::NEW_SYMBOL);
      setState(132);
      match(DLParser::IDENTIFIER);
      setState(133);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(134);
      expList();
      setState(135);
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
  enterRule(_localctx, 20, DLParser::RuleExpList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(144);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(139);
      exp();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(140);
      exp();
      setState(141);
      match(DLParser::COMMA_SYMBOL);
      setState(142);
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

tree::TerminalNode* DLParser::StatementContext::THEN_SYMBOL() {
  return getToken(DLParser::THEN_SYMBOL, 0);
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
  enterRule(_localctx, 22, DLParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(173);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(146);
      match(DLParser::IF_SYMBOL);
      setState(147);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(148);
      exp();
      setState(149);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(150);
      match(DLParser::THEN_SYMBOL);
      setState(151);
      compoundBlock();
      setState(152);
      match(DLParser::ELSE_SYMBOL);
      setState(153);
      compoundBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(155);
      match(DLParser::IF_SYMBOL);
      setState(156);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(157);
      exp();
      setState(158);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(159);
      match(DLParser::THEN_SYMBOL);
      setState(160);
      compoundBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(162);
      match(DLParser::FOR_SYMBOL);
      setState(163);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(164);
      compoundBlock();
      setState(165);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(166);
      exp();
      setState(167);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(168);
      exp();
      setState(169);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(170);
      compoundBlock();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(172);
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
  enterRule(_localctx, 24, DLParser::RuleCompoundBlock);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(181);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(175);
      match(DLParser::OPEN_CURLY_SYMBOL);
      setState(176);
      match(DLParser::CLOSE_CURLY_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(177);
      match(DLParser::OPEN_CURLY_SYMBOL);
      setState(178);
      blockList();
      setState(179);
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
  enterRule(_localctx, 26, DLParser::RuleBlockList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(204);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(183);
      statement();
      setState(184);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(186);
      statement();
      setState(187);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(188);
      blockList();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(190);
      exp();
      setState(191);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(193);
      exp();
      setState(194);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(195);
      blockList();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(197);
      decl();
      setState(198);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(200);
      decl();
      setState(201);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(202);
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
  enterRule(_localctx, 28, DLParser::RuleJumpStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(206);
      match(DLParser::BREAK_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(207);
      match(DLParser::RETURN_SYMBOL);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(208);
      match(DLParser::RETURN_SYMBOL);
      setState(209);
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
  enterRule(_localctx, 30, DLParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    match(DLParser::IDENTIFIER);
   
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
  enterRule(_localctx, 32, DLParser::RuleFunctionType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    type();
    setState(215);
    match(DLParser::JSON_SEPARATOR_SYMBOL);
    setState(216);
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
  enterRule(_localctx, 34, DLParser::RuleRefType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(223);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(218);
      match(DLParser::BITWISE_AND_OPERATOR);
      setState(219);
      type();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(220);
      match(DLParser::BITWISE_AND_OPERATOR);
      setState(221);
      match(DLParser::MUT_SYMBOL);
      setState(222);
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
  enterRule(_localctx, 36, DLParser::RuleDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(229);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::SEMICOLON_SYMBOL:
      case DLParser::SIG_SYMBOL:
      case DLParser::FUN_SYMBOL: {
        enterOuterAlt(_localctx, 1);
        setState(225);
        functionDecl();
        break;
      }

      case DLParser::LET_SYMBOL:
      case DLParser::LETMUT_SYMBOL: {
        enterOuterAlt(_localctx, 2);
        setState(226);
        varDecl();
        break;
      }

      case DLParser::CLASS_SYMBOL: {
        enterOuterAlt(_localctx, 3);
        setState(227);
        classDecl();
        break;
      }

      case DLParser::INTERFACE_SYMBOL: {
        enterOuterAlt(_localctx, 4);
        setState(228);
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
  enterRule(_localctx, 38, DLParser::RuleFunctionDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(235);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(231);
      signature();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(232);
      signature();
      setState(233);
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
  enterRule(_localctx, 40, DLParser::RuleSignature);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::SEMICOLON_SYMBOL:
      case DLParser::FUN_SYMBOL: {
        enterOuterAlt(_localctx, 1);

        break;
      }

      case DLParser::SIG_SYMBOL: {
        enterOuterAlt(_localctx, 2);
        setState(238);
        match(DLParser::SIG_SYMBOL);
        setState(239);
        match(DLParser::IDENTIFIER);
        setState(240);
        match(DLParser::ALIAS_SYMBOL);
        setState(241);
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
  enterRule(_localctx, 42, DLParser::RuleFunctionDef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(256);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(244);
      match(DLParser::FUN_SYMBOL);
      setState(245);
      match(DLParser::IDENTIFIER);
      setState(246);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(247);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(248);
      compoundBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(249);
      match(DLParser::FUN_SYMBOL);
      setState(250);
      match(DLParser::IDENTIFIER);
      setState(251);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(252);
      paramList();
      setState(253);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(254);
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
  enterRule(_localctx, 44, DLParser::RuleParamList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(258);
      match(DLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(259);
      match(DLParser::IDENTIFIER);
      setState(260);
      match(DLParser::COMMA_SYMBOL);
      setState(261);
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
  enterRule(_localctx, 46, DLParser::RuleVarDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(286);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(264);
      match(DLParser::LET_SYMBOL);
      setState(265);
      match(DLParser::IDENTIFIER);
      setState(266);
      match(DLParser::COLON_SYMBOL);
      setState(267);
      type();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(268);
      match(DLParser::LET_SYMBOL);
      setState(269);
      match(DLParser::IDENTIFIER);
      setState(270);
      match(DLParser::COLON_SYMBOL);
      setState(271);
      type();
      setState(272);
      match(DLParser::EQUAL_OPERATOR);
      setState(273);
      exp();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(275);
      match(DLParser::LETMUT_SYMBOL);
      setState(276);
      match(DLParser::IDENTIFIER);
      setState(277);
      match(DLParser::COLON_SYMBOL);
      setState(278);
      type();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(279);
      match(DLParser::LETMUT_SYMBOL);
      setState(280);
      match(DLParser::IDENTIFIER);
      setState(281);
      match(DLParser::COLON_SYMBOL);
      setState(282);
      type();
      setState(283);
      match(DLParser::EQUAL_OPERATOR);
      setState(284);
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
  enterRule(_localctx, 48, DLParser::RuleClassDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    classHead();
    setState(289);
    match(DLParser::OPEN_CURLY_SYMBOL);
    setState(290);
    classBody();
    setState(291);
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
  enterRule(_localctx, 50, DLParser::RuleClassHead);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(309);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(293);
      match(DLParser::CLASS_SYMBOL);
      setState(294);
      match(DLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(295);
      match(DLParser::CLASS_SYMBOL);
      setState(296);
      match(DLParser::IDENTIFIER);
      setState(297);
      match(DLParser::EXTENDS_SYMBOL);
      setState(298);
      match(DLParser::IDENTIFIER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(299);
      match(DLParser::CLASS_SYMBOL);
      setState(300);
      match(DLParser::IDENTIFIER);
      setState(301);
      match(DLParser::IMPL_SYMBOL);
      setState(302);
      interfaceList();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(303);
      match(DLParser::CLASS_SYMBOL);
      setState(304);
      match(DLParser::IDENTIFIER);
      setState(305);
      match(DLParser::EXTENDS_SYMBOL);
      setState(306);
      match(DLParser::IDENTIFIER);
      setState(307);
      match(DLParser::IMPL_SYMBOL);
      setState(308);
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
  enterRule(_localctx, 52, DLParser::RuleClassBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(327);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(311);
      accessSpecifier();
      setState(312);
      decl();
      setState(313);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(315);
      accessSpecifier();
      setState(316);
      decl();
      setState(317);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(318);
      classBody();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(320);
      constructor();
      setState(321);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(323);
      constructor();
      setState(324);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(325);
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

tree::TerminalNode* DLParser::ConstructorContext::SEMICOLON_SYMBOL() {
  return getToken(DLParser::SEMICOLON_SYMBOL, 0);
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
  enterRule(_localctx, 54, DLParser::RuleConstructor);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(342);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(329);
      match(DLParser::CONSTRUCTOR_SYMBOL);
      setState(330);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(331);
      paramList();
      setState(332);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(333);
      compoundBlock();
      setState(334);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(336);
      match(DLParser::CONSTRUCTOR_SYMBOL);
      setState(337);
      match(DLParser::OPEN_PAR_SYMBOL);
      setState(338);
      match(DLParser::CLOSE_PAR_SYMBOL);
      setState(339);
      compoundBlock();
      setState(340);
      match(DLParser::SEMICOLON_SYMBOL);
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
  enterRule(_localctx, 56, DLParser::RuleAccessSpecifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(344);
    _la = _input->LA(1);
    if (!(_la == DLParser::PRIVATE_SYMBOL

    || _la == DLParser::PUBLIC_SYMBOL)) {
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
  enterRule(_localctx, 58, DLParser::RuleInterfaceList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(350);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(346);
      match(DLParser::INTERFACE_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(347);
      match(DLParser::INTERFACE_SYMBOL);
      setState(348);
      match(DLParser::COMMA_SYMBOL);
      setState(349);
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
  enterRule(_localctx, 60, DLParser::RuleInterfaceDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    interfaceHead();
    setState(353);
    match(DLParser::OPEN_CURLY_SYMBOL);
    setState(354);
    interfaceBody();
    setState(355);
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
  enterRule(_localctx, 62, DLParser::RuleInterfaceHead);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(363);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(357);
      match(DLParser::INTERFACE_SYMBOL);
      setState(358);
      match(DLParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(359);
      match(DLParser::INTERFACE_SYMBOL);
      setState(360);
      match(DLParser::IDENTIFIER);
      setState(361);
      match(DLParser::EXTENDS_SYMBOL);
      setState(362);
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
  enterRule(_localctx, 64, DLParser::RuleInterfaceBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(372);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(365);
      decl();
      setState(366);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(368);
      decl();
      setState(369);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(370);
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
  enterRule(_localctx, 66, DLParser::RuleProgram);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(381);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(374);
      decl();
      setState(375);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(377);
      decl();
      setState(378);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(379);
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
  "exp", "arrayExp", "arrayAccessExp", "arrayPatternMatchExp", "callExp", 
  "pointExp", "opExp", "aryOp", "unAryOp", "newExp", "expList", "statement", 
  "compoundBlock", "blockList", "jumpStatement", "type", "functionType", 
  "refType", "decl", "functionDecl", "signature", "functionDef", "paramList", 
  "varDecl", "classDecl", "classHead", "classBody", "constructor", "accessSpecifier", 
  "interfaceList", "interfaceDecl", "interfaceHead", "interfaceBody", "program"
};

std::vector<std::string> DLParser::_literalNames = {
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
  "XID_SYMBOL", "XML_SYMBOL", "YEAR_SYMBOL", "CONST", "IDENTIFIER", "QUOTED_STRING", 
  "OPEN_PAR_SYMBOL", "CLOSE_PAR_SYMBOL", "OPEN_SQUARE_SYMBOL", "CLOSE_SQUARE_SYMBOL", 
  "AT_SIGN_SYMBOL", "DOT_SYMBOL", "PLUS_OPERATOR", "MINUS_OPERATOR", "MULT_OPERATOR", 
  "DIV_OPERATOR", "MOD_OPERATOR", "ASSIGN_OPERATOR", "EQUAL_OPERATOR", "LOGICAL_AND_OPERATOR", 
  "LOGICAL_OR_OPERATOR", "BITWISE_AND_OPERATOR", "LOGICAL_NOT_OPERATOR", 
  "BITWISE_NOT_OPERATOR", "COMMA_SYMBOL", "IF_SYMBOL", "THEN_SYMBOL", "ELSE_SYMBOL", 
  "FOR_SYMBOL", "SEMICOLON_SYMBOL", "OPEN_CURLY_SYMBOL", "CLOSE_CURLY_SYMBOL", 
  "BREAK_SYMBOL", "RETURN_SYMBOL", "JSON_SEPARATOR_SYMBOL", "MUT_SYMBOL", 
  "SIG_SYMBOL", "ALIAS_SYMBOL", "FUN_SYMBOL", "LET_SYMBOL", "COLON_SYMBOL", 
  "LETMUT_SYMBOL", "CLASS_SYMBOL", "EXTENDS_SYMBOL", "IMPL_SYMBOL", "CONSTRUCTOR_SYMBOL", 
  "PRIVATE_SYMBOL", "PUBLIC_SYMBOL", "INTERFACE_SYMBOL"
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
    0x3, 0x1a9, 0x182, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x4e, 0xa, 0x2, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x5, 0x3, 0x58, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x6f, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x7c, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x8c, 0xa, 0xb, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x93, 0xa, 
    0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 
    0xd, 0xb0, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x5, 0xe, 0xb8, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xcf, 0xa, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xd5, 0xa, 0x10, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xe2, 0xa, 0x13, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0xe8, 0xa, 0x14, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0xee, 0xa, 0x15, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0xf5, 0xa, 
    0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 
    0x17, 0x103, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x5, 0x18, 0x109, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x121, 
    0xa, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x138, 0xa, 0x1b, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x14a, 0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x159, 
    0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x5, 0x1f, 0x161, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 
    0x21, 0x3, 0x21, 0x5, 0x21, 0x16e, 0xa, 0x21, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x177, 
    0xa, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x5, 0x23, 0x180, 0xa, 0x23, 0x3, 0x23, 0x2, 0x2, 0x24, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 
    0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 
    0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x2, 0x5, 0x3, 
    0x2, 0x185, 0x18d, 0x3, 0x2, 0x18e, 0x190, 0x3, 0x2, 0x1a7, 0x1a8, 0x2, 
    0x18a, 0x2, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4, 0x57, 0x3, 0x2, 0x2, 0x2, 
    0x6, 0x59, 0x3, 0x2, 0x2, 0x2, 0x8, 0x5e, 0x3, 0x2, 0x2, 0x2, 0xa, 0x6e, 
    0x3, 0x2, 0x2, 0x2, 0xc, 0x70, 0x3, 0x2, 0x2, 0x2, 0xe, 0x7b, 0x3, 0x2, 
    0x2, 0x2, 0x10, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x12, 0x7f, 0x3, 0x2, 0x2, 
    0x2, 0x14, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x16, 0x92, 0x3, 0x2, 0x2, 0x2, 
    0x18, 0xaf, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xb7, 0x3, 0x2, 0x2, 0x2, 0x1c, 
    0xce, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xd4, 0x3, 0x2, 0x2, 0x2, 0x20, 0xd6, 
    0x3, 0x2, 0x2, 0x2, 0x22, 0xd8, 0x3, 0x2, 0x2, 0x2, 0x24, 0xe1, 0x3, 
    0x2, 0x2, 0x2, 0x26, 0xe7, 0x3, 0x2, 0x2, 0x2, 0x28, 0xed, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0xf4, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x102, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0x108, 0x3, 0x2, 0x2, 0x2, 0x30, 0x120, 0x3, 0x2, 0x2, 0x2, 
    0x32, 0x122, 0x3, 0x2, 0x2, 0x2, 0x34, 0x137, 0x3, 0x2, 0x2, 0x2, 0x36, 
    0x149, 0x3, 0x2, 0x2, 0x2, 0x38, 0x158, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x15a, 
    0x3, 0x2, 0x2, 0x2, 0x3c, 0x160, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x162, 0x3, 
    0x2, 0x2, 0x2, 0x40, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x42, 0x176, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x46, 0x4e, 0x7, 0x17c, 0x2, 
    0x2, 0x47, 0x4e, 0x7, 0x17d, 0x2, 0x2, 0x48, 0x4e, 0x7, 0x17e, 0x2, 
    0x2, 0x49, 0x4a, 0x7, 0x17f, 0x2, 0x2, 0x4a, 0x4b, 0x5, 0x2, 0x2, 0x2, 
    0x4b, 0x4c, 0x7, 0x180, 0x2, 0x2, 0x4c, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4d, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x47, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x48, 
    0x3, 0x2, 0x2, 0x2, 0x4d, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x181, 0x2, 0x2, 0x50, 0x58, 0x7, 0x182, 
    0x2, 0x2, 0x51, 0x52, 0x7, 0x181, 0x2, 0x2, 0x52, 0x53, 0x5, 0x16, 0xc, 
    0x2, 0x53, 0x54, 0x7, 0x182, 0x2, 0x2, 0x54, 0x58, 0x3, 0x2, 0x2, 0x2, 
    0x55, 0x58, 0x5, 0x6, 0x4, 0x2, 0x56, 0x58, 0x5, 0x8, 0x5, 0x2, 0x57, 
    0x4f, 0x3, 0x2, 0x2, 0x2, 0x57, 0x51, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 
    0x3, 0x2, 0x2, 0x2, 0x57, 0x56, 0x3, 0x2, 0x2, 0x2, 0x58, 0x5, 0x3, 
    0x2, 0x2, 0x2, 0x59, 0x5a, 0x5, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x7, 0x181, 
    0x2, 0x2, 0x5b, 0x5c, 0x5, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0x182, 0x2, 
    0x2, 0x5d, 0x7, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x5, 0x2, 0x2, 0x2, 
    0x5f, 0x60, 0x7, 0x183, 0x2, 0x2, 0x60, 0x61, 0x7, 0x17d, 0x2, 0x2, 
    0x61, 0x62, 0x7, 0x17f, 0x2, 0x2, 0x62, 0x63, 0x5, 0x16, 0xc, 0x2, 0x63, 
    0x64, 0x7, 0x180, 0x2, 0x2, 0x64, 0x9, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 
    0x5, 0x2, 0x2, 0x2, 0x66, 0x67, 0x7, 0x17f, 0x2, 0x2, 0x67, 0x68, 0x7, 
    0x180, 0x2, 0x2, 0x68, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x5, 0x2, 
    0x2, 0x2, 0x6a, 0x6b, 0x7, 0x17f, 0x2, 0x2, 0x6b, 0x6c, 0x5, 0x16, 0xc, 
    0x2, 0x6c, 0x6d, 0x7, 0x180, 0x2, 0x2, 0x6d, 0x6f, 0x3, 0x2, 0x2, 0x2, 
    0x6e, 0x65, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6f, 
    0xb, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0x5, 0x2, 0x2, 0x2, 0x71, 0x72, 
    0x7, 0x184, 0x2, 0x2, 0x72, 0x73, 0x7, 0x17d, 0x2, 0x2, 0x73, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0x74, 0x75, 0x5, 0x2, 0x2, 0x2, 0x75, 0x76, 0x5, 0x10, 
    0x9, 0x2, 0x76, 0x77, 0x5, 0x2, 0x2, 0x2, 0x77, 0x7c, 0x3, 0x2, 0x2, 
    0x2, 0x78, 0x79, 0x5, 0x12, 0xa, 0x2, 0x79, 0x7a, 0x5, 0x2, 0x2, 0x2, 
    0x7a, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x74, 0x3, 0x2, 0x2, 0x2, 0x7b, 
    0x78, 0x3, 0x2, 0x2, 0x2, 0x7c, 0xf, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 
    0x9, 0x2, 0x2, 0x2, 0x7e, 0x11, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x80, 0x9, 
    0x3, 0x2, 0x2, 0x80, 0x13, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x7, 0xee, 
    0x2, 0x2, 0x82, 0x83, 0x7, 0x17d, 0x2, 0x2, 0x83, 0x84, 0x7, 0x17f, 
    0x2, 0x2, 0x84, 0x8c, 0x7, 0x180, 0x2, 0x2, 0x85, 0x86, 0x7, 0xee, 0x2, 
    0x2, 0x86, 0x87, 0x7, 0x17d, 0x2, 0x2, 0x87, 0x88, 0x7, 0x17f, 0x2, 
    0x2, 0x88, 0x89, 0x5, 0x16, 0xc, 0x2, 0x89, 0x8a, 0x7, 0x180, 0x2, 0x2, 
    0x8a, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x81, 0x3, 0x2, 0x2, 0x2, 0x8b, 
    0x85, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x15, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x93, 
    0x5, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x5, 0x2, 0x2, 0x2, 0x8f, 0x90, 0x7, 
    0x191, 0x2, 0x2, 0x90, 0x91, 0x5, 0x16, 0xc, 0x2, 0x91, 0x93, 0x3, 0x2, 
    0x2, 0x2, 0x92, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x92, 0x8e, 0x3, 0x2, 0x2, 
    0x2, 0x93, 0x17, 0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 0x7, 0x192, 0x2, 0x2, 
    0x95, 0x96, 0x7, 0x17f, 0x2, 0x2, 0x96, 0x97, 0x5, 0x2, 0x2, 0x2, 0x97, 
    0x98, 0x7, 0x180, 0x2, 0x2, 0x98, 0x99, 0x7, 0x193, 0x2, 0x2, 0x99, 
    0x9a, 0x5, 0x1a, 0xe, 0x2, 0x9a, 0x9b, 0x7, 0x194, 0x2, 0x2, 0x9b, 0x9c, 
    0x5, 0x1a, 0xe, 0x2, 0x9c, 0xb0, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 0x7, 
    0x192, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x17f, 0x2, 0x2, 0x9f, 0xa0, 0x5, 
    0x2, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x180, 0x2, 0x2, 0xa1, 0xa2, 0x7, 0x193, 
    0x2, 0x2, 0xa2, 0xa3, 0x5, 0x1a, 0xe, 0x2, 0xa3, 0xb0, 0x3, 0x2, 0x2, 
    0x2, 0xa4, 0xa5, 0x7, 0x195, 0x2, 0x2, 0xa5, 0xa6, 0x7, 0x17f, 0x2, 
    0x2, 0xa6, 0xa7, 0x5, 0x1a, 0xe, 0x2, 0xa7, 0xa8, 0x7, 0x196, 0x2, 0x2, 
    0xa8, 0xa9, 0x5, 0x2, 0x2, 0x2, 0xa9, 0xaa, 0x7, 0x196, 0x2, 0x2, 0xaa, 
    0xab, 0x5, 0x2, 0x2, 0x2, 0xab, 0xac, 0x7, 0x180, 0x2, 0x2, 0xac, 0xad, 
    0x5, 0x1a, 0xe, 0x2, 0xad, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xae, 0xb0, 0x5, 
    0x1e, 0x10, 0x2, 0xaf, 0x94, 0x3, 0x2, 0x2, 0x2, 0xaf, 0x9d, 0x3, 0x2, 
    0x2, 0x2, 0xaf, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xae, 0x3, 0x2, 0x2, 
    0x2, 0xb0, 0x19, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x7, 0x197, 0x2, 0x2, 
    0xb2, 0xb8, 0x7, 0x198, 0x2, 0x2, 0xb3, 0xb4, 0x7, 0x197, 0x2, 0x2, 
    0xb4, 0xb5, 0x5, 0x1c, 0xf, 0x2, 0xb5, 0xb6, 0x7, 0x198, 0x2, 0x2, 0xb6, 
    0xb8, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb3, 
    0x3, 0x2, 0x2, 0x2, 0xb8, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 0x5, 
    0x18, 0xd, 0x2, 0xba, 0xbb, 0x7, 0x196, 0x2, 0x2, 0xbb, 0xcf, 0x3, 0x2, 
    0x2, 0x2, 0xbc, 0xbd, 0x5, 0x18, 0xd, 0x2, 0xbd, 0xbe, 0x7, 0x196, 0x2, 
    0x2, 0xbe, 0xbf, 0x5, 0x1c, 0xf, 0x2, 0xbf, 0xcf, 0x3, 0x2, 0x2, 0x2, 
    0xc0, 0xc1, 0x5, 0x2, 0x2, 0x2, 0xc1, 0xc2, 0x7, 0x196, 0x2, 0x2, 0xc2, 
    0xcf, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 0x5, 0x2, 0x2, 0x2, 0xc4, 0xc5, 
    0x7, 0x196, 0x2, 0x2, 0xc5, 0xc6, 0x5, 0x1c, 0xf, 0x2, 0xc6, 0xcf, 0x3, 
    0x2, 0x2, 0x2, 0xc7, 0xc8, 0x5, 0x26, 0x14, 0x2, 0xc8, 0xc9, 0x7, 0x196, 
    0x2, 0x2, 0xc9, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcb, 0x5, 0x26, 0x14, 
    0x2, 0xcb, 0xcc, 0x7, 0x196, 0x2, 0x2, 0xcc, 0xcd, 0x5, 0x1c, 0xf, 0x2, 
    0xcd, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xce, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xce, 
    0xbc, 0x3, 0x2, 0x2, 0x2, 0xce, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xce, 0xc3, 
    0x3, 0x2, 0x2, 0x2, 0xce, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xce, 0xca, 0x3, 
    0x2, 0x2, 0x2, 0xcf, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xd5, 0x7, 0x199, 
    0x2, 0x2, 0xd1, 0xd5, 0x7, 0x19a, 0x2, 0x2, 0xd2, 0xd3, 0x7, 0x19a, 
    0x2, 0x2, 0xd3, 0xd5, 0x5, 0x2, 0x2, 0x2, 0xd4, 0xd0, 0x3, 0x2, 0x2, 
    0x2, 0xd4, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd2, 0x3, 0x2, 0x2, 0x2, 
    0xd5, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd7, 0x7, 0x17d, 0x2, 0x2, 0xd7, 
    0x21, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x5, 0x20, 0x11, 0x2, 0xd9, 0xda, 
    0x7, 0x19b, 0x2, 0x2, 0xda, 0xdb, 0x5, 0x20, 0x11, 0x2, 0xdb, 0x23, 
    0x3, 0x2, 0x2, 0x2, 0xdc, 0xdd, 0x7, 0x18e, 0x2, 0x2, 0xdd, 0xe2, 0x5, 
    0x20, 0x11, 0x2, 0xde, 0xdf, 0x7, 0x18e, 0x2, 0x2, 0xdf, 0xe0, 0x7, 
    0x19c, 0x2, 0x2, 0xe0, 0xe2, 0x5, 0x20, 0x11, 0x2, 0xe1, 0xdc, 0x3, 
    0x2, 0x2, 0x2, 0xe1, 0xde, 0x3, 0x2, 0x2, 0x2, 0xe2, 0x25, 0x3, 0x2, 
    0x2, 0x2, 0xe3, 0xe8, 0x5, 0x28, 0x15, 0x2, 0xe4, 0xe8, 0x5, 0x30, 0x19, 
    0x2, 0xe5, 0xe8, 0x5, 0x32, 0x1a, 0x2, 0xe6, 0xe8, 0x5, 0x3e, 0x20, 
    0x2, 0xe7, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe4, 0x3, 0x2, 0x2, 0x2, 
    0xe7, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe8, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xee, 0x5, 0x2a, 0x16, 0x2, 0xea, 0xeb, 
    0x5, 0x2a, 0x16, 0x2, 0xeb, 0xec, 0x5, 0x2c, 0x17, 0x2, 0xec, 0xee, 
    0x3, 0x2, 0x2, 0x2, 0xed, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xed, 0xea, 0x3, 
    0x2, 0x2, 0x2, 0xee, 0x29, 0x3, 0x2, 0x2, 0x2, 0xef, 0xf5, 0x3, 0x2, 
    0x2, 0x2, 0xf0, 0xf1, 0x7, 0x19d, 0x2, 0x2, 0xf1, 0xf2, 0x7, 0x17d, 
    0x2, 0x2, 0xf2, 0xf3, 0x7, 0x19e, 0x2, 0x2, 0xf3, 0xf5, 0x5, 0x20, 0x11, 
    0x2, 0xf4, 0xef, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf0, 0x3, 0x2, 0x2, 0x2, 
    0xf5, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf7, 0x7, 0x19f, 0x2, 0x2, 0xf7, 
    0xf8, 0x7, 0x17d, 0x2, 0x2, 0xf8, 0xf9, 0x7, 0x17f, 0x2, 0x2, 0xf9, 
    0xfa, 0x7, 0x180, 0x2, 0x2, 0xfa, 0x103, 0x5, 0x1a, 0xe, 0x2, 0xfb, 
    0xfc, 0x7, 0x19f, 0x2, 0x2, 0xfc, 0xfd, 0x7, 0x17d, 0x2, 0x2, 0xfd, 
    0xfe, 0x7, 0x17f, 0x2, 0x2, 0xfe, 0xff, 0x5, 0x2e, 0x18, 0x2, 0xff, 
    0x100, 0x7, 0x180, 0x2, 0x2, 0x100, 0x101, 0x5, 0x1a, 0xe, 0x2, 0x101, 
    0x103, 0x3, 0x2, 0x2, 0x2, 0x102, 0xf6, 0x3, 0x2, 0x2, 0x2, 0x102, 0xfb, 
    0x3, 0x2, 0x2, 0x2, 0x103, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x104, 0x109, 0x7, 
    0x17d, 0x2, 0x2, 0x105, 0x106, 0x7, 0x17d, 0x2, 0x2, 0x106, 0x107, 0x7, 
    0x191, 0x2, 0x2, 0x107, 0x109, 0x5, 0x2e, 0x18, 0x2, 0x108, 0x104, 0x3, 
    0x2, 0x2, 0x2, 0x108, 0x105, 0x3, 0x2, 0x2, 0x2, 0x109, 0x2f, 0x3, 0x2, 
    0x2, 0x2, 0x10a, 0x10b, 0x7, 0x1a0, 0x2, 0x2, 0x10b, 0x10c, 0x7, 0x17d, 
    0x2, 0x2, 0x10c, 0x10d, 0x7, 0x1a1, 0x2, 0x2, 0x10d, 0x121, 0x5, 0x20, 
    0x11, 0x2, 0x10e, 0x10f, 0x7, 0x1a0, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x17d, 
    0x2, 0x2, 0x110, 0x111, 0x7, 0x1a1, 0x2, 0x2, 0x111, 0x112, 0x5, 0x20, 
    0x11, 0x2, 0x112, 0x113, 0x7, 0x18b, 0x2, 0x2, 0x113, 0x114, 0x5, 0x2, 
    0x2, 0x2, 0x114, 0x121, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 0x7, 0x1a2, 
    0x2, 0x2, 0x116, 0x117, 0x7, 0x17d, 0x2, 0x2, 0x117, 0x118, 0x7, 0x1a1, 
    0x2, 0x2, 0x118, 0x121, 0x5, 0x20, 0x11, 0x2, 0x119, 0x11a, 0x7, 0x1a2, 
    0x2, 0x2, 0x11a, 0x11b, 0x7, 0x17d, 0x2, 0x2, 0x11b, 0x11c, 0x7, 0x1a1, 
    0x2, 0x2, 0x11c, 0x11d, 0x5, 0x20, 0x11, 0x2, 0x11d, 0x11e, 0x7, 0x18b, 
    0x2, 0x2, 0x11e, 0x11f, 0x5, 0x2, 0x2, 0x2, 0x11f, 0x121, 0x3, 0x2, 
    0x2, 0x2, 0x120, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x120, 0x10e, 0x3, 0x2, 
    0x2, 0x2, 0x120, 0x115, 0x3, 0x2, 0x2, 0x2, 0x120, 0x119, 0x3, 0x2, 
    0x2, 0x2, 0x121, 0x31, 0x3, 0x2, 0x2, 0x2, 0x122, 0x123, 0x5, 0x34, 
    0x1b, 0x2, 0x123, 0x124, 0x7, 0x197, 0x2, 0x2, 0x124, 0x125, 0x5, 0x36, 
    0x1c, 0x2, 0x125, 0x126, 0x7, 0x198, 0x2, 0x2, 0x126, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x127, 0x128, 0x7, 0x1a3, 0x2, 0x2, 0x128, 0x138, 0x7, 0x17d, 
    0x2, 0x2, 0x129, 0x12a, 0x7, 0x1a3, 0x2, 0x2, 0x12a, 0x12b, 0x7, 0x17d, 
    0x2, 0x2, 0x12b, 0x12c, 0x7, 0x1a4, 0x2, 0x2, 0x12c, 0x138, 0x7, 0x17d, 
    0x2, 0x2, 0x12d, 0x12e, 0x7, 0x1a3, 0x2, 0x2, 0x12e, 0x12f, 0x7, 0x17d, 
    0x2, 0x2, 0x12f, 0x130, 0x7, 0x1a5, 0x2, 0x2, 0x130, 0x138, 0x5, 0x3c, 
    0x1f, 0x2, 0x131, 0x132, 0x7, 0x1a3, 0x2, 0x2, 0x132, 0x133, 0x7, 0x17d, 
    0x2, 0x2, 0x133, 0x134, 0x7, 0x1a4, 0x2, 0x2, 0x134, 0x135, 0x7, 0x17d, 
    0x2, 0x2, 0x135, 0x136, 0x7, 0x1a5, 0x2, 0x2, 0x136, 0x138, 0x5, 0x3c, 
    0x1f, 0x2, 0x137, 0x127, 0x3, 0x2, 0x2, 0x2, 0x137, 0x129, 0x3, 0x2, 
    0x2, 0x2, 0x137, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x137, 0x131, 0x3, 0x2, 
    0x2, 0x2, 0x138, 0x35, 0x3, 0x2, 0x2, 0x2, 0x139, 0x13a, 0x5, 0x3a, 
    0x1e, 0x2, 0x13a, 0x13b, 0x5, 0x26, 0x14, 0x2, 0x13b, 0x13c, 0x7, 0x196, 
    0x2, 0x2, 0x13c, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13e, 0x5, 0x3a, 
    0x1e, 0x2, 0x13e, 0x13f, 0x5, 0x26, 0x14, 0x2, 0x13f, 0x140, 0x7, 0x196, 
    0x2, 0x2, 0x140, 0x141, 0x5, 0x36, 0x1c, 0x2, 0x141, 0x14a, 0x3, 0x2, 
    0x2, 0x2, 0x142, 0x143, 0x5, 0x38, 0x1d, 0x2, 0x143, 0x144, 0x7, 0x196, 
    0x2, 0x2, 0x144, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 0x5, 0x38, 
    0x1d, 0x2, 0x146, 0x147, 0x7, 0x196, 0x2, 0x2, 0x147, 0x148, 0x5, 0x36, 
    0x1c, 0x2, 0x148, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x149, 0x139, 0x3, 0x2, 
    0x2, 0x2, 0x149, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x149, 0x142, 0x3, 0x2, 
    0x2, 0x2, 0x149, 0x145, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x14b, 0x14c, 0x7, 0x1a6, 0x2, 0x2, 0x14c, 0x14d, 0x7, 0x17f, 0x2, 
    0x2, 0x14d, 0x14e, 0x5, 0x2e, 0x18, 0x2, 0x14e, 0x14f, 0x7, 0x180, 0x2, 
    0x2, 0x14f, 0x150, 0x5, 0x1a, 0xe, 0x2, 0x150, 0x151, 0x7, 0x196, 0x2, 
    0x2, 0x151, 0x159, 0x3, 0x2, 0x2, 0x2, 0x152, 0x153, 0x7, 0x1a6, 0x2, 
    0x2, 0x153, 0x154, 0x7, 0x17f, 0x2, 0x2, 0x154, 0x155, 0x7, 0x180, 0x2, 
    0x2, 0x155, 0x156, 0x5, 0x1a, 0xe, 0x2, 0x156, 0x157, 0x7, 0x196, 0x2, 
    0x2, 0x157, 0x159, 0x3, 0x2, 0x2, 0x2, 0x158, 0x14b, 0x3, 0x2, 0x2, 
    0x2, 0x158, 0x152, 0x3, 0x2, 0x2, 0x2, 0x159, 0x39, 0x3, 0x2, 0x2, 0x2, 
    0x15a, 0x15b, 0x9, 0x4, 0x2, 0x2, 0x15b, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x15c, 
    0x161, 0x7, 0x1a9, 0x2, 0x2, 0x15d, 0x15e, 0x7, 0x1a9, 0x2, 0x2, 0x15e, 
    0x15f, 0x7, 0x191, 0x2, 0x2, 0x15f, 0x161, 0x5, 0x3c, 0x1f, 0x2, 0x160, 
    0x15c, 0x3, 0x2, 0x2, 0x2, 0x160, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x161, 
    0x3d, 0x3, 0x2, 0x2, 0x2, 0x162, 0x163, 0x5, 0x40, 0x21, 0x2, 0x163, 
    0x164, 0x7, 0x197, 0x2, 0x2, 0x164, 0x165, 0x5, 0x42, 0x22, 0x2, 0x165, 
    0x166, 0x7, 0x198, 0x2, 0x2, 0x166, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x167, 
    0x168, 0x7, 0x1a9, 0x2, 0x2, 0x168, 0x16e, 0x7, 0x17d, 0x2, 0x2, 0x169, 
    0x16a, 0x7, 0x1a9, 0x2, 0x2, 0x16a, 0x16b, 0x7, 0x17d, 0x2, 0x2, 0x16b, 
    0x16c, 0x7, 0x1a4, 0x2, 0x2, 0x16c, 0x16e, 0x7, 0x17d, 0x2, 0x2, 0x16d, 
    0x167, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x169, 0x3, 0x2, 0x2, 0x2, 0x16e, 
    0x41, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0x5, 0x26, 0x14, 0x2, 0x170, 
    0x171, 0x7, 0x196, 0x2, 0x2, 0x171, 0x177, 0x3, 0x2, 0x2, 0x2, 0x172, 
    0x173, 0x5, 0x26, 0x14, 0x2, 0x173, 0x174, 0x7, 0x196, 0x2, 0x2, 0x174, 
    0x175, 0x5, 0x42, 0x22, 0x2, 0x175, 0x177, 0x3, 0x2, 0x2, 0x2, 0x176, 
    0x16f, 0x3, 0x2, 0x2, 0x2, 0x176, 0x172, 0x3, 0x2, 0x2, 0x2, 0x177, 
    0x43, 0x3, 0x2, 0x2, 0x2, 0x178, 0x179, 0x5, 0x26, 0x14, 0x2, 0x179, 
    0x17a, 0x7, 0x196, 0x2, 0x2, 0x17a, 0x180, 0x3, 0x2, 0x2, 0x2, 0x17b, 
    0x17c, 0x5, 0x26, 0x14, 0x2, 0x17c, 0x17d, 0x7, 0x196, 0x2, 0x2, 0x17d, 
    0x17e, 0x5, 0x44, 0x23, 0x2, 0x17e, 0x180, 0x3, 0x2, 0x2, 0x2, 0x17f, 
    0x178, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x180, 
    0x45, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x4d, 0x57, 0x6e, 0x7b, 0x8b, 0x92, 
    0xaf, 0xb7, 0xce, 0xd4, 0xe1, 0xe7, 0xed, 0xf4, 0x102, 0x108, 0x120, 
    0x137, 0x149, 0x158, 0x160, 0x16d, 0x176, 0x17f, 
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
