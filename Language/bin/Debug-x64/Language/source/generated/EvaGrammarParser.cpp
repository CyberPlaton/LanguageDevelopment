
// Generated from source/EvaGrammar.g4 by ANTLR 4.7


#include "EvaGrammarListener.h"
#include "EvaGrammarVisitor.h"

#include "EvaGrammarParser.h"


using namespace antlrcpp;
using namespace antlr4;

EvaGrammarParser::EvaGrammarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

EvaGrammarParser::~EvaGrammarParser() {
  delete _interpreter;
}

std::string EvaGrammarParser::getGrammarFileName() const {
  return "EvaGrammar.g4";
}

const std::vector<std::string>& EvaGrammarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& EvaGrammarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

EvaGrammarParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EvaGrammarParser::ProgramContext::EOF() {
  return getToken(EvaGrammarParser::EOF, 0);
}

std::vector<tree::TerminalNode *> EvaGrammarParser::ProgramContext::NEWLINE() {
  return getTokens(EvaGrammarParser::NEWLINE);
}

tree::TerminalNode* EvaGrammarParser::ProgramContext::NEWLINE(size_t i) {
  return getToken(EvaGrammarParser::NEWLINE, i);
}

std::vector<EvaGrammarParser::ExprContext *> EvaGrammarParser::ProgramContext::expr() {
  return getRuleContexts<EvaGrammarParser::ExprContext>();
}

EvaGrammarParser::ExprContext* EvaGrammarParser::ProgramContext::expr(size_t i) {
  return getRuleContext<EvaGrammarParser::ExprContext>(i);
}


size_t EvaGrammarParser::ProgramContext::getRuleIndex() const {
  return EvaGrammarParser::RuleProgram;
}

void EvaGrammarParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void EvaGrammarParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any EvaGrammarParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EvaGrammarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

EvaGrammarParser::ProgramContext* EvaGrammarParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, EvaGrammarParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(14);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << EvaGrammarParser::T__0)
      | (1ULL << EvaGrammarParser::INT)
      | (1ULL << EvaGrammarParser::NEWLINE))) != 0)) {
      setState(12);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case EvaGrammarParser::NEWLINE: {
          setState(10);
          match(EvaGrammarParser::NEWLINE);
          break;
        }

        case EvaGrammarParser::T__0:
        case EvaGrammarParser::INT: {
          setState(11);
          expr(0);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(16);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(17);
    match(EvaGrammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Single_inputContext ------------------------------------------------------------------

EvaGrammarParser::Single_inputContext::Single_inputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EvaGrammarParser::Single_inputContext::NEWLINE() {
  return getToken(EvaGrammarParser::NEWLINE, 0);
}

EvaGrammarParser::ExprContext* EvaGrammarParser::Single_inputContext::expr() {
  return getRuleContext<EvaGrammarParser::ExprContext>(0);
}


size_t EvaGrammarParser::Single_inputContext::getRuleIndex() const {
  return EvaGrammarParser::RuleSingle_input;
}

void EvaGrammarParser::Single_inputContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingle_input(this);
}

void EvaGrammarParser::Single_inputContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingle_input(this);
}


antlrcpp::Any EvaGrammarParser::Single_inputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EvaGrammarVisitor*>(visitor))
    return parserVisitor->visitSingle_input(this);
  else
    return visitor->visitChildren(this);
}

