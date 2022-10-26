#include "logicaloperations.h"

#include <stdexcept>

//void LogicalOperation::Operation() {}

void LogicalOperation::Operation(const std::string& oper, std::stack <int>& stack1) {
	if (stack1.size() > 1) {
		int a = stack1.top();
		stack1.pop();
		int b = stack1.top();
		stack1.pop();
		if (oper == "<") {
			if (b < a) stack1.push(1);
			else stack1.push(0);
			return;
		}
		if (oper == ">") {
			if (b > a) stack1.push(1);
			else stack1.push(0);
			return;
		}
		if (oper == "=") {
			if (b == a) stack1.push(1);
			else stack1.push(0);
			return;
		}
	}
	if (!stack1.empty()) {
		stack1.pop();
	}
	throw std::invalid_argument("Error: not enough numbers to complete the operation");
}

CommandForth* CreateLogicalOperation() {
	return new LogicalOperation;
}
