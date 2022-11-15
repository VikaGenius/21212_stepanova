#include "internalcommands.h"

#include <stdexcept>
#include <fstream>

void InternalCommands::Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) {
	const std::string oper = instruction.front();
	instruction.pop_front();
	std::ofstream out;          // поток для записи
    out.open("out.txt");

	if (oper == "cr") {
		out << std::endl;
		return;
	}

	IsEmpty(stack1);
	
	if (oper == "drop") {
		stack1.pop();
		return;
	}
	
	int top = stack1.top();
	if (oper == "dup") {
		stack1.push(top);
		return;
	}
	if (oper == ".") {
		out << top;
		stack1.pop();
		return;
	}
	if (oper == "emit") {
		out << (char)top;
		stack1.pop();
		return;
	}
	if (oper == "swap") {
		stack1.pop();
		IsEmpty(stack1);
		int second = stack1.top();
		stack1.pop();
		stack1.push(top);
		stack1.push(second);
		return;	
	}
	if (oper == "over") {
		stack1.pop();
		IsEmpty(stack1);
		int second = stack1.top();
		stack1.push(top);
		stack1.push(second);
		return;
	}
	if (oper == "rot") {
		stack1.pop();
		IsEmpty(stack1);
		int second = stack1.top();
		stack1.pop();
		IsEmpty(stack1);
		int third = stack1.top();
		stack1.pop();
		stack1.push(top);
		stack1.push(third);
		stack1.push(second);
	}
}

CommandForth* CreateInternalCommands() {
	return  new InternalCommands;
}

void IsEmpty(std::stack<int> stack1) {
	if (stack1.empty()) {
			throw std::invalid_argument("Error: not enough numbers to complete the operation");
		}
}