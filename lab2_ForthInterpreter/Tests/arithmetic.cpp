#include "arithmetic.h"

#include <stdexcept>
#include <iostream>
#include <limits.h>

void ArithmeticOperation::Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) {
	const std::string oper = instruction.front();
	instruction.pop_front();
	if (stack1.size() > 1) {
		int a = stack1.top();
		stack1.pop();
		int b = stack1.top();
		stack1.pop();
		long long resultOperation;
		if (oper == "+") {
			resultOperation = static_cast<long long>(b) + static_cast<long long>(a);
			IsOverflow(resultOperation);
			stack1.push(b + a);
			return;
		}
		if (oper == "-") {
			resultOperation = static_cast<long long>(b) - static_cast<long long>(a);
			IsOverflow(resultOperation);
			stack1.push(b - a);
			return;
		}
		if (oper == "*") {
			resultOperation = static_cast<long long>(b) * static_cast<long long>(a);
			IsOverflow(resultOperation);
			stack1.push(b * a);
			return;
		}
	}
	if (!stack1.empty()) {
		stack1.pop();
	}
	throw std::invalid_argument("Error: not enough numbers to complete the operation");

}

CommandForth* CreateArithmeticOperation() {
	return new ArithmeticOperation;
}

void IsOverflow (long long resultOperation) {
	if (std::abs(resultOperation) > INT_MAX) {
			throw std::invalid_argument("Error: integer type overflow");
	}
}

