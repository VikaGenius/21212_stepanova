#pragma once

#include "CommandForth.h"

class ArithmeticOperation : public CommandForth {

	//Performs an addition, subtraction, or multiplication operation
	void Operation(ExecutionContext& context) override;
};

CommandForth* CreateArithmeticOperation();
void IsOverflow (long long resultOperation);
