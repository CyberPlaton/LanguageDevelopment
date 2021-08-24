#pragma once

#include "lang_chunk.h"

class Application;

struct LangDebugger
{
	/*
	* Disassembling a chunk and printing it to console.
	*/
	static void disassembleChunk(LangChunk* c, const std::string& name);


	/*
	* Disassembling a chunk and printing to the application console.
	*/
	static void disassembleChunk(LangChunk* c, const std::string& name, Application* app);
};