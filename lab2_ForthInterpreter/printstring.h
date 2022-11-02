#pragma once

#include "CommandForth.h"

class PrintString : public CommandForth {
	//Prints the given string
	void Operation(std::stack<int>& stack1, std::deque<std::string>& instruction) override;
};

std::unique_ptr<CommandForth> CreatePrintString();