#include "division.h"

#include <iostream>
#include <stdexcept>

void OperationDivision::Operation(ExecutionContext& context) {
	const std::string oper = context.InstructionFront();
	context.InstructionPopFront();
	if (context.StackSize() > 1) {
		int a = context.StackTop();
		context.StackPop();
		int b = context.StackTop();
		context.StackPop();
		if (a == 0) {
			throw std::invalid_argument("Error: division by zero");
		}
		if (oper == "/") {
			context.StackPush(b / a);
			return;
		}
		if (oper == "mod") {
			context.StackPush(b % a);
			return;
		}
	}
	if (!context.StackIsEmpty()) {
		context.StackPop();
	}
	throw std::invalid_argument("Error: not enough numbers to complete the operation");
}

CommandForth* CreateOperationDivision() {
	return new OperationDivision;
}