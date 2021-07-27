
// Generated from source/EvaGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "EvaGrammarParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by EvaGrammarParser.
 */
class  EvaGrammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(EvaGrammarParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(EvaGrammarParser::ProgramContext *ctx) = 0;

  virtual void enterSingle_input(EvaGrammarParser::Single_inputContext *ctx) = 0;
  virtual void exitSingle_input(EvaGrammarParser::Single_inputContext *ctx) = 0;

  virtual void enterExpr(EvaGrammarParser::ExprContext *ctx) = 0;
  virtual void exitExpr(EvaGrammarParser::ExprContext *ctx) = 0;

  virtual void enterTerm(EvaGrammarParser::TermContext *ctx) = 0;
  virtual void exitTerm(EvaGrammarParser::TermContext *ctx) = 0;

  virtual void enterLiteral(EvaGrammarParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(EvaGrammarParser::LiteralContext *ctx) = 0;


};

