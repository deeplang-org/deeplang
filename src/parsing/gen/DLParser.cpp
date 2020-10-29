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
  enterRule(_localctx, 0, DLParser::RuleAryOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
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

//----------------- ExpressionListContext ------------------------------------------------------------------

DLParser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DLParser::ExpressionStatementContext *> DLParser::ExpressionListContext::expressionStatement() {
  return getRuleContexts<DLParser::ExpressionStatementContext>();
}

DLParser::ExpressionStatementContext* DLParser::ExpressionListContext::expressionStatement(size_t i) {
  return getRuleContext<DLParser::ExpressionStatementContext>(i);
}

std::vector<tree::TerminalNode *> DLParser::ExpressionListContext::COMMA_SYMBOL() {
  return getTokens(DLParser::COMMA_SYMBOL);
}

tree::TerminalNode* DLParser::ExpressionListContext::COMMA_SYMBOL(size_t i) {
  return getToken(DLParser::COMMA_SYMBOL, i);
}


size_t DLParser::ExpressionListContext::getRuleIndex() const {
  return DLParser::RuleExpressionList;
}

void DLParser::ExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionList(this);
}

void DLParser::ExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionList(this);
}


antlrcpp::Any DLParser::ExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitExpressionList(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ExpressionListContext* DLParser::expressionList() {
  ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 2, DLParser::RuleExpressionList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 408) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 408)) & ((1ULL << (DLParser::OPEN_CURLY_SYMBOL - 408))
      | (1ULL << (DLParser::CONST - 408))
      | (1ULL << (DLParser::IDENTIFIER - 408))
      | (1ULL << (DLParser::QUOTED_STRING - 408)))) != 0)) {
      setState(32);
      expressionStatement();
      setState(37);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == DLParser::COMMA_SYMBOL) {
        setState(33);
        match(DLParser::COMMA_SYMBOL);
        setState(34);
        expressionStatement();
        setState(39);
        _errHandler->sync(this);
        _la = _input->LA(1);
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

//----------------- ExpressionStatementContext ------------------------------------------------------------------

DLParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::BlockExpressionContext* DLParser::ExpressionStatementContext::blockExpression() {
  return getRuleContext<DLParser::BlockExpressionContext>(0);
}

DLParser::UnblockExpressionContext* DLParser::ExpressionStatementContext::unblockExpression() {
  return getRuleContext<DLParser::UnblockExpressionContext>(0);
}


size_t DLParser::ExpressionStatementContext::getRuleIndex() const {
  return DLParser::RuleExpressionStatement;
}

void DLParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void DLParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}


antlrcpp::Any DLParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ExpressionStatementContext* DLParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 4, DLParser::RuleExpressionStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(44);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::OPEN_CURLY_SYMBOL: {
        enterOuterAlt(_localctx, 1);
        setState(42);
        blockExpression();
        break;
      }

      case DLParser::CONST:
      case DLParser::IDENTIFIER:
      case DLParser::QUOTED_STRING: {
        enterOuterAlt(_localctx, 2);
        setState(43);
        unblockExpression(0);
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

//----------------- BlockExpressionContext ------------------------------------------------------------------

DLParser::BlockExpressionContext::BlockExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::BlockExpressionContext::OPEN_CURLY_SYMBOL() {
  return getToken(DLParser::OPEN_CURLY_SYMBOL, 0);
}

DLParser::StatementsContext* DLParser::BlockExpressionContext::statements() {
  return getRuleContext<DLParser::StatementsContext>(0);
}

tree::TerminalNode* DLParser::BlockExpressionContext::CLOSE_CURLY_SYMBOL() {
  return getToken(DLParser::CLOSE_CURLY_SYMBOL, 0);
}


size_t DLParser::BlockExpressionContext::getRuleIndex() const {
  return DLParser::RuleBlockExpression;
}

void DLParser::BlockExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockExpression(this);
}

void DLParser::BlockExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockExpression(this);
}


antlrcpp::Any DLParser::BlockExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitBlockExpression(this);
  else
    return visitor->visitChildren(this);
}

