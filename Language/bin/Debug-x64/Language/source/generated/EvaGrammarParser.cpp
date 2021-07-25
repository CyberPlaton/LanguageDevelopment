
// Generated from source/EvaGrammar.g4 by ANTLR 4.7


#include "EvaGrammarListener.h"

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


//----------------- File_inputContext ------------------------------------------------------------------

EvaGrammarParser::File_inputContext::File_inputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EvaGrammarParser::File_inputContext::EOF() {
  return getToken(EvaGrammarParser::EOF, 0);
}

std::vector<tree::TerminalNode *> EvaGrammarParser::File_inputContext::NEWLINE() {
  return getTokens(EvaGrammarParser::NEWLINE);
}

tree::TerminalNode* EvaGrammarParser::File_inputContext::NEWLINE(size_t i) {
  return getToken(EvaGrammarParser::NEWLINE, i);
}

std::vector<EvaGrammarParser::EContext *> EvaGrammarParser::File_inputContext::e() {
  return getRuleContexts<EvaGrammarParser::EContext>();
}

EvaGrammarParser::EContext* EvaGrammarParser::File_inputContext::e(size_t i) {
  return getRuleContext<EvaGrammarParser::EContext>(i);
}


size_t EvaGrammarParser::File_inputContext::getRuleIndex() const {
  return EvaGrammarParser::RuleFile_input;
}

void EvaGrammarParser::File_inputContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile_input(this);
}

void EvaGrammarParser::File_inputContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile_input(this);
}

EvaGrammarParser::File_inputContext* EvaGrammarParser::file_input() {
  File_inputContext *_localctx = _tracker.createInstance<File_inputContext>(_ctx, getState());
  enterRule(_localctx, 0, EvaGrammarParser::RuleFile_input);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(16);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << EvaGrammarParser::T__3)
      | (1ULL << EvaGrammarParser::INT)
      | (1ULL << EvaGrammarParser::NEWLINE))) != 0)) {
      setState(14);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case EvaGrammarParser::NEWLINE: {
          setState(12);
          match(EvaGrammarParser::NEWLINE);
          break;
        }

        case EvaGrammarParser::T__3:
        case EvaGrammarParser::INT: {
          setState(13);
          e(0);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(18);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(19);
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

EvaGrammarParser::EContext* EvaGrammarParser::Single_inputContext::e() {
  return getRuleContext<EvaGrammarParser::EContext>(0);
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

EvaGrammarParser::Single_inputContext* EvaGrammarParser::single_input() {
  Single_inputContext *_localctx = _tracker.createInstance<Single_inputContext>(_ctx, getState());
  enterRule(_localctx, 2, EvaGrammarParser::RuleSingle_input);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(26);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(21);
      match(EvaGrammarParser::NEWLINE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(22);
      e(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(23);
      e(0);
      setState(24);
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

//----------------- EContext ------------------------------------------------------------------

EvaGrammarParser::EContext::EContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EvaGrammarParser::TContext* EvaGrammarParser::EContext::t() {
  return getRuleContext<EvaGrammarParser::TContext>(0);
}

EvaGrammarParser::EContext* EvaGrammarParser::EContext::e() {
  return getRuleContext<EvaGrammarParser::EContext>(0);
}


size_t EvaGrammarParser::EContext::getRuleIndex() const {
  return EvaGrammarParser::RuleE;
}

void EvaGrammarParser::EContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterE(this);
}

void EvaGrammarParser::EContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitE(this);
}


EvaGrammarParser::EContext* EvaGrammarParser::e() {
   return e(0);
}

EvaGrammarParser::EContext* EvaGrammarParser::e(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  EvaGrammarParser::EContext *_localctx = _tracker.createInstance<EContext>(_ctx, parentState);
  EvaGrammarParser::EContext *previousContext = _localctx;
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, EvaGrammarParser::RuleE, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(29);
    t(0);
    _ctx->stop = _input->LT(-1);
    setState(36);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<EContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleE);
        setState(31);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(32);
        match(EvaGrammarParser::T__0);
        setState(33);
        t(0); 
      }
      setState(38);
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

//----------------- TContext ------------------------------------------------------------------

EvaGrammarParser::TContext::TContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EvaGrammarParser::MContext* EvaGrammarParser::TContext::m() {
  return getRuleContext<EvaGrammarParser::MContext>(0);
}

EvaGrammarParser::TContext* EvaGrammarParser::TContext::t() {
  return getRuleContext<EvaGrammarParser::TContext>(0);
}


size_t EvaGrammarParser::TContext::getRuleIndex() const {
  return EvaGrammarParser::RuleT;
}

void EvaGrammarParser::TContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterT(this);
}

void EvaGrammarParser::TContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitT(this);
}


EvaGrammarParser::TContext* EvaGrammarParser::t() {
   return t(0);
}

EvaGrammarParser::TContext* EvaGrammarParser::t(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  EvaGrammarParser::TContext *_localctx = _tracker.createInstance<TContext>(_ctx, parentState);
  EvaGrammarParser::TContext *previousContext = _localctx;
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, EvaGrammarParser::RuleT, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(40);
    m(0);
    _ctx->stop = _input->LT(-1);
    setState(47);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleT);
        setState(42);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(43);
        match(EvaGrammarParser::T__1);
        setState(44);
        m(0); 
      }
      setState(49);
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

