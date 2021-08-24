#include "lang_debug.h"

static int simpleInstruction(const std::string& name, int offset)
{
	printf("[OpCode]%s\n", name.c_str());
	return offset + 1;
}

static int constantInstruction(const std::string& name, LangChunk* c, int offset)
{
	byte constant_index = c->code[offset + 1];

	printf("[OpCode]%-16s %4d \"", name.c_str(), constant_index);

	printf("%.4f", c->constants.values[constant_index]);

	printf("\" \n");

	return offset + 1;
}


static int disassembleInstruction(LangChunk* c, int offset)
{
	printf("[Offset]%04d ", offset);
	
	if (offset > 0 && c->lines[offset] == c->lines[offset - 1])
	{
		printf("    |");
	}
	else
	{
		printf("[Ln]%4d ", c->lines[offset]);
	}

	byte instr = c->code[offset];
	switch (instr)
	{
	case LangOpCode::op_constant:
		return constantInstruction("op_constant", c, offset);


	case LangOpCode::op_negate:
		return simpleInstruction("op_negate", offset);


	case LangOpCode::op_return:
		return simpleInstruction("op_return", offset);

	case LangOpCode::op_add:
		return simpleInstruction("op_add", offset);

	case LangOpCode::op_subtract:
		return simpleInstruction("op_subtract", offset);

	case LangOpCode::op_multiply:
		return simpleInstruction("op_multiply", offset);

	case LangOpCode::op_divide:
		return simpleInstruction("op_divide", offset);

	default:
		break;
	}


}



void LangDebugger::disassembleChunk(LangChunk* c, const std::string& name)
{
	using namespace std;

	cout << "Chunk		\""<< name << "\"" << endl;

	for (int i = 0; i < c->code.size(); i++)
	{
		i = disassembleInstruction(c, i);
	}

	cout << endl;
	cout << endl;
}