EvaGrammarParser::Single_inputContext* EvaGrammarParser::single_input() {
  Single_inputContext *_localctx = _tracker.createInstance<Single_inputContext>(_ctx, getState());
  enterRule(_localctx, 2, EvaGrammarParser::RuleSingle_input);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(24);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(19);
      match(EvaGrammarParser::NEWLINE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(20);
      expr(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(21);
      expr(0);
      setState(22);
      match(EvaGrammarParser::NEWLINE);
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

//----------------- ExprContext ------------------------------------------------------------------

EvaGrammarParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EvaGrammarParser::TermContext* EvaGrammarParser::ExprContext::term() {
  return getRuleContext<EvaGrammarParser::TermContext>(0);
}

EvaGrammarParser::ExprContext* EvaGrammarParser::ExprContext::expr() {
  return getRuleContext<EvaGrammarParser::ExprContext>(0);
}

tree::TerminalNode* EvaGrammarParser::ExprContext::PLUS() {
  return getToken(EvaGrammarParser::PLUS, 0);
}

tree::TerminalNode* EvaGrammarParser::ExprContext::MINUS() {
  return getToken(EvaGrammarParser::MINUS, 0);
}


size_t EvaGrammarParser::ExprContext::getRuleIndex() const {
  return EvaGrammarParser::RuleExpr;
}

void EvaGrammarParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void EvaGrammarParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


antlrcpp::Any EvaGrammarParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EvaGrammarVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


EvaGrammarParser::ExprContext* EvaGrammarParser::expr() {
   return expr(0);
}

EvaGrammarParser::ExprContext* EvaGrammarParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  EvaGrammarParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  EvaGrammarParser::ExprContext *previousContext = _localctx;
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, EvaGrammarParser::RuleExpr, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(27);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(34);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpr);
        setState(29);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(30);
        _la = _input->LA(1);
        if (!(_la == EvaGrammarParser::PLUS

        || _la == EvaGrammarParser::MINUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(31);
        term(0); 
      }
      setState(36);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

EvaGrammarParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EvaGrammarParser::LiteralContext* EvaGrammarParser::TermContext::literal() {
  return getRuleContext<EvaGrammarParser::LiteralContext>(0);
}

EvaGrammarParser::TermContext* EvaGrammarParser::TermContext::term() {
  return getRuleContext<EvaGrammarParser::TermContext>(0);
}

tree::TerminalNode* EvaGrammarParser::TermContext::MUL() {
  return getToken(EvaGrammarParser::MUL, 0);
}

tree::TerminalNode* EvaGrammarParser::TermContext::DIVIDE() {
  return getToken(EvaGrammarParser::DIVIDE, 0);
}


size_t EvaGrammarParser::TermContext::getRuleIndex() const {
  return EvaGrammarParser::RuleTerm;
}

void EvaGrammarParser::TermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerm(this);
}

void EvaGrammarParser::TermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerm(this);
}


antlrcpp::Any EvaGrammarParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EvaGrammarVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}


EvaGrammarParser::TermContext* EvaGrammarParser::term() {
   return term(0);
}

EvaGrammarParser::TermContext* EvaGrammarParser::term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  EvaGrammarParser::TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, parentState);
  EvaGrammarParser::TermContext *previousContext = _localctx;
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, EvaGrammarParser::RuleTerm, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(38);
    literal();
    _ctx->stop = _input->LT(-1);
    setState(45);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleTerm);
        setState(40);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(41);
        _la = _input->LA(1);
        if (!(_la == EvaGrammarParser::MUL

        || _la == EvaGrammarParser::DIVIDE)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(42);
        literal(); 
      }
      setState(47);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

EvaGrammarParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EvaGrammarParser::LiteralContext::INT() {
  return getToken(EvaGrammarParser::INT, 0);
}

EvaGrammarParser::ExprContext* EvaGrammarParser::LiteralContext::expr() {
  return getRuleContext<EvaGrammarParser::ExprContext>(0);
}


size_t EvaGrammarParser::LiteralContext::getRuleIndex() const {
  return EvaGrammarParser::RuleLiteral;
}

void EvaGrammarParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void EvaGrammarParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


antlrcpp::Any EvaGrammarParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EvaGrammarVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