//----------------- MContext ------------------------------------------------------------------

EvaGrammarParser::MContext::MContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EvaGrammarParser::FContext* EvaGrammarParser::MContext::f() {
  return getRuleContext<EvaGrammarParser::FContext>(0);
}

EvaGrammarParser::MContext* EvaGrammarParser::MContext::m() {
  return getRuleContext<EvaGrammarParser::MContext>(0);
}


size_t EvaGrammarParser::MContext::getRuleIndex() const {
  return EvaGrammarParser::RuleM;
}

void EvaGrammarParser::MContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterM(this);
}

void EvaGrammarParser::MContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitM(this);
}


EvaGrammarParser::MContext* EvaGrammarParser::m() {
   return m(0);
}

EvaGrammarParser::MContext* EvaGrammarParser::m(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  EvaGrammarParser::MContext *_localctx = _tracker.createInstance<MContext>(_ctx, parentState);
  EvaGrammarParser::MContext *previousContext = _localctx;
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, EvaGrammarParser::RuleM, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(51);
    f();
    _ctx->stop = _input->LT(-1);
    setState(58);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleM);
        setState(53);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(54);
        match(EvaGrammarParser::T__2);
        setState(55);
        f(); 
      }
      setState(60);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
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

EvaGrammarParser::FContext::FContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EvaGrammarParser::FContext::INT() {
  return getToken(EvaGrammarParser::INT, 0);
}

EvaGrammarParser::EContext* EvaGrammarParser::FContext::e() {
  return getRuleContext<EvaGrammarParser::EContext>(0);
}


size_t EvaGrammarParser::FContext::getRuleIndex() const {
  return EvaGrammarParser::RuleF;
}

void EvaGrammarParser::FContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterF(this);
}

void EvaGrammarParser::FContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<EvaGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitF(this);
}

