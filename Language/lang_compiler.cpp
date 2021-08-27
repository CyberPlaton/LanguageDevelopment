#include "lang_compiler.h"

LangParser* LangCompiler::parser = nullptr;
LangChunk* LangCompiler::compilingChunk = nullptr;
std::map<LangTokenType, LangParseRule> LangCompiler::rules;


void LangCompiler::emitErrorAtCurrentToken(LangCompiler* comp, const std::string& msg)
{
	LangCompiler::emitError(comp, comp->parser->current, msg);
}


void LangCompiler::emitErrorAtPreviousToken(LangCompiler* comp, const std::string& msg)
{
	LangCompiler::emitError(comp, comp->parser->previous, msg);
}


void LangCompiler::emitError(LangCompiler* comp, LangToken token, const std::string& msg)
{
	printf("[Ln %d] Error", token.line);

	if (token.type == LangTokenType::token_eof)
	{
		printf(" at End ");
	}
	else if (token.type == LangTokenType::token_error)
	{
		// ...
	}
	else
	{
		printf(" at '%.*s' ", token.length, token.start);
	}

	printf(": %s \n", msg);

	comp->parser->hadError = true;
	comp->parser->panicMode = true;
}


void LangCompiler::emitReturn(LangCompiler* comp)
{
	LangCompiler::emitByte(comp, LangOpCode::op_return);
}


void LangCompiler::emitBytes(LangCompiler* comp, byte b1, byte b2)
{
	LangCompiler::emitByte(comp, b1);
	LangCompiler::emitByte(comp, b2);
}


void LangCompiler::expression(LangCompiler* comp)
{
	LangCompiler::parsePrecedence(comp, LangPrecedence::prec_assignment);
}


void LangCompiler::emitConstant(LangCompiler* comp, LangValue value)
{
	LangCompiler::emitBytes(comp, LangOpCode::op_return, LangCompiler::makeConstant(comp, value));
}


void LangCompiler::number(LangCompiler* comp)
{
	LangValue v = strtod(comp->parser->previous.start, NULL);
	LangCompiler::emitConstant(comp, v);
}


byte LangCompiler::makeConstant(LangCompiler* comp, LangValue value)
{
	int c = LangChunk::addConstant(comp->currentChunk(comp), value);

	if (c > UINT8_MAX)
	{
		printf("Error! To many constants on chunk!");
		return 0;
	}

	return (byte)c;
}


LangParseRule LangCompiler::getRule(LangCompiler* comp, LangTokenType type)
{
	return comp->rules[type];
}


void LangCompiler::binary(LangCompiler* comp)
{
	LangTokenType op_type = comp->parser->previous.type;

	LangParseRule* rule = &LangCompiler::getRule(comp, op_type);

	LangCompiler::parsePrecedence(comp, (LangPrecedence)(rule->precedence + 1));

	switch (op_type)
	{
	case LangTokenType::token_plus: LangCompiler::emitByte(comp, LangOpCode::op_add); break;
	case LangTokenType::token_minus:LangCompiler::emitByte(comp, LangOpCode::op_subtract); break;
	case LangTokenType::token_star:LangCompiler::emitByte(comp, LangOpCode::op_multiply); break;
	case LangTokenType::token_slash:LangCompiler::emitByte(comp, LangOpCode::op_divide); break;
	default:return;
	}
}

void LangCompiler::unary(LangCompiler* comp)
{
	LangCompiler::parsePrecedence(comp, LangPrecedence::prec_unary);

	LangTokenType op_type = comp->parser->previous.type;

	LangCompiler::expression(comp);

	switch (op_type)
	{
	case LangTokenType::token_minus: LangCompiler::emitByte(comp, LangOpCode::op_negate); break;
	default:
		return;
	}
}


