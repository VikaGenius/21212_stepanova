#pragma once

#include "CommandForth.h"

class OperationDivision : public CommandForth {

	//Performs a division operation or takes the remainder of a division
	void Operation(const std::string& oper, std::stack <int>& stack1) override;
};

CommandForth* CreateOperationDivision();
