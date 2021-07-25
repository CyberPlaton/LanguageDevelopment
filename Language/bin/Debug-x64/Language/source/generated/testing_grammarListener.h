
// Generated from source/testing_grammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "testing_grammarParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by testing_grammarParser.
 */
class  testing_grammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterE(testing_grammarParser::EContext *ctx) = 0;
  virtual void exitE(testing_grammarParser::EContext *ctx) = 0;

  virtual void enterT(testing_grammarParser::TContext *ctx) = 0;
  virtual void exitT(testing_grammarParser::TContext *ctx) = 0;

  virtual void enterM(testing_grammarParser::MContext *ctx) = 0;
  virtual void exitM(testing_grammarParser::MContext *ctx) = 0;

  virtual void enterF(testing_grammarParser::FContext *ctx) = 0;
  virtual void exitF(testing_grammarParser::FContext *ctx) = 0;


};

