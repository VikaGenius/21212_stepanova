#include "logicaloperations.h"

#include <stdexcept>

void LogicalOperation::Operation(ExecutionContext& context) {
	const std::string oper = context.InstructionFront();
	context.InstructionPopFront();
	if (context.StackSize() > 1) {
		int a = context.StackTop();
		context.StackPop();
		int b = context.StackTop();
		context.StackPop();
		if (oper == "<") {
			if (b < a) context.StackPush(1);
			else context.StackPush(0);
			return;
		}
		if (oper == ">") {
			if (b > a) context.StackPush(1);
			else context.StackPush(0);
			return;
		}
		if (oper == "=") {
			if (b == a) context.StackPush(1);
			else context.StackPush(0);
			return;
		}
	}
	if (!context.StackIsEmpty()) {
		context.StackPop();
	}
	throw std::invalid_argument("Error: not enough numbers to complete the operation");
}

CommandForth* CreateLogicalOperation() {
	return new LogicalOperation;
}