void LangCompiler::parsePrecedence(LangCompiler* comp, LangPrecedence prec)
{
	LangCompiler::advance(comp);

	LangParseFn prefix_rule = LangCompiler::getRule(comp, comp->parser->previous.type).prefix;

	if (prefix_rule == NULL)
	{
		printf("Error! Expect Expression!");
		return;
	}


	prefix_rule(comp);


	while (prec <= LangCompiler::getRule(comp, comp->parser->current.type).precedence)
	{
		LangCompiler::advance(comp);

		LangParseFn infix_rule = LangCompiler::getRule(comp, comp->parser->current.type).infix;

		infix_rule(comp);
	}
}



void LangCompiler::grouping(LangCompiler* comp)
{
	LangCompiler::expression(comp);
	LangCompiler::consume(comp, LangTokenType::token_right_bracket, "Expected \")\" after expression");
}

bool LangCompiler::compile(LangCompiler* comp, const std::string& source, LangChunk* chunk)
{
	// Initialize rules.
	comp->rules.emplace(std::make_pair(LangTokenType::token_left_bracket, LangParseRule(LangCompiler::grouping, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_right_bracket, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_left_brace, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_right_brace, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_comma, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_dot, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_semicolon, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_slash, LangParseRule(NULL, LangCompiler::binary, LangPrecedence::prec_factor)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_star, LangParseRule(NULL, LangCompiler::binary, LangPrecedence::prec_factor)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_plus, LangParseRule(NULL, LangCompiler::binary, LangPrecedence::prec_term)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_minus, LangParseRule(LangCompiler::unary, LangCompiler::binary, LangPrecedence::prec_term)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_not_equal, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_equal, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_equal_equal, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_not, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_greater, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_less, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_greater_equal, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_less_equal, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_identifier, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_string, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_number, LangParseRule(LangCompiler::number, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_and, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_or, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_if, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_else, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_true, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_false, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_for, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_while, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_fun, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_nil, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_return, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_super, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_this, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_var, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_class, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_print, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_eof, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));
	comp->rules.emplace(std::make_pair(LangTokenType::token_error, LangParseRule(NULL, NULL, LangPrecedence::prec_none)));


	// Initialize.
	comp->start = source.c_str();
	comp->current = source.c_str();
	comp->line = 1;

	comp->parser->hadError = false;
	comp->parser->panicMode = false;

	comp->compilingChunk = chunk;

	LangCompiler::advanceCompiler(comp);
	LangCompiler::expression(comp);
	LangCompiler::consume(comp, LangTokenType::token_eof, "Expected EOF");
	LangCompiler::emitReturn(comp); // End compilation.


#ifdef _DEBUG
	if (comp->parser->hadError)
	{
		LangDebugger::disassembleChunk(comp->currentChunk(comp), "code");
	}
#endif


	return true;
}


void LangCompiler::emitByte(LangCompiler* comp, byte b)
{
	LangChunk::writeChunk(LangCompiler::currentChunk(comp), b, comp->parser->previous.line);
}


LangChunk* LangCompiler::currentChunk(LangCompiler* comp)
{
	return comp->compilingChunk;
}


void LangCompiler::consume(LangCompiler* comp, LangTokenType type, const std::string& msg)
{
	if (comp->parser->current.type == type)
	{
		comp->advanceCompiler(comp);
		return;
	}

	LangCompiler::emitErrorAtCurrentToken(comp, msg);
}


void LangCompiler::advanceCompiler(LangCompiler* comp)
{
	comp->parser->previous = comp->parser->current;


	for (;;)
	{
		comp->parser->current = LangCompiler::scanToken(comp);

		if (comp->parser->current.type != LangTokenType::token_error) break;

		LangCompiler::emitErrorAtCurrentToken(comp, comp->parser->current.start);
	}
}


void LangCompiler::freeCompiler(LangCompiler* comp)
{
	delete comp->current;
	delete comp->start;

	comp->current = 0;
	comp->start = 0;
	comp->line = 0;


	delete comp;
	comp = 0;
}


void LangCompiler::scan(LangCompiler* comp, const std::string& source)
{


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


bool LangCompiler::isDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool LangCompiler::isLetter(char c)
{
	return (c >= 'a' && c <= 'z' ||
			c >= 'A' && c <= 'Z' ||
			c == '_');
}

LangToken LangCompiler::makeNumber(LangCompiler* comp)
{
	while (LangCompiler::isDigit(LangCompiler::peek(comp))) LangCompiler::advance(comp);

	// Fraction.
	if (LangCompiler::peek(comp) == '.' &&
		LangCompiler::isDigit(LangCompiler::peekNext(comp)))
	{
		LangCompiler::advance(comp);

		while (LangCompiler::isDigit(LangCompiler::peek(comp)))
		{
			LangCompiler::advance(comp);
		}
	}

	return LangCompiler::makeToken(comp, LangTokenType::token_number);
}

LangTokenType LangCompiler::identifierType(LangCompiler* comp)
{
	switch (comp->start[0])
	{
	case 'a':return LangCompiler::checkKeyword(comp, 1, 2, "nd", LangTokenType::token_and);
	case 'c':return LangCompiler::checkKeyword(comp, 1, 4, "lass", LangTokenType::token_class);
	case 'e':return LangCompiler::checkKeyword(comp, 1, 3, "lse", LangTokenType::token_else);
	case 'i':return LangCompiler::checkKeyword(comp, 1, 1, "f", LangTokenType::token_if);
	case 'n':return LangCompiler::checkKeyword(comp, 1, 2, "il", LangTokenType::token_nil);
	case 'o':return LangCompiler::checkKeyword(comp, 1, 1, "r", LangTokenType::token_or);
	case 'p':return LangCompiler::checkKeyword(comp, 1, 4, "rint", LangTokenType::token_print);
	case 'r':return LangCompiler::checkKeyword(comp, 1, 5, "eturn", LangTokenType::token_return);
	case 's':return LangCompiler::checkKeyword(comp, 1, 4, "uper", LangTokenType::token_super);
	case 'v':return LangCompiler::checkKeyword(comp, 1, 2, "ar", LangTokenType::token_var);
	case 'w':return LangCompiler::checkKeyword(comp, 1, 4, "hile", LangTokenType::token_while);
	case 'f':
		if (comp->current - comp->start > 1)
		{
			switch (comp->start[1])
			{
			case 'a': return LangCompiler::checkKeyword(comp, 2, 3, "lse", LangTokenType::token_false);
			case 'o': return LangCompiler::checkKeyword(comp, 2, 1, "r", LangTokenType::token_for);
			case 'u': return LangCompiler::checkKeyword(comp, 2, 1, "n", LangTokenType::token_fun);
			}
		}
		break;

	case 't':
		if (comp->current - comp->start > 1)
		{
			switch (comp->start[1])
			{
			case 'h':return LangCompiler::checkKeyword(comp, 2, 2, "is", LangTokenType::token_this);
			case 'r':return LangCompiler::checkKeyword(comp, 2, 2, "ue", LangTokenType::token_true);
			}
		}
		break;
	}



	return LangTokenType::token_identifier;
}


LangTokenType LangCompiler::checkKeyword(LangCompiler* comp, int start, int length, const char* rest, LangTokenType type)
{
	if (comp->current - comp->start == start + length &&
		memcpy(&comp->start + start, rest, length) == 0)
	{
		return type;
	}

	return LangTokenType::token_identifier;
}


LangToken LangCompiler::makeIdentifier(LangCompiler* comp)
{
	while (LangCompiler::isLetter(LangCompiler::peek(comp)) ||
		LangCompiler::isDigit(LangCompiler::peek(comp)))
	{
		LangCompiler::advance(comp);
	}

	return LangCompiler::makeToken(comp, LangCompiler::identifierType(comp));
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

	if (LangCompiler::isDigit(c)) return LangCompiler::makeNumber(comp);

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