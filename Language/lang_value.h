#pragma once

#include "lang_common.h"

using LangValue = double;

struct LangValueArray
{
	/*
	* Push a value in the storage.
	*/
	static void writeValueArray(LangValueArray* a, LangValue v);


	/*
	* Free memory and reset vector of values.
	*/
	static void freeValueArray(LangValueArray* a);


	/*
	* Returns the value at given index.
	*/
	static LangValue getValue(LangValueArray* a, int index);



	std::vector<LangValue> values;
};