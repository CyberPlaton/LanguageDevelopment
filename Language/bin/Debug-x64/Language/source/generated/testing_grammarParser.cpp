
// Generated from source/testing_grammar.g4 by ANTLR 4.7


#include "testing_grammarListener.h"

#include "testing_grammarParser.h"


using namespace antlrcpp;
using namespace antlr4;

testing_grammarParser::testing_grammarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

testing_grammarParser::~testing_grammarParser() {
  delete _interpreter;
}

std::string testing_grammarParser::getGrammarFileName() const {
  return "testing_grammar.g4";
}

const std::vector<std::string>& testing_grammarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& testing_grammarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- EContext ------------------------------------------------------------------

testing_grammarParser::EContext::EContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

testing_grammarParser::TContext* testing_grammarParser::EContext::t() {
  return getRuleContext<testing_grammarParser::TContext>(0);
}

testing_grammarParser::EContext* testing_grammarParser::EContext::e() {
  return getRuleContext<testing_grammarParser::EContext>(0);
}


size_t testing_grammarParser::EContext::getRuleIndex() const {
  return testing_grammarParser::RuleE;
}

void testing_grammarParser::EContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<testing_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterE(this);
}

void testing_grammarParser::EContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<testing_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitE(this);
}


testing_grammarParser::EContext* testing_grammarParser::e() {
   return e(0);
}

testing_grammarParser::EContext* testing_grammarParser::e(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  testing_grammarParser::EContext *_localctx = _tracker.createInstance<EContext>(_ctx, parentState);
  testing_grammarParser::EContext *previousContext = _localctx;
  size_t startState = 0;
  enterRecursionRule(_localctx, 0, testing_grammarParser::RuleE, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(9);
    t(0);
    _ctx->stop = _input->LT(-1);
    setState(16);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<EContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleE);
        setState(11);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(12);
        match(testing_grammarParser::T__0);
        setState(13);
        t(0); 
      }
      setState(18);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TContext ------------------------------------------------------------------

testing_grammarParser::TContext::TContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

testing_grammarParser::MContext* testing_grammarParser::TContext::m() {
  return getRuleContext<testing_grammarParser::MContext>(0);
}

testing_grammarParser::TContext* testing_grammarParser::TContext::t() {
  return getRuleContext<testing_grammarParser::TContext>(0);
}


size_t testing_grammarParser::TContext::getRuleIndex() const {
  return testing_grammarParser::RuleT;
}

void testing_grammarParser::TContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<testing_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterT(this);
}

void testing_grammarParser::TContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<testing_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitT(this);
}


testing_grammarParser::TContext* testing_grammarParser::t() {
   return t(0);
}

testing_grammarParser::TContext* testing_grammarParser::t(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  testing_grammarParser::TContext *_localctx = _tracker.createInstance<TContext>(_ctx, parentState);
  testing_grammarParser::TContext *previousContext = _localctx;
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, testing_grammarParser::RuleT, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(20);
    m(0);
    _ctx->stop = _input->LT(-1);
    setState(27);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleT);
        setState(22);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(23);
        match(testing_grammarParser::T__1);
        setState(24);
        m(0); 
      }
      setState(29);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MContext ------------------------------------------------------------------

testing_grammarParser::MContext::MContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

testing_grammarParser::FContext* testing_grammarParser::MContext::f() {
  return getRuleContext<testing_grammarParser::FContext>(0);
}

testing_grammarParser::MContext* testing_grammarParser::MContext::m() {
  return getRuleContext<testing_grammarParser::MContext>(0);
}


size_t testing_grammarParser::MContext::getRuleIndex() const {
  return testing_grammarParser::RuleM;
}

void testing_grammarParser::MContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<testing_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterM(this);
}

void testing_grammarParser::MContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<testing_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitM(this);
}


testing_grammarParser::MContext* testing_grammarParser::m() {
   return m(0);
}

testing_grammarParser::MContext* testing_grammarParser::m(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  testing_grammarParser::MContext *_localctx = _tracker.createInstance<MContext>(_ctx, parentState);
  testing_grammarParser::MContext *previousContext = _localctx;
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, testing_grammarParser::RuleM, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(31);
    f();
    _ctx->stop = _input->LT(-1);
    setState(38);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleM);
        setState(33);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(34);
        match(testing_grammarParser::T__2);
        setState(35);
        f(); 
      }
      setState(40);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FContext ------------------------------------------------------------------

testing_grammarParser::FContext::FContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* testing_grammarParser::FContext::INT() {
  return getToken(testing_grammarParser::INT, 0);
}

testing_grammarParser::EContext* testing_grammarParser::FContext::e() {
  return getRuleContext<testing_grammarParser::EContext>(0);
}


size_t testing_grammarParser::FContext::getRuleIndex() const {
  return testing_grammarParser::RuleF;
}

void testing_grammarParser::FContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<testing_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterF(this);
}

void testing_grammarParser::FContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<testing_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitF(this);
}