EvaGrammarParser::FContext* EvaGrammarParser::f() {
  FContext *_localctx = _tracker.createInstance<FContext>(_ctx, getState());
  enterRule(_localctx, 10, EvaGrammarParser::RuleF);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(66);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case EvaGrammarParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(61);
        match(EvaGrammarParser::INT);
        break;
      }

      case EvaGrammarParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(62);
        match(EvaGrammarParser::T__3);
        setState(63);
        e(0);
        setState(64);
        match(EvaGrammarParser::T__4);
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
    case 2: return eSempred(dynamic_cast<EContext *>(context), predicateIndex);
    case 3: return tSempred(dynamic_cast<TContext *>(context), predicateIndex);
    case 4: return mSempred(dynamic_cast<MContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool EvaGrammarParser::eSempred(EContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool EvaGrammarParser::tSempred(TContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool EvaGrammarParser::mSempred(MContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);

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
  "file_input", "single_input", "e", "t", "m", "f"
};

std::vector<std::string> EvaGrammarParser::_literalNames = {
  "", "'+'", "'*'", "'%'", "'('", "')'"
};

std::vector<std::string> EvaGrammarParser::_symbolicNames = {
  "", "", "", "", "", "", "INT", "NEWLINE"
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
    0x3, 0x9, 0x47, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x3, 
    0x2, 0x3, 0x2, 0x7, 0x2, 0x11, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x14, 0xb, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x1d, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x25, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x28, 
    0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x7, 0x5, 0x30, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x33, 0xb, 0x5, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x3b, 0xa, 
    0x6, 0xc, 0x6, 0xe, 0x6, 0x3e, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x45, 0xa, 0x7, 0x3, 0x7, 0x2, 0x5, 0x6, 
    0x8, 0xa, 0x8, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0x2, 0x2, 0x2, 0x48, 0x2, 
    0x12, 0x3, 0x2, 0x2, 0x2, 0x4, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x6, 0x1e, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x29, 0x3, 0x2, 0x2, 0x2, 0xa, 0x34, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x44, 0x3, 0x2, 0x2, 0x2, 0xe, 0x11, 0x7, 0x9, 0x2, 0x2, 
    0xf, 0x11, 0x5, 0x6, 0x4, 0x2, 0x10, 0xe, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0xf, 0x3, 0x2, 0x2, 0x2, 0x11, 0x14, 0x3, 0x2, 0x2, 0x2, 0x12, 0x10, 
    0x3, 0x2, 0x2, 0x2, 0x12, 0x13, 0x3, 0x2, 0x2, 0x2, 0x13, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x12, 0x3, 0x2, 0x2, 0x2, 0x15, 0x16, 0x7, 0x2, 
    0x2, 0x3, 0x16, 0x3, 0x3, 0x2, 0x2, 0x2, 0x17, 0x1d, 0x7, 0x9, 0x2, 
    0x2, 0x18, 0x1d, 0x5, 0x6, 0x4, 0x2, 0x19, 0x1a, 0x5, 0x6, 0x4, 0x2, 
    0x1a, 0x1b, 0x7, 0x9, 0x2, 0x2, 0x1b, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1c, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x1d, 0x5, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x8, 
    0x4, 0x1, 0x2, 0x1f, 0x20, 0x5, 0x8, 0x5, 0x2, 0x20, 0x26, 0x3, 0x2, 
    0x2, 0x2, 0x21, 0x22, 0xc, 0x4, 0x2, 0x2, 0x22, 0x23, 0x7, 0x3, 0x2, 
    0x2, 0x23, 0x25, 0x5, 0x8, 0x5, 0x2, 0x24, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0x25, 0x28, 0x3, 0x2, 0x2, 0x2, 0x26, 0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0x27, 0x7, 0x3, 0x2, 0x2, 0x2, 0x28, 0x26, 
    0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x8, 0x5, 0x1, 0x2, 0x2a, 0x2b, 0x5, 
    0xa, 0x6, 0x2, 0x2b, 0x31, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0xc, 0x4, 
    0x2, 0x2, 0x2d, 0x2e, 0x7, 0x4, 0x2, 0x2, 0x2e, 0x30, 0x5, 0xa, 0x6, 
    0x2, 0x2f, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x30, 0x33, 0x3, 0x2, 0x2, 0x2, 
    0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x3, 0x2, 0x2, 0x2, 0x32, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 
    0x8, 0x6, 0x1, 0x2, 0x35, 0x36, 0x5, 0xc, 0x7, 0x2, 0x36, 0x3c, 0x3, 
    0x2, 0x2, 0x2, 0x37, 0x38, 0xc, 0x4, 0x2, 0x2, 0x38, 0x39, 0x7, 0x5, 
    0x2, 0x2, 0x39, 0x3b, 0x5, 0xc, 0x7, 0x2, 0x3a, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x3b, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3a, 0x3, 0x2, 0x2, 0x2, 
    0x3c, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3d, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x3c, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x45, 0x7, 0x8, 0x2, 0x2, 0x40, 0x41, 
    0x7, 0x6, 0x2, 0x2, 0x41, 0x42, 0x5, 0x6, 0x4, 0x2, 0x42, 0x43, 0x7, 
    0x7, 0x2, 0x2, 0x43, 0x45, 0x3, 0x2, 0x2, 0x2, 0x44, 0x3f, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x40, 0x3, 0x2, 0x2, 0x2, 0x45, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x9, 0x10, 0x12, 0x1c, 0x26, 0x31, 0x3c, 0x44, 
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
