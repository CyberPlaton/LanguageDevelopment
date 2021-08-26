#pragma once

#include "lang_common.h"

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

struct LangToken
{
	LangTokenType type;
	const char* start = nullptr;
	int length = 0;
	int line = 0;
};


struct LangCompiler
{
	/*
	* Compiling related functions.
	*/
	static void compile(LangCompiler* comp, const std::string& source);
	

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
};