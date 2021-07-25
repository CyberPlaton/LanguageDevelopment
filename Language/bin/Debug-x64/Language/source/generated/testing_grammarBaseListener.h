
// Generated from source/testing_grammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "testing_grammarListener.h"


/**
 * This class provides an empty implementation of testing_grammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  testing_grammarBaseListener : public testing_grammarListener {
public:

  virtual void enterE(testing_grammarParser::EContext * /*ctx*/) override { }
  virtual void exitE(testing_grammarParser::EContext * /*ctx*/) override { }

  virtual void enterT(testing_grammarParser::TContext * /*ctx*/) override { }
  virtual void exitT(testing_grammarParser::TContext * /*ctx*/) override { }

  virtual void enterM(testing_grammarParser::MContext * /*ctx*/) override { }
  virtual void exitM(testing_grammarParser::MContext * /*ctx*/) override { }

  virtual void enterF(testing_grammarParser::FContext * /*ctx*/) override { }
  virtual void exitF(testing_grammarParser::FContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