DLParser::BlockExpressionContext* DLParser::blockExpression() {
  BlockExpressionContext *_localctx = _tracker.createInstance<BlockExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, DLParser::RuleBlockExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(52);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(46);
      match(DLParser::OPEN_CURLY_SYMBOL);
      setState(47);
      statements();
      setState(48);
      match(DLParser::CLOSE_CURLY_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(50);
      match(DLParser::OPEN_CURLY_SYMBOL);
      setState(51);
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

//----------------- UnblockExpressionContext ------------------------------------------------------------------

DLParser::UnblockExpressionContext::UnblockExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::UnblockExpressionContext::QUOTED_STRING() {
  return getToken(DLParser::QUOTED_STRING, 0);
}

tree::TerminalNode* DLParser::UnblockExpressionContext::CONST() {
  return getToken(DLParser::CONST, 0);
}

tree::TerminalNode* DLParser::UnblockExpressionContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

std::vector<DLParser::UnblockExpressionContext *> DLParser::UnblockExpressionContext::unblockExpression() {
  return getRuleContexts<DLParser::UnblockExpressionContext>();
}

DLParser::UnblockExpressionContext* DLParser::UnblockExpressionContext::unblockExpression(size_t i) {
  return getRuleContext<DLParser::UnblockExpressionContext>(i);
}

tree::TerminalNode* DLParser::UnblockExpressionContext::MULT_OPERATOR() {
  return getToken(DLParser::MULT_OPERATOR, 0);
}

tree::TerminalNode* DLParser::UnblockExpressionContext::DIV_OPERATOR() {
  return getToken(DLParser::DIV_OPERATOR, 0);
}

tree::TerminalNode* DLParser::UnblockExpressionContext::PLUS_OPERATOR() {
  return getToken(DLParser::PLUS_OPERATOR, 0);
}

tree::TerminalNode* DLParser::UnblockExpressionContext::MINUS_OPERATOR() {
  return getToken(DLParser::MINUS_OPERATOR, 0);
}

tree::TerminalNode* DLParser::UnblockExpressionContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

DLParser::ExpressionListContext* DLParser::UnblockExpressionContext::expressionList() {
  return getRuleContext<DLParser::ExpressionListContext>(0);
}

tree::TerminalNode* DLParser::UnblockExpressionContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}


size_t DLParser::UnblockExpressionContext::getRuleIndex() const {
  return DLParser::RuleUnblockExpression;
}

void DLParser::UnblockExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnblockExpression(this);
}

void DLParser::UnblockExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnblockExpression(this);
}


antlrcpp::Any DLParser::UnblockExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitUnblockExpression(this);
  else
    return visitor->visitChildren(this);
}


DLParser::UnblockExpressionContext* DLParser::unblockExpression() {
   return unblockExpression(0);
}

DLParser::UnblockExpressionContext* DLParser::unblockExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  DLParser::UnblockExpressionContext *_localctx = _tracker.createInstance<UnblockExpressionContext>(_ctx, parentState);
  DLParser::UnblockExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, DLParser::RuleUnblockExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(58);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::QUOTED_STRING: {
        setState(55);
        match(DLParser::QUOTED_STRING);
        break;
      }

      case DLParser::CONST: {
        setState(56);
        match(DLParser::CONST);
        break;
      }

      case DLParser::IDENTIFIER: {
        setState(57);
        match(DLParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(73);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(71);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<UnblockExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleUnblockExpression);
          setState(60);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(61);
          dynamic_cast<UnblockExpressionContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == DLParser::MULT_OPERATOR

          || _la == DLParser::DIV_OPERATOR)) {
            dynamic_cast<UnblockExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(62);
          unblockExpression(7);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<UnblockExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleUnblockExpression);
          setState(63);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(64);
          dynamic_cast<UnblockExpressionContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == DLParser::PLUS_OPERATOR

          || _la == DLParser::MINUS_OPERATOR)) {
            dynamic_cast<UnblockExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(65);
          unblockExpression(6);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<UnblockExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleUnblockExpression);
          setState(66);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(67);
          match(DLParser::OPEN_PAR_SYMBOL);
          setState(68);
          expressionList();
          setState(69);
          match(DLParser::CLOSE_PAR_SYMBOL);
          break;
        }

        } 
      }
      setState(75);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TupleTypeContext ------------------------------------------------------------------

