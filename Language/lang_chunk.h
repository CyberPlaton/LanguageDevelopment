#pragma once

#include "lang_common.h"
#include "lang_value.h"

using byte = uint8_t;


enum LangOpCode : byte
{
	op_add,
	op_subtract,
	op_multiply,
	op_divide,
	op_constant,
	op_negate,
	op_return,
};


struct LangChunk
{
	/*
	* Add a byte to a chunk.
	* 
	* TODO Inform user when we run out of memory and then exit program.
	* 
	* 
	* OpCode Format.
	* 
	* [op_return] -- [-/-]
	* [op_constant] -- [number], where number specifies the index of the value in constants.values array.
	*/
	static void writeChunk(LangChunk* c, byte b, int line);



	/*
	* Free memory for the chunk.
	* The storage for code and constants still will take 64 Bytes.
	*/
	static void freeChunk(LangChunk* c);


	/*
	* Add a value to constants vector, where value is some decimal number.
	* Returns the index where the value is located in the vector.
	*/
	static int addConstant(LangChunk* c, LangValue v);


	LangValueArray constants;
	std::vector<byte> code;
	std::vector<int> lines;
};