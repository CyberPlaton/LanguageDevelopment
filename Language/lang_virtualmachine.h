#pragma once

#include "lang_chunk.h"

enum LangInterpretResult : byte
{
	interpret_ok,
	interpret_compile_error,
	interpret_runtime_error
};


struct LangVM
{
	static LangInterpretResult interpret(LangVM* vm, LangChunk* c);
	static LangInterpretResult run(LangVM* vm);
	static bool initVM(LangVM* vm);
	static void freeVM(LangVM* vm);

	static void pushValue(LangVM* vm, LangValue v);
	static LangValue popValue(LangVM* vm);



	/*
	* Tiny Helpers.
	*/
	static byte readByte(LangVM* vm);
	static LangValue readConstant(LangVM* vm);
	static void showStackTop(LangVM* vm);

	static void binaryAdd(LangVM* vm);
	static void binarySubtract(LangVM* vm);
	static void binaryMultiply(LangVM* vm);
	static void binaryDivide(LangVM* vm);



	LangChunk* chunk = nullptr;
	byte* instruction_pointer = nullptr; // Keeps track of the current about to be executed instr.

	std::stack<LangValue> stack;
};