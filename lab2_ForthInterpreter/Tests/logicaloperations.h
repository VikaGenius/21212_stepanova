#pragma once

#include "CommandForth.h"

class LogicalOperation : public CommandForth {
	//Boolean operations (>, <, =)
	void Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) override;
};

CommandForth* CreateLogicalOperation();

