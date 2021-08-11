
// Generated from source/EvaGrammar.g4 by ANTLR 4.7


#include "EvaGrammarLexer.h"


using namespace antlr4;


EvaGrammarLexer::EvaGrammarLexer(CharStream *input) : Lexer(input) {
  _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

EvaGrammarLexer::~EvaGrammarLexer() {
  delete _interpreter;
}

std::string EvaGrammarLexer::getGrammarFileName() const {
  return "EvaGrammar.g4";
}

const std::vector<std::string>& EvaGrammarLexer::getRuleNames() const {
  return _ruleNames;
}

const std::vector<std::string>& EvaGrammarLexer::getChannelNames() const {
  return _channelNames;
}

const std::vector<std::string>& EvaGrammarLexer::getModeNames() const {
  return _modeNames;
}

const std::vector<std::string>& EvaGrammarLexer::getTokenNames() const {
  return _tokenNames;
}

dfa::Vocabulary& EvaGrammarLexer::getVocabulary() const {
  return _vocabulary;
}

const std::vector<uint16_t> EvaGrammarLexer::getSerializedATN() const {
  return _serializedATN;
}

const atn::ATN& EvaGrammarLexer::getATN() const {
  return _atn;
}




// Static vars and initialization.
std::vector<dfa::DFA> EvaGrammarLexer::_decisionToDFA;
atn::PredictionContextCache EvaGrammarLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN EvaGrammarLexer::_atn;
std::vector<uint16_t> EvaGrammarLexer::_serializedATN;

std::vector<std::string> EvaGrammarLexer::_ruleNames = {
  u8"INT", u8"NEWLINE", u8"WS", u8"MUL", u8"PLUS", u8"MINUS", u8"DIVIDE"
};

std::vector<std::string> EvaGrammarLexer::_channelNames = {
  "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
};

std::vector<std::string> EvaGrammarLexer::_modeNames = {
  u8"DEFAULT_MODE"
};

std::vector<std::string> EvaGrammarLexer::_literalNames = {
  "", "", "", "", u8"'*'", u8"'+'", u8"'-'", u8"'/'"
};

std::vector<std::string> EvaGrammarLexer::_symbolicNames = {
  "", u8"INT", u8"NEWLINE", u8"WS", u8"MUL", u8"PLUS", u8"MINUS", u8"DIVIDE"
};

dfa::Vocabulary EvaGrammarLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> EvaGrammarLexer::_tokenNames;

EvaGrammarLexer::Initializer::Initializer() {
  // This code could be in a static initializer lambda, but VS doesn't allow access to private class members from there.
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
    0x2, 0x9, 0x26, 0x8, 0x1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 
    0x4, 0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
    0x7, 0x4, 0x8, 0x9, 0x8, 0x3, 0x2, 0x6, 0x2, 0x13, 0xa, 0x2, 0xd, 0x2, 
    0xe, 0x2, 0x14, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x2, 0x2, 0x9, 0x3, 0x3, 0x5, 0x4, 
    0x7, 0x5, 0x9, 0x6, 0xb, 0x7, 0xd, 0x8, 0xf, 0x9, 0x3, 0x2, 0x5, 0x3, 
    0x2, 0x32, 0x3b, 0x4, 0x2, 0xc, 0xc, 0xf, 0xf, 0x6, 0x2, 0xb, 0xb, 0x22, 
    0x22, 0x29, 0x29, 0x7e, 0x7e, 0x2, 0x26, 0x2, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x2, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x2, 0xb, 0x3, 0x2, 0x2, 0x2, 0x2, 0xd, 0x3, 0x2, 
    0x2, 0x2, 0x2, 0xf, 0x3, 0x2, 0x2, 0x2, 0x3, 0x12, 0x3, 0x2, 0x2, 0x2, 
    0x5, 0x16, 0x3, 0x2, 0x2, 0x2, 0x7, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x9, 0x1e, 
    0x3, 0x2, 0x2, 0x2, 0xb, 0x20, 0x3, 0x2, 0x2, 0x2, 0xd, 0x22, 0x3, 0x2, 
    0x2, 0x2, 0xf, 0x24, 0x3, 0x2, 0x2, 0x2, 0x11, 0x13, 0x9, 0x2, 0x2, 
    0x2, 0x12, 0x11, 0x3, 0x2, 0x2, 0x2, 0x13, 0x14, 0x3, 0x2, 0x2, 0x2, 
    0x14, 0x12, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x3, 0x2, 0x2, 0x2, 0x15, 
    0x4, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 0x9, 0x3, 0x2, 0x2, 0x17, 0x18, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x8, 0x3, 0x2, 0x2, 0x19, 0x6, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x1b, 0x9, 0x4, 0x2, 0x2, 0x1b, 0x1c, 0x3, 0x2, 
    0x2, 0x2, 0x1c, 0x1d, 0x8, 0x4, 0x2, 0x2, 0x1d, 0x8, 0x3, 0x2, 0x2, 
    0x2, 0x1e, 0x1f, 0x7, 0x2c, 0x2, 0x2, 0x1f, 0xa, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0x21, 0x7, 0x2d, 0x2, 0x2, 0x21, 0xc, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x23, 0x7, 0x2f, 0x2, 0x2, 0x23, 0xe, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 
    0x7, 0x31, 0x2, 0x2, 0x25, 0x10, 0x3, 0x2, 0x2, 0x2, 0x4, 0x2, 0x14, 
    0x3, 0x8, 0x2, 0x2, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

EvaGrammarLexer::Initializer EvaGrammarLexer::_init;
