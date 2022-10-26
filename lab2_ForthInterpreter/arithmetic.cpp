#include "arithmetic.h"

#include <stdexcept>
#include <iostream>


void ArithmeticOperation::Operation(const std::string& oper, std::stack <int>& stack1) {
	if (stack1.size() > 1) {
		int a = stack1.top();
		stack1.pop();
		int b = stack1.top();
		stack1.pop();
		if (oper == "+") {
			stack1.push(b + a);
			return;
		}
		if (oper == "-") {
			stack1.push(b - a);
			return;
		}
		if (oper == "*") {
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
