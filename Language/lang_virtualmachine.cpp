#include "lang_virtualmachine.h"


bool LangVM::initVM(LangVM* vm)
{
	while (!vm->stack.empty())
	{
		vm->stack.pop();
	}


	return true;
}


void LangVM::freeVM(LangVM* vm)
{

}


void LangVM::showStackTop(LangVM* vm)
{
	printf("Stack Top: %.4f \n", vm->stack.top());
}


void LangVM::pushValue(LangVM* vm, LangValue v)
{
	vm->stack.push(v);
}

LangValue LangVM::popValue(LangVM* vm)
{
	LangValue v = vm->stack.top();
	vm->stack.pop();
	return v;
}



LangInterpretResult LangVM::interpret(LangCompiler* comp, LangVM* vm, const std::string& source)
{
	LangChunk chunk;

	if (!LangCompiler::compile(comp, source.c_str(), &chunk))
	{
		LangChunk::freeChunk(&chunk);
		return LangInterpretResult::interpret_compile_error;
	}

	vm->chunk = &chunk;
	vm->instruction_pointer = &vm->chunk->code[0];


	LangInterpretResult result = LangVM::run(vm);


	LangChunk::freeChunk(&chunk);
	return result;
}


byte LangVM::readByte(LangVM* vm)
{
	return *(vm->instruction_pointer++);
}


LangValue LangVM::readConstant(LangVM* vm)
{
	return vm->chunk->constants.values[LangVM::readByte(vm)];
}



void LangVM::binaryAdd(LangVM* vm)
{
	LangValue b = LangVM::popValue(vm);
	LangValue a = LangVM::popValue(vm);
	LangVM::pushValue(vm, (a + b));
}


void LangVM::binarySubtract(LangVM* vm)
{
	LangValue b = LangVM::popValue(vm);
	LangValue a = LangVM::popValue(vm);
	LangVM::pushValue(vm, (a - b));
}


void LangVM::binaryMultiply(LangVM* vm)
{
	LangValue b = LangVM::popValue(vm);
	LangValue a = LangVM::popValue(vm);
	LangVM::pushValue(vm, (a * b));
}


void LangVM::binaryDivide(LangVM* vm)
{
	LangValue b = LangVM::popValue(vm);
	LangValue a = LangVM::popValue(vm);
	LangVM::pushValue(vm, (a / b));
}



LangInterpretResult LangVM::run(LangVM* vm)
{
	if (vm->chunk == nullptr || vm->instruction_pointer == nullptr)
	{
		return LangInterpretResult::interpret_compile_error;
	}


	LangValue c;


	while (true)
	{
		byte instr;
		instr = LangVM::readByte(vm);

		switch (instr)
		{
		case LangOpCode::op_return:
			return LangInterpretResult::interpret_ok;


		case LangOpCode::op_constant:
			c = LangVM::readConstant(vm);
			LangVM::pushValue(vm, c);
			break;


		case LangOpCode::op_negate:
			LangVM::pushValue(vm, -LangVM::popValue(vm));
			break;


		case LangOpCode::op_add:
			binaryAdd(vm);
			break;

		case LangOpCode::op_subtract:
			binarySubtract(vm);
			break;

		case LangOpCode::op_multiply:
			binaryMultiply(vm);
			break;

		case LangOpCode::op_divide:
			binaryDivide(vm);
			break;
		}
	}
}

#undef BINARY_OP
