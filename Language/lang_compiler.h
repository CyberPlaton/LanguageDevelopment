#pragma once

#include "lang_common.h"
#include "lang_chunk.h"

#ifdef _DEBUG
#include "lang_debug.h"
#endif

struct LangCompiler;

enum LangTokenType
{
	token_invalid = -1,

	// Single char. tokens
	token_left_bracket,		// (
	token_right_bracket,	// )
	token_left_brace,		// {
	token_right_brace,		// }
	token_comma,			// ,
	token_dot,				// .
	token_semicolon,		// ;
	token_slash,			// /
	token_star,				// *
	token_plus,				// +
	token_minus,			// -

	// Single or two char. tokens
	token_not_equal,		// !=
	token_equal,			// =
	token_equal_equal,		// ==
	token_not,				// !
	token_greater,			// >
	token_less,				// <
	token_greater_equal,	// >=
	token_less_equal,		// <=

	// Literals
	token_identifier,
	token_string,
	token_number,

	// Keywords
	token_and,
	token_or,
	token_if,
	token_else,
	token_true,
	token_false,
	token_for,
	token_while,
	token_fun,
	token_nil,
	token_return,
	token_super,
	token_this,
	token_var,
	token_class,

	token_print,

	token_eof,
	token_error,
};


enum LangPrecedence
{
	prec_none,
	prec_assignment,  // =
	prec_or,          // or
	prec_and,         // and
	prec_equality,    // == !=
	prec_comparison,  // < > <= >=
	prec_term,        // + -
	prec_factor,      // * /
	prec_unary,       // ! -
	prec_call,        // . ()
	prec_primary
};


using LangParseFn = void(*)(LangCompiler*);
struct LangParseRule
{
	LangParseRule(LangParseFn prefix_fun, LangParseFn infix_fun, LangPrecedence prec) :
		prefix(prefix_fun), infix(infix_fun), precedence(prec)
	{

	}

	LangParseFn prefix;
	LangParseFn infix;
	LangPrecedence precedence;
};


struct LangToken
{
	LangTokenType type;
	const char* start = nullptr;
	int length = 0;
	int line = 0;
};


struct LangParser
{
	LangToken current;
	LangToken previous;
	bool hadError = false;
	bool panicMode = false;
};



struct LangCompiler
{
	static void emitErrorAtCurrentToken(LangCompiler* comp, const std::string& msg);
	static void emitErrorAtPreviousToken(LangCompiler* comp, const std::string& msg);
	static void emitError(LangCompiler* comp, LangToken token, const std::string& msg);

	/*
	* Compiling related functions.
	*/
	static bool compile(LangCompiler* comp, const std::string& source, LangChunk* chunk);
	static void freeCompiler(LangCompiler* comp);
	static void advanceCompiler(LangCompiler* comp);
	static void consume(LangCompiler* comp, LangTokenType type, const std::string& msg);

	static void emitReturn(LangCompiler* comp);
	static void emitByte(LangCompiler* comp, byte b);
	static void emitBytes(LangCompiler* comp, byte b1, byte b2);
	static void emitConstant(LangCompiler* comp, LangValue value);
	static byte makeConstant(LangCompiler* comp, LangValue value);
	static void expression(LangCompiler* comp);
	static LangChunk* currentChunk(LangCompiler* comp);
	static void grouping(LangCompiler* comp);
	static void unary(LangCompiler* comp);
	static void binary(LangCompiler* comp);
	static void number(LangCompiler* comp);
	static void parsePrecedence(LangCompiler* comp, LangPrecedence prec);
	static LangParseRule getRule(LangCompiler* comp, LangTokenType type);

	/*
	* Scanning related functions.
	*/
	static void scan(LangCompiler* comp, const std::string& source);
	static LangToken scanToken(LangCompiler* comp);
	static bool isAtEnd(LangCompiler* comp);
	static LangToken makeToken(LangCompiler* comp, LangTokenType type);
	static LangToken errorToken(LangCompiler* comp, const std::string& msg);
	static char advance(LangCompiler* comp);
	static bool match(LangCompiler* comp, char expected);
	static void skipWhitespace(LangCompiler* comp);
	static char peek(LangCompiler* comp);
	static char peekNext(LangCompiler* comp);
	static bool isDigit(char c);
	static bool isLetter(char c);
	static LangToken makeIdentifier(LangCompiler* comp);
	static LangToken makeNumber(LangCompiler* comp);
	static LangToken makeString(LangCompiler* comp);
	static LangTokenType identifierType(LangCompiler* comp);
	static LangTokenType checkKeyword(LangCompiler* comp, int start, int length, const char* rest, LangTokenType type);


	const char* start = nullptr;
	const char* current = nullptr;
	int line = 0;

	static LangParser* parser;

	static LangChunk* compilingChunk;


	static std::map<LangTokenType, LangParseRule> rules;
};