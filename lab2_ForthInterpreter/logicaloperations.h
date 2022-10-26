#pragma once

#include "CommandForth.h"

class LogicalOperation : public CommandForth {
	//Boolean operations (>, <, =)
	void Operation(const std::string& oper, std::stack <int>& stack1) override;
};

CommandForth* CreateLogicalOperation();