EvaGrammarParser::LiteralContext* EvaGrammarParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 8, EvaGrammarParser::RuleLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(53);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case EvaGrammarParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(48);
        match(EvaGrammarParser::INT);
        break;
      }

      case EvaGrammarParser::T__0: {
        enterOuterAlt(_localctx, 2);
        setState(49);
        match(EvaGrammarParser::T__0);
        setState(50);
        expr(0);
        setState(51);
        match(EvaGrammarParser::T__1);
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

bool EvaGrammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);
    case 3: return termSempred(dynamic_cast<TermContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool EvaGrammarParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool EvaGrammarParser::termSempred(TermContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> EvaGrammarParser::_decisionToDFA;
atn::PredictionContextCache EvaGrammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN EvaGrammarParser::_atn;
std::vector<uint16_t> EvaGrammarParser::_serializedATN;

std::vector<std::string> EvaGrammarParser::_ruleNames = {
  "program", "single_input", "expr", "term", "literal"
};

std::vector<std::string> EvaGrammarParser::_literalNames = {
  "", "'('", "')'", "", "", "", "'*'", "'+'", "'-'", "'/'"
};

std::vector<std::string> EvaGrammarParser::_symbolicNames = {
  "", "", "", "INT", "NEWLINE", "WS", "MUL", "PLUS", "MINUS", "DIVIDE"
};

dfa::Vocabulary EvaGrammarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> EvaGrammarParser::_tokenNames;

EvaGrammarParser::Initializer::Initializer() {
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
    0x3, 0xb, 0x3a, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x3, 0x2, 0x3, 0x2, 0x7, 
    0x2, 0xf, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x12, 0xb, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x1b, 
    0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x7, 0x4, 0x23, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x26, 0xb, 0x4, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x2e, 0xa, 
    0x5, 0xc, 0x5, 0xe, 0x5, 0x31, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x38, 0xa, 0x6, 0x3, 0x6, 0x2, 0x4, 0x6, 
    0x8, 0x7, 0x2, 0x4, 0x6, 0x8, 0xa, 0x2, 0x4, 0x3, 0x2, 0x9, 0xa, 0x4, 
    0x2, 0x8, 0x8, 0xb, 0xb, 0x2, 0x3b, 0x2, 0x10, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x1a, 0x3, 0x2, 0x2, 0x2, 0x6, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x8, 0x27, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x37, 0x3, 0x2, 0x2, 0x2, 0xc, 0xf, 0x7, 0x6, 
    0x2, 0x2, 0xd, 0xf, 0x5, 0x6, 0x4, 0x2, 0xe, 0xc, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0xd, 0x3, 0x2, 0x2, 0x2, 0xf, 0x12, 0x3, 0x2, 0x2, 0x2, 0x10, 0xe, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x11, 0x3, 0x2, 0x2, 0x2, 0x11, 0x13, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x10, 0x3, 0x2, 0x2, 0x2, 0x13, 0x14, 0x7, 0x2, 
    0x2, 0x3, 0x14, 0x3, 0x3, 0x2, 0x2, 0x2, 0x15, 0x1b, 0x7, 0x6, 0x2, 
    0x2, 0x16, 0x1b, 0x5, 0x6, 0x4, 0x2, 0x17, 0x18, 0x5, 0x6, 0x4, 0x2, 
    0x18, 0x19, 0x7, 0x6, 0x2, 0x2, 0x19, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x16, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0x1b, 0x5, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x8, 
    0x4, 0x1, 0x2, 0x1d, 0x1e, 0x5, 0x8, 0x5, 0x2, 0x1e, 0x24, 0x3, 0x2, 
    0x2, 0x2, 0x1f, 0x20, 0xc, 0x4, 0x2, 0x2, 0x20, 0x21, 0x9, 0x2, 0x2, 
    0x2, 0x21, 0x23, 0x5, 0x8, 0x5, 0x2, 0x22, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0x23, 0x26, 0x3, 0x2, 0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x7, 0x3, 0x2, 0x2, 0x2, 0x26, 0x24, 
    0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x8, 0x5, 0x1, 0x2, 0x28, 0x29, 0x5, 
    0xa, 0x6, 0x2, 0x29, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0xc, 0x4, 
    0x2, 0x2, 0x2b, 0x2c, 0x9, 0x3, 0x2, 0x2, 0x2c, 0x2e, 0x5, 0xa, 0x6, 
    0x2, 0x2d, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0x2f, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x3, 0x2, 0x2, 0x2, 0x30, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x32, 0x38, 
    0x7, 0x5, 0x2, 0x2, 0x33, 0x34, 0x7, 0x3, 0x2, 0x2, 0x34, 0x35, 0x5, 
    0x6, 0x4, 0x2, 0x35, 0x36, 0x7, 0x4, 0x2, 0x2, 0x36, 0x38, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0x32, 0x3, 0x2, 0x2, 0x2, 0x37, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0xb, 0x3, 0x2, 0x2, 0x2, 0x8, 0xe, 0x10, 0x1a, 0x24, 0x2f, 
    0x37, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

EvaGrammarParser::Initializer EvaGrammarParser::_init;
