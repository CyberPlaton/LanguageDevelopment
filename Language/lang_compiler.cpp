#include "lang_compiler.h"


void LangCompiler::compile(LangCompiler* comp, const std::string& source)
{

}


void LangCompiler::scan(LangCompiler* comp, const std::string& source)
{
	// Initialize.
	comp->start = source.c_str();
	comp->current = source.c_str();
	comp->line = 1;


}


char LangCompiler::peek(LangCompiler* comp)
{
	return *comp->current;
}

char LangCompiler::peekNext(LangCompiler* comp)
{
	if (LangCompiler::isAtEnd(comp)) return '\0';

	return comp->current[1];
}

char LangCompiler::advance(LangCompiler* comp)
{
	comp->current++;
	return comp->current[-1];
}

bool LangCompiler::match(LangCompiler* comp, char expected)
{
	if (LangCompiler::isAtEnd(comp)) return false;

	if (*comp->current != expected) return false;

	comp->current++;

	return true;
}

void LangCompiler::skipWhitespace(LangCompiler* comp)
{
	while (true)
	{
		char c = LangCompiler::peek(comp);

		switch (c)
		{
		case ' ':
		case '\r':
		case '\t':
			LangCompiler::advance(comp);
			break;

		case '\n':
			comp->line++;
			LangCompiler::advance(comp);
			break;

		case '/':
			if (LangCompiler::peekNext(comp) == '/')
			{
				// Skip commentary.
				while (LangCompiler::peek(comp) != '\n' && !LangCompiler::isAtEnd(comp)) LangCompiler::advance(comp);
			}
			else
			{
				return;
			}

		default:
			return;
		}
	}
}

bool LangCompiler::isAtEnd(LangCompiler* comp)
{
	return *comp->current == '\0';
}

LangToken LangCompiler::makeToken(LangCompiler* comp, LangTokenType type)
{
	LangToken token;
	token.type = type;
	token.start = comp->start;
	token.length = (int)(comp->current - comp->start);
	token.line = comp->line;
	return token;
}


LangToken LangCompiler::makeString(LangCompiler* comp)
{
	while (LangCompiler::peek(comp) != '"' && !LangCompiler::isAtEnd(comp))
	{
		if (LangCompiler::peek(comp) == '\n') comp->line++;

		LangCompiler::advance(comp);
	}


	if (LangCompiler::isAtEnd(comp)) return LangCompiler::errorToken(comp, "Unterminated String");

	LangCompiler::advance(comp);
	return LangCompiler::makeToken(comp, LangTokenType::token_string);
}


bool LangCompiler::isDigit(LangCompiler* comp, char c)
{
	return c >= '0' && c <= '9';
}


LangToken LangCompiler::makeNumber(LangCompiler* comp)
{
	while (LangCompiler::isDigit(comp, LangCompiler::peek(comp))) LangCompiler::advance(comp);

	// Fraction.
	if (LangCompiler::peek(comp) == '.' &&
		LangCompiler::isDigit(comp, LangCompiler::peekNext(comp)))
	{
		LangCompiler::advance(comp);

		while (LangCompiler::isDigit(comp, LangCompiler::peek(comp)))
		{
			LangCompiler::advance(comp);
		}
	}

	return LangCompiler::makeToken(comp, LangTokenType::token_number);
}


LangToken LangCompiler::errorToken(LangCompiler* comp, const std::string& msg)
{
	LangToken token;
	token.type = LangTokenType::token_error;
	token.start = msg.c_str();
	token.length = msg.length();
	token.line = comp->line;
	return token;
}


LangToken LangCompiler::scanToken(LangCompiler* comp)
{
	LangCompiler::skipWhitespace(comp);

	comp->start = comp->current;

	if (LangCompiler::isAtEnd(comp))
	{
		return LangCompiler::makeToken(comp, LangTokenType::token_eof);
	}

	char c = LangCompiler::advance(comp);

	if (LangCompiler::isDigit(comp, c)) return LangCompiler::makeNumber(comp);

	switch (c)
	{
		// Single Character
	case '(': return LangCompiler::makeToken(comp, LangTokenType::token_left_bracket);
	case ')': return LangCompiler::makeToken(comp, LangTokenType::token_right_bracket);
	case '{': return LangCompiler::makeToken(comp, LangTokenType::token_left_brace);
	case '}': return LangCompiler::makeToken(comp, LangTokenType::token_right_brace);
	case ';': return LangCompiler::makeToken(comp, LangTokenType::token_semicolon);
	case ',': return LangCompiler::makeToken(comp, LangTokenType::token_comma);
	case '.': return LangCompiler::makeToken(comp, LangTokenType::token_dot);
	case '-': return LangCompiler::makeToken(comp, LangTokenType::token_minus);
	case '+': return LangCompiler::makeToken(comp, LangTokenType::token_plus);
	case '/': return LangCompiler::makeToken(comp, LangTokenType::token_slash);
	case '*': return LangCompiler::makeToken(comp, LangTokenType::token_star);

		// Single or two character
	case '!': return LangCompiler::makeToken(comp, LangCompiler::match(comp, '=') ? LangTokenType::token_not_equal : LangTokenType::token_not);
	case '=': return LangCompiler::makeToken(comp, LangCompiler::match(comp, '=') ? LangTokenType::token_equal_equal : LangTokenType::token_equal);
	case '<': return LangCompiler::makeToken(comp, LangCompiler::match(comp, '=') ? LangTokenType::token_less_equal : LangTokenType::token_less);
	case '>': return LangCompiler::makeToken(comp, LangCompiler::match(comp, '=') ? LangTokenType::token_greater_equal : LangTokenType::token_greater);

		// Literals
	case '"': return LangCompiler::makeString(comp);
	}


	return LangCompiler::errorToken(comp, "Unexpected character");
}