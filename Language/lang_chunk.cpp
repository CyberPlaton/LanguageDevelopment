#include "lang_chunk.h"

void LangChunk::writeChunk(LangChunk* c, byte b, int line)
{
	c->code.push_back(b);
	c->lines.push_back(line);
}


void LangChunk::freeChunk(LangChunk* c)
{
	c->code.clear();
	c->code.resize(0);
}

int LangChunk::addConstant(LangChunk* c, LangValue v)
{
	c->constants.writeValueArray(&c->constants, v);
	return c->constants.values.size() - 1;
}