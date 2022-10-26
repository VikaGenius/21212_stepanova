#pragma once

#include "CommandForth.h"

class ArithmeticOperation : public CommandForth {

	//Performs an addition, subtraction, or multiplication operation
	void Operation(const std::string& oper, std::stack <int>& stack1) override;
};

CommandForth* CreateArithmeticOperation();
