#include "internalcommands.h"

#include <stdexcept>
#include <iostream>

void InternalCommands::Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) {
	const std::string oper = instruction.front();
	instruction.pop_front();
	if (stack1.empty()) {
		throw std::invalid_argument("Error: stack is empty");
	}
	if (oper == "drop") {
		stack1.pop();
		return;
	}
	if (oper == "cr") {
		std::cout << std::endl;
		return;
	}

	int top = stack1.top();
	if (oper == "dup") {
		stack1.push(top);
		return;
	}
	if (oper == ".") {
		std::cout << top;
		stack1.pop();
		return;
	}
	if (oper == "emit") {
		std::cout << (char)top;
		stack1.pop();
		return;
	}
	if (oper == "swap") {
		stack1.pop();
		int second = stack1.top();
		stack1.pop();
		stack1.push(second);
		stack1.push(top);
		return;	
	}
	if (oper == "over") {
		stack1.pop();
		int second = stack1.top();
		stack1.push(top);
		stack1.push(second);
		return;
	}
	if (oper == "rot") {
		stack1.pop();
		int second = stack1.top();
		stack1.pop();
		int third = stack1.top();
		stack1.pop();
		stack1.push(top);
		stack1.push(third);
		stack1.push(second);
	}

}

std::unique_ptr<CommandForth> CreateInternalCommands() {
	return  std::make_unique<CommandForth>(new InternalCommands);
}