DLParser::TupleTypeContext::TupleTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::TupleTypeContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

tree::TerminalNode* DLParser::TupleTypeContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}


size_t DLParser::TupleTypeContext::getRuleIndex() const {
  return DLParser::RuleTupleType;
}

void DLParser::TupleTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTupleType(this);
}

void DLParser::TupleTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTupleType(this);
}


antlrcpp::Any DLParser::TupleTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitTupleType(this);
  else
    return visitor->visitChildren(this);
}

DLParser::TupleTypeContext* DLParser::tupleType() {
  TupleTypeContext *_localctx = _tracker.createInstance<TupleTypeContext>(_ctx, getState());
  enterRule(_localctx, 10, DLParser::RuleTupleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    match(DLParser::OPEN_PAR_SYMBOL);
    setState(77);
    match(DLParser::CLOSE_PAR_SYMBOL);
   
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

DLParser::TupleTypeContext* DLParser::TypeContext::tupleType() {
  return getRuleContext<DLParser::TupleTypeContext>(0);
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
  enterRule(_localctx, 12, DLParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(81);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::OPEN_PAR_SYMBOL: {
        enterOuterAlt(_localctx, 1);
        setState(79);
        tupleType();
        break;
      }

      case DLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(80);
        match(DLParser::IDENTIFIER);
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

//----------------- VariableDeclContext ------------------------------------------------------------------

DLParser::VariableDeclContext::VariableDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::VariableDeclContext::LET_SYMBOL() {
  return getToken(DLParser::LET_SYMBOL, 0);
}

tree::TerminalNode* DLParser::VariableDeclContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::VariableDeclContext::COLON_SYMBOL() {
  return getToken(DLParser::COLON_SYMBOL, 0);
}

DLParser::TypeContext* DLParser::VariableDeclContext::type() {
  return getRuleContext<DLParser::TypeContext>(0);
}

tree::TerminalNode* DLParser::VariableDeclContext::EQUAL_OPERATOR() {
  return getToken(DLParser::EQUAL_OPERATOR, 0);
}

DLParser::ExpressionStatementContext* DLParser::VariableDeclContext::expressionStatement() {
  return getRuleContext<DLParser::ExpressionStatementContext>(0);
}


size_t DLParser::VariableDeclContext::getRuleIndex() const {
  return DLParser::RuleVariableDecl;
}

void DLParser::VariableDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDecl(this);
}

void DLParser::VariableDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDecl(this);
}


antlrcpp::Any DLParser::VariableDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitVariableDecl(this);
  else
    return visitor->visitChildren(this);
}

DLParser::VariableDeclContext* DLParser::variableDecl() {
  VariableDeclContext *_localctx = _tracker.createInstance<VariableDeclContext>(_ctx, getState());
  enterRule(_localctx, 14, DLParser::RuleVariableDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(94);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(83);
      match(DLParser::LET_SYMBOL);
      setState(84);
      match(DLParser::IDENTIFIER);
      setState(85);
      match(DLParser::COLON_SYMBOL);
      setState(86);
      type();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(87);
      match(DLParser::LET_SYMBOL);
      setState(88);
      match(DLParser::IDENTIFIER);
      setState(89);
      match(DLParser::COLON_SYMBOL);
      setState(90);
      type();
      setState(91);
      match(DLParser::EQUAL_OPERATOR);
      setState(92);
      expressionStatement();
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

//----------------- ParamContext ------------------------------------------------------------------

DLParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::ParamContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::ParamContext::COLON_SYMBOL() {
  return getToken(DLParser::COLON_SYMBOL, 0);
}

DLParser::TypeContext* DLParser::ParamContext::type() {
  return getRuleContext<DLParser::TypeContext>(0);
}


size_t DLParser::ParamContext::getRuleIndex() const {
  return DLParser::RuleParam;
}

void DLParser::ParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam(this);
}

void DLParser::ParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam(this);
}


antlrcpp::Any DLParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ParamContext* DLParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 16, DLParser::RuleParam);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(DLParser::IDENTIFIER);
    setState(97);
    match(DLParser::COLON_SYMBOL);
    setState(98);
    type();
   
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

