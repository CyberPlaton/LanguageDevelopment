
// Generated from source/EvaGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "EvaGrammarListener.h"


/**
 * This class provides an empty implementation of EvaGrammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  EvaGrammarBaseListener : public EvaGrammarListener {
public:

  virtual void enterProgram(EvaGrammarParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(EvaGrammarParser::ProgramContext * /*ctx*/) override { }

  virtual void enterSingle_input(EvaGrammarParser::Single_inputContext * /*ctx*/) override { }
  virtual void exitSingle_input(EvaGrammarParser::Single_inputContext * /*ctx*/) override { }

  virtual void enterExpr(EvaGrammarParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(EvaGrammarParser::ExprContext * /*ctx*/) override { }

  virtual void enterTerm(EvaGrammarParser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(EvaGrammarParser::TermContext * /*ctx*/) override { }

  virtual void enterLiteral(EvaGrammarParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(EvaGrammarParser::LiteralContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

