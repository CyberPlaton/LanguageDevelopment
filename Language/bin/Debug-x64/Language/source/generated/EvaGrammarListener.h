
// Generated from source/EvaGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "EvaGrammarParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by EvaGrammarParser.
 */
class  EvaGrammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile_input(EvaGrammarParser::File_inputContext *ctx) = 0;
  virtual void exitFile_input(EvaGrammarParser::File_inputContext *ctx) = 0;

  virtual void enterSingle_input(EvaGrammarParser::Single_inputContext *ctx) = 0;
  virtual void exitSingle_input(EvaGrammarParser::Single_inputContext *ctx) = 0;

  virtual void enterE(EvaGrammarParser::EContext *ctx) = 0;
  virtual void exitE(EvaGrammarParser::EContext *ctx) = 0;

  virtual void enterT(EvaGrammarParser::TContext *ctx) = 0;
  virtual void exitT(EvaGrammarParser::TContext *ctx) = 0;

  virtual void enterM(EvaGrammarParser::MContext *ctx) = 0;
  virtual void exitM(EvaGrammarParser::MContext *ctx) = 0;

  virtual void enterF(EvaGrammarParser::FContext *ctx) = 0;
  virtual void exitF(EvaGrammarParser::FContext *ctx) = 0;


};

