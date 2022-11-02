#include "printstring.h"

#include <iostream>
#include <stdexcept>



void PrintString::Operation(std::stack<int>& stack1, std::deque<std::string>& instruction) {
	instruction.pop_front();
	while (instruction.front() != "\"") {
		std::cout << instruction.front();
		instruction.pop_front();
	}
	if (!instruction.empty() && instruction.front() == "\"") {
		instruction.pop_front();
		std::cout << std::endl;
		return;
	}
	throw std::invalid_argument("Error: unknown command");
}

std::unique_ptr<CommandForth> CreatePrintString() {
	return std::unique_ptr<CommandForth>(new PrintString);
}