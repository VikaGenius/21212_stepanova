#include "internalcommands.h"

#include <stdexcept>
#include <fstream>

void InternalCommands::Operation(ExecutionContext& context) {
	const std::string oper = context.InstructionFront();
	context.InstructionPopFront();
	//std::ofstream out;          // поток для записи
    //out.open("out.txt");

	if (oper == "cr") {
		context.PrintLine() << std::endl;
		return;
	}

	IsEmpty(context);
	
	if (oper == "drop") {
		context.StackPop();
		return;
	}
	
	int top = context.StackTop();
	if (oper == "dup") {
		context.StackPush(top);
		return;
	}
	if (oper == ".") {
		context.PrintLine() << top;
		context.StackPop();
		return;
	}
	if (oper == "emit") {
		context.PrintLine() << (char)top; //проверить
		context.StackPop();
		return;
	}
	if (oper == "swap") {
		context.StackPop();
		IsEmpty(context);
		int second = context.StackTop();
		context.StackPop();
		context.StackPush(top);
		context.StackPush(second);
		return;	
	}
	if (oper == "over") {
		context.StackPop();
		IsEmpty(context);
		int second = context.StackTop();
		context.StackPush(top);
		context.StackPush(second);
		return;
	}
	if (oper == "rot") {
		context.StackPop();
		IsEmpty(context);
		int second = context.StackTop();
		context.StackPop();
		IsEmpty(context);
		int third = context.StackTop();
		context.StackPop();
		context.StackPush(top);
		context.StackPush(third);
		context.StackPush(second);
	}
}

CommandForth* CreateInternalCommands() {
	return  new InternalCommands;
}

void IsEmpty(ExecutionContext& context) {
	if (context.StackIsEmpty()) {
			throw std::invalid_argument("Error: not enough numbers to complete the operation");
		}
}