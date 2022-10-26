#pragma once

#include "CommandForth.h"

class PrintString : public CommandForth {
	//Prints the given string
	void Operation(const std::string& oper, std::stack<int>& stack1) override;
};

CommandForth* CreatePrintString();