testing_grammarParser::FContext* testing_grammarParser::f() {
  FContext *_localctx = _tracker.createInstance<FContext>(_ctx, getState());
  enterRule(_localctx, 6, testing_grammarParser::RuleF);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(47);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case testing_grammarParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(41);
        match(testing_grammarParser::INT);
        break;
      }

      case testing_grammarParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(42);
        match(testing_grammarParser::T__3);
        setState(43);
        e(0);
        setState(44);
        match(testing_grammarParser::T__4);
         std::cout<< e.text() << std::endl; 
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

bool testing_grammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 0: return eSempred(dynamic_cast<EContext *>(context), predicateIndex);
    case 1: return tSempred(dynamic_cast<TContext *>(context), predicateIndex);
    case 2: return mSempred(dynamic_cast<MContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool testing_grammarParser::eSempred(EContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool testing_grammarParser::tSempred(TContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool testing_grammarParser::mSempred(MContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> testing_grammarParser::_decisionToDFA;
atn::PredictionContextCache testing_grammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN testing_grammarParser::_atn;
std::vector<uint16_t> testing_grammarParser::_serializedATN;

std::vector<std::string> testing_grammarParser::_ruleNames = {
  "e", "t", "m", "f"
};

std::vector<std::string> testing_grammarParser::_literalNames = {
  "", "'+'", "'*'", "'%'", "'('", "')'"
};

std::vector<std::string> testing_grammarParser::_symbolicNames = {
  "", "", "", "", "", "", "INT"
};

dfa::Vocabulary testing_grammarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> testing_grammarParser::_tokenNames;

testing_grammarParser::Initializer::Initializer() {
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
    0x3, 0x8, 0x34, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x7, 0x2, 0x11, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x14, 0xb, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 
    0x3, 0x1c, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x1f, 0xb, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x27, 0xa, 0x4, 
    0xc, 0x4, 0xe, 0x4, 0x2a, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x32, 0xa, 0x5, 0x3, 0x5, 0x2, 0x5, 
    0x2, 0x4, 0x6, 0x6, 0x2, 0x4, 0x6, 0x8, 0x2, 0x2, 0x2, 0x33, 0x2, 0xa, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x15, 0x3, 0x2, 0x2, 0x2, 0x6, 0x20, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x31, 0x3, 0x2, 0x2, 0x2, 0xa, 0xb, 0x8, 0x2, 0x1, 0x2, 
    0xb, 0xc, 0x5, 0x4, 0x3, 0x2, 0xc, 0x12, 0x3, 0x2, 0x2, 0x2, 0xd, 0xe, 
    0xc, 0x4, 0x2, 0x2, 0xe, 0xf, 0x7, 0x3, 0x2, 0x2, 0xf, 0x11, 0x5, 0x4, 
    0x3, 0x2, 0x10, 0xd, 0x3, 0x2, 0x2, 0x2, 0x11, 0x14, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x10, 0x3, 0x2, 0x2, 0x2, 0x12, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0x13, 0x3, 0x3, 0x2, 0x2, 0x2, 0x14, 0x12, 0x3, 0x2, 0x2, 0x2, 0x15, 
    0x16, 0x8, 0x3, 0x1, 0x2, 0x16, 0x17, 0x5, 0x6, 0x4, 0x2, 0x17, 0x1d, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0xc, 0x4, 0x2, 0x2, 0x19, 0x1a, 0x7, 
    0x4, 0x2, 0x2, 0x1a, 0x1c, 0x5, 0x6, 0x4, 0x2, 0x1b, 0x18, 0x3, 0x2, 
    0x2, 0x2, 0x1c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x5, 0x3, 0x2, 0x2, 0x2, 
    0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x8, 0x4, 0x1, 0x2, 0x21, 
    0x22, 0x5, 0x8, 0x5, 0x2, 0x22, 0x28, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 
    0xc, 0x4, 0x2, 0x2, 0x24, 0x25, 0x7, 0x5, 0x2, 0x2, 0x25, 0x27, 0x5, 
    0x8, 0x5, 0x2, 0x26, 0x23, 0x3, 0x2, 0x2, 0x2, 0x27, 0x2a, 0x3, 0x2, 
    0x2, 0x2, 0x28, 0x26, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x3, 0x2, 0x2, 
    0x2, 0x29, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x28, 0x3, 0x2, 0x2, 0x2, 
    0x2b, 0x32, 0x7, 0x8, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0x6, 0x2, 0x2, 0x2d, 
    0x2e, 0x5, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0x7, 0x2, 0x2, 0x2f, 0x30, 
    0x8, 0x5, 0x1, 0x2, 0x30, 0x32, 0x3, 0x2, 0x2, 0x2, 0x31, 0x2b, 0x3, 
    0x2, 0x2, 0x2, 0x31, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x32, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x12, 0x1d, 0x28, 0x31, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

testing_grammarParser::Initializer testing_grammarParser::_init;
