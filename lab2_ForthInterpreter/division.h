#pragma once

#include "CommandForth.h"

class OperationDivision : public CommandForth {

	//Performs a division operation or takes the remainder of a division
	void Operation(ExecutionContext& context) override;
};

CommandForth* CreateOperationDivision();
