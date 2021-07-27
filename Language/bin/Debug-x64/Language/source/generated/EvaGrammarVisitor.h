
// Generated from source/EvaGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "EvaGrammarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by EvaGrammarParser.
 */
class  EvaGrammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by EvaGrammarParser.
   */
    virtual antlrcpp::Any visitProgram(EvaGrammarParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitSingle_input(EvaGrammarParser::Single_inputContext *context) = 0;

    virtual antlrcpp::Any visitExpr(EvaGrammarParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitTerm(EvaGrammarParser::TermContext *context) = 0;

    virtual antlrcpp::Any visitLiteral(EvaGrammarParser::LiteralContext *context) = 0;


};

