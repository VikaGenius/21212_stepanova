#include "arithmetic.h"

#include <stdexcept>
#include <iostream>
#include <limits.h>

void ArithmeticOperation::Operation(ExecutionContext& context) {
	const std::string oper = context.InstructionFront();
	context.InstructionPopFront();
	if (context.StackSize() > 1) {
		int a = context.StackTop();
		context.StackPop();
		int b = context.StackTop();
		context.StackPop();
		long long resultOperation;
		if (oper == "+") {
			resultOperation = static_cast<long long>(b) + static_cast<long long>(a);
			IsOverflow(resultOperation);
			context.StackPush(b + a);
			return;
		}
		if (oper == "-") {
			resultOperation = static_cast<long long>(b) - static_cast<long long>(a);
			IsOverflow(resultOperation);
			context.StackPush(b - a);
			return;
		}
		if (oper == "*") {
			resultOperation = static_cast<long long>(b) * static_cast<long long>(a);
			IsOverflow(resultOperation);
			context.StackPush(b * a);
			return;
		}
	}
	if (!context.StackIsEmpty()) {
		context.StackPop();
	}
	throw std::invalid_argument("Error: not enough numbers to complete the operation");

}

CommandForth* CreateArithmeticOperation() {
	return new ArithmeticOperation;
}

void IsOverflow (long long resultOperation) {
	if (resultOperation > INT_MAX || resultOperation < INT_MIN) { 
			throw std::invalid_argument("Error: integer type overflow");
	}
}

