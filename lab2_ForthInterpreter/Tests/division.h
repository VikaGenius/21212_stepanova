#pragma once

#include "CommandForth.h"

class OperationDivision : public CommandForth {

	//Performs a division operation or takes the remainder of a division
	void Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) override;
};

CommandForth* CreateOperationDivision();
