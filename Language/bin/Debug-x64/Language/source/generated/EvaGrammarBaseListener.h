
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

  virtual void enterFile_input(EvaGrammarParser::File_inputContext * /*ctx*/) override { }
  virtual void exitFile_input(EvaGrammarParser::File_inputContext * /*ctx*/) override { }

  virtual void enterSingle_input(EvaGrammarParser::Single_inputContext * /*ctx*/) override { }
  virtual void exitSingle_input(EvaGrammarParser::Single_inputContext * /*ctx*/) override { }

  virtual void enterE(EvaGrammarParser::EContext * /*ctx*/) override { }
  virtual void exitE(EvaGrammarParser::EContext * /*ctx*/) override { }

  virtual void enterT(EvaGrammarParser::TContext * /*ctx*/) override { }
  virtual void exitT(EvaGrammarParser::TContext * /*ctx*/) override { }

  virtual void enterM(EvaGrammarParser::MContext * /*ctx*/) override { }
  virtual void exitM(EvaGrammarParser::MContext * /*ctx*/) override { }

  virtual void enterF(EvaGrammarParser::FContext * /*ctx*/) override { }
  virtual void exitF(EvaGrammarParser::FContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

