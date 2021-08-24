#include "lang_value.h"

void LangValueArray::writeValueArray(LangValueArray* a, LangValue v)
{
	a->values.push_back(v);
}


void LangValueArray::freeValueArray(LangValueArray* a)
{
	a->values.clear();
	a->values.resize(0);
}


LangValue LangValueArray::getValue(LangValueArray* a, int index)
{
	if (a->values.size() == 0 || a->values.size() <= index)
	{
		throw std::runtime_error("Index out of range");
	}

	return a->values.at(index);
}