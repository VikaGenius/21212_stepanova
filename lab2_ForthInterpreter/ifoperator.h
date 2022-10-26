#pragma once

#include "CommandForth.h"

class OperatorIf : public CommandForth {
	void Operation(const std::string& oper, std::stack<int>& stack1) override;
	void Operation1(std::string& str, std::stack<int>& stack1);
};
