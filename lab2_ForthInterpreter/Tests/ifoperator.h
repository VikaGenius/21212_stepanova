#pragma once

#include "CommandForth.h"

class OperatorIf : public CommandForth {
	void Operation(std::stack<int>& stack1, std::deque<std::string>& instruction) override;
};

CommandForth* CreateOperatorIf();
