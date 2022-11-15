#pragma once

#include "CommandForth.h"

class PrintString : public CommandForth {
	//Prints the given string
	void Operation(std::stack<int>&, std::deque<std::string>& instruction) override;
};

CommandForth* CreatePrintString();