std::vector<DLParser::ParamContext *> DLParser::ParamListContext::param() {
  return getRuleContexts<DLParser::ParamContext>();
}

DLParser::ParamContext* DLParser::ParamListContext::param(size_t i) {
  return getRuleContext<DLParser::ParamContext>(i);
}

std::vector<tree::TerminalNode *> DLParser::ParamListContext::COMMA_SYMBOL() {
  return getTokens(DLParser::COMMA_SYMBOL);
}

tree::TerminalNode* DLParser::ParamListContext::COMMA_SYMBOL(size_t i) {
  return getToken(DLParser::COMMA_SYMBOL, i);
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
  enterRule(_localctx, 18, DLParser::RuleParamList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DLParser::IDENTIFIER) {
      setState(100);
      param();
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == DLParser::COMMA_SYMBOL) {
        setState(101);
        match(DLParser::COMMA_SYMBOL);
        setState(102);
        param();
        setState(107);
        _errHandler->sync(this);
        _la = _input->LA(1);
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

//----------------- FunctionDeclContext ------------------------------------------------------------------

DLParser::FunctionDeclContext::FunctionDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* DLParser::FunctionDeclContext::FUN_SYMBOL() {
  return getToken(DLParser::FUN_SYMBOL, 0);
}

tree::TerminalNode* DLParser::FunctionDeclContext::IDENTIFIER() {
  return getToken(DLParser::IDENTIFIER, 0);
}

tree::TerminalNode* DLParser::FunctionDeclContext::OPEN_PAR_SYMBOL() {
  return getToken(DLParser::OPEN_PAR_SYMBOL, 0);
}

DLParser::ParamListContext* DLParser::FunctionDeclContext::paramList() {
  return getRuleContext<DLParser::ParamListContext>(0);
}

tree::TerminalNode* DLParser::FunctionDeclContext::CLOSE_PAR_SYMBOL() {
  return getToken(DLParser::CLOSE_PAR_SYMBOL, 0);
}

tree::TerminalNode* DLParser::FunctionDeclContext::JSON_SEPARATOR_SYMBOL() {
  return getToken(DLParser::JSON_SEPARATOR_SYMBOL, 0);
}

DLParser::TypeContext* DLParser::FunctionDeclContext::type() {
  return getRuleContext<DLParser::TypeContext>(0);
}

DLParser::BlockExpressionContext* DLParser::FunctionDeclContext::blockExpression() {
  return getRuleContext<DLParser::BlockExpressionContext>(0);
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
  enterRule(_localctx, 20, DLParser::RuleFunctionDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(DLParser::FUN_SYMBOL);
    setState(111);
    match(DLParser::IDENTIFIER);
    setState(112);
    match(DLParser::OPEN_PAR_SYMBOL);
    setState(113);
    paramList();
    setState(114);
    match(DLParser::CLOSE_PAR_SYMBOL);
    setState(115);
    match(DLParser::JSON_SEPARATOR_SYMBOL);
    setState(116);
    type();
    setState(117);
    blockExpression();
   
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

DLParser::VariableDeclContext* DLParser::DeclContext::variableDecl() {
  return getRuleContext<DLParser::VariableDeclContext>(0);
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
  enterRule(_localctx, 22, DLParser::RuleDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::FUN_SYMBOL: {
        enterOuterAlt(_localctx, 1);
        setState(119);
        functionDecl();
        break;
      }

      case DLParser::LET_SYMBOL: {
        enterOuterAlt(_localctx, 2);
        setState(120);
        variableDecl();
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

//----------------- StatementContext ------------------------------------------------------------------

DLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::DeclContext* DLParser::StatementContext::decl() {
  return getRuleContext<DLParser::DeclContext>(0);
}

DLParser::ExpressionStatementContext* DLParser::StatementContext::expressionStatement() {
  return getRuleContext<DLParser::ExpressionStatementContext>(0);
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
  enterRule(_localctx, 24, DLParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(125);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DLParser::LET_SYMBOL:
      case DLParser::FUN_SYMBOL: {
        enterOuterAlt(_localctx, 1);
        setState(123);
        decl();
        break;
      }

      case DLParser::OPEN_CURLY_SYMBOL:
      case DLParser::CONST:
      case DLParser::IDENTIFIER:
      case DLParser::QUOTED_STRING: {
        enterOuterAlt(_localctx, 2);
        setState(124);
        expressionStatement();
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

//----------------- StatementsContext ------------------------------------------------------------------

DLParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::StatementContext* DLParser::StatementsContext::statement() {
  return getRuleContext<DLParser::StatementContext>(0);
}

tree::TerminalNode* DLParser::StatementsContext::SEMICOLON_SYMBOL() {
  return getToken(DLParser::SEMICOLON_SYMBOL, 0);
}

DLParser::StatementsContext* DLParser::StatementsContext::statements() {
  return getRuleContext<DLParser::StatementsContext>(0);
}


size_t DLParser::StatementsContext::getRuleIndex() const {
  return DLParser::RuleStatements;
}

void DLParser::StatementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatements(this);
}

void DLParser::StatementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatements(this);
}


antlrcpp::Any DLParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

DLParser::StatementsContext* DLParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 26, DLParser::RuleStatements);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(134);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(127);
      statement();
      setState(128);
      match(DLParser::SEMICOLON_SYMBOL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(130);
      statement();
      setState(131);
      match(DLParser::SEMICOLON_SYMBOL);
      setState(132);
      statements();
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

//----------------- ModuleContext ------------------------------------------------------------------

DLParser::ModuleContext::ModuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DLParser::StatementsContext* DLParser::ModuleContext::statements() {
  return getRuleContext<DLParser::StatementsContext>(0);
}

tree::TerminalNode* DLParser::ModuleContext::EOF() {
  return getToken(DLParser::EOF, 0);
}


size_t DLParser::ModuleContext::getRuleIndex() const {
  return DLParser::RuleModule;
}

void DLParser::ModuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModule(this);
}

void DLParser::ModuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DLParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModule(this);
}


antlrcpp::Any DLParser::ModuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<DLParserVisitor*>(visitor))
    return parserVisitor->visitModule(this);
  else
    return visitor->visitChildren(this);
}

DLParser::ModuleContext* DLParser::module() {
  ModuleContext *_localctx = _tracker.createInstance<ModuleContext>(_ctx, getState());
  enterRule(_localctx, 28, DLParser::RuleModule);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(136);
    statements();
    setState(137);
    match(DLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool DLParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 4: return unblockExpressionSempred(dynamic_cast<UnblockExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool DLParser::unblockExpressionSempred(UnblockExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 6);
    case 1: return precpred(_ctx, 5);
    case 2: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> DLParser::_decisionToDFA;
atn::PredictionContextCache DLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN DLParser::_atn;
std::vector<uint16_t> DLParser::_serializedATN;

std::vector<std::string> DLParser::_ruleNames = {
  "aryOp", "expressionList", "expressionStatement", "blockExpression", "unblockExpression", 
  "tupleType", "type", "variableDecl", "param", "paramList", "functionDecl", 
  "decl", "statement", "statements", "module"
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
    0x3, 0x1c5, 0x8e, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x26, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x29, 
    0xb, 0x3, 0x5, 0x3, 0x2b, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x2f, 
    0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x5, 0x5, 0x37, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 
    0x6, 0x3d, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 
    0x4a, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x4d, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x54, 0xa, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x61, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x6a, 0xa, 
    0xb, 0xc, 0xb, 0xe, 0xb, 0x6d, 0xb, 0xb, 0x5, 0xb, 0x6f, 0xa, 0xb, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x7c, 0xa, 0xd, 0x3, 0xe, 
    0x3, 0xe, 0x5, 0xe, 0x80, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x89, 0xa, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x2, 0x3, 0xa, 0x11, 0x2, 0x4, 0x6, 
    0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 
    0x2, 0x5, 0x6, 0x2, 0x181, 0x182, 0x188, 0x18c, 0x190, 0x190, 0x192, 
    0x192, 0x3, 0x2, 0x18a, 0x18b, 0x3, 0x2, 0x188, 0x189, 0x2, 0x8e, 0x2, 
    0x20, 0x3, 0x2, 0x2, 0x2, 0x4, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2e, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x36, 0x3, 0x2, 0x2, 0x2, 0xa, 0x3c, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x4e, 0x3, 0x2, 0x2, 0x2, 0xe, 0x53, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0x60, 0x3, 0x2, 0x2, 0x2, 0x12, 0x62, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0x6e, 0x3, 0x2, 0x2, 0x2, 0x16, 0x70, 0x3, 0x2, 0x2, 0x2, 0x18, 0x7b, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x88, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x9, 0x2, 
    0x2, 0x2, 0x21, 0x3, 0x3, 0x2, 0x2, 0x2, 0x22, 0x27, 0x5, 0x6, 0x4, 
    0x2, 0x23, 0x24, 0x7, 0x195, 0x2, 0x2, 0x24, 0x26, 0x5, 0x6, 0x4, 0x2, 
    0x25, 0x23, 0x3, 0x2, 0x2, 0x2, 0x26, 0x29, 0x3, 0x2, 0x2, 0x2, 0x27, 
    0x25, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2b, 
    0x3, 0x2, 0x2, 0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x22, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x2c, 0x2f, 0x5, 0x8, 0x5, 0x2, 0x2d, 0x2f, 0x5, 0xa, 0x6, 
    0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2d, 0x3, 0x2, 0x2, 0x2, 
    0x2f, 0x7, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x7, 0x19a, 0x2, 0x2, 0x31, 
    0x32, 0x5, 0x1c, 0xf, 0x2, 0x32, 0x33, 0x7, 0x19b, 0x2, 0x2, 0x33, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x7, 0x19a, 0x2, 0x2, 0x35, 0x37, 0x7, 
    0x19b, 0x2, 0x2, 0x36, 0x30, 0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0x9, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x8, 0x6, 0x1, 
    0x2, 0x39, 0x3d, 0x7, 0x1c2, 0x2, 0x2, 0x3a, 0x3d, 0x7, 0x1a4, 0x2, 
    0x2, 0x3b, 0x3d, 0x7, 0x1c1, 0x2, 0x2, 0x3c, 0x38, 0x3, 0x2, 0x2, 0x2, 
    0x3c, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 
    0x4b, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0xc, 0x8, 0x2, 0x2, 0x3f, 0x40, 
    0x9, 0x3, 0x2, 0x2, 0x40, 0x4a, 0x5, 0xa, 0x6, 0x9, 0x41, 0x42, 0xc, 
    0x7, 0x2, 0x2, 0x42, 0x43, 0x9, 0x4, 0x2, 0x2, 0x43, 0x4a, 0x5, 0xa, 
    0x6, 0x8, 0x44, 0x45, 0xc, 0x5, 0x2, 0x2, 0x45, 0x46, 0x7, 0x198, 0x2, 
    0x2, 0x46, 0x47, 0x5, 0x4, 0x3, 0x2, 0x47, 0x48, 0x7, 0x199, 0x2, 0x2, 
    0x48, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x49, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x49, 
    0x41, 0x3, 0x2, 0x2, 0x2, 0x49, 0x44, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0xb, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4b, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x4f, 0x7, 0x198, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x199, 
    0x2, 0x2, 0x50, 0xd, 0x3, 0x2, 0x2, 0x2, 0x51, 0x54, 0x5, 0xc, 0x7, 
    0x2, 0x52, 0x54, 0x7, 0x1c1, 0x2, 0x2, 0x53, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x53, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 0xf, 0x3, 0x2, 0x2, 0x2, 0x55, 
    0x56, 0x7, 0x1a9, 0x2, 0x2, 0x56, 0x57, 0x7, 0x1c1, 0x2, 0x2, 0x57, 
    0x58, 0x7, 0x197, 0x2, 0x2, 0x58, 0x61, 0x5, 0xe, 0x8, 0x2, 0x59, 0x5a, 
    0x7, 0x1a9, 0x2, 0x2, 0x5a, 0x5b, 0x7, 0x1c1, 0x2, 0x2, 0x5b, 0x5c, 
    0x7, 0x197, 0x2, 0x2, 0x5c, 0x5d, 0x5, 0xe, 0x8, 0x2, 0x5d, 0x5e, 0x7, 
    0x182, 0x2, 0x2, 0x5e, 0x5f, 0x5, 0x6, 0x4, 0x2, 0x5f, 0x61, 0x3, 0x2, 
    0x2, 0x2, 0x60, 0x55, 0x3, 0x2, 0x2, 0x2, 0x60, 0x59, 0x3, 0x2, 0x2, 
    0x2, 0x61, 0x11, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x7, 0x1c1, 0x2, 0x2, 
    0x63, 0x64, 0x7, 0x197, 0x2, 0x2, 0x64, 0x65, 0x5, 0xe, 0x8, 0x2, 0x65, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x66, 0x6b, 0x5, 0x12, 0xa, 0x2, 0x67, 0x68, 
    0x7, 0x195, 0x2, 0x2, 0x68, 0x6a, 0x5, 0x12, 0xa, 0x2, 0x69, 0x67, 0x3, 
    0x2, 0x2, 0x2, 0x6a, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 
    0x2, 0x2, 0x6b, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6f, 0x3, 0x2, 0x2, 
    0x2, 0x6d, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x66, 0x3, 0x2, 0x2, 0x2, 
    0x6e, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x15, 0x3, 0x2, 0x2, 0x2, 0x70, 
    0x71, 0x7, 0x1aa, 0x2, 0x2, 0x71, 0x72, 0x7, 0x1c1, 0x2, 0x2, 0x72, 
    0x73, 0x7, 0x198, 0x2, 0x2, 0x73, 0x74, 0x5, 0x14, 0xb, 0x2, 0x74, 0x75, 
    0x7, 0x199, 0x2, 0x2, 0x75, 0x76, 0x7, 0x19f, 0x2, 0x2, 0x76, 0x77, 
    0x5, 0xe, 0x8, 0x2, 0x77, 0x78, 0x5, 0x8, 0x5, 0x2, 0x78, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0x79, 0x7c, 0x5, 0x16, 0xc, 0x2, 0x7a, 0x7c, 0x5, 0x10, 
    0x9, 0x2, 0x7b, 0x79, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7a, 0x3, 0x2, 0x2, 
    0x2, 0x7c, 0x19, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x80, 0x5, 0x18, 0xd, 0x2, 
    0x7e, 0x80, 0x5, 0x6, 0x4, 0x2, 0x7f, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7f, 
    0x7e, 0x3, 0x2, 0x2, 0x2, 0x80, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 
    0x5, 0x1a, 0xe, 0x2, 0x82, 0x83, 0x7, 0x196, 0x2, 0x2, 0x83, 0x89, 0x3, 
    0x2, 0x2, 0x2, 0x84, 0x85, 0x5, 0x1a, 0xe, 0x2, 0x85, 0x86, 0x7, 0x196, 
    0x2, 0x2, 0x86, 0x87, 0x5, 0x1c, 0xf, 0x2, 0x87, 0x89, 0x3, 0x2, 0x2, 
    0x2, 0x88, 0x81, 0x3, 0x2, 0x2, 0x2, 0x88, 0x84, 0x3, 0x2, 0x2, 0x2, 
    0x89, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x5, 0x1c, 0xf, 0x2, 0x8b, 
    0x8c, 0x7, 0x2, 0x2, 0x3, 0x8c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x10, 0x27, 
    0x2a, 0x2e, 0x36, 0x3c, 0x49, 0x4b, 0x53, 0x60, 0x6b, 0x6e, 0x7b, 0x7f, 
    0x88, 
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
