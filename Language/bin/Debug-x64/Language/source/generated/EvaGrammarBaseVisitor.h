
// Generated from source/EvaGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "EvaGrammarVisitor.h"


/**
 * This class provides an empty implementation of EvaGrammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  EvaGrammarBaseVisitor : public EvaGrammarVisitor {
public:

  virtual antlrcpp::Any visitProgram(EvaGrammarParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSingle_input(EvaGrammarParser::Single_inputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(EvaGrammarParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTerm(EvaGrammarParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteral(EvaGrammarParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

