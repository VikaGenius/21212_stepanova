#pragma once

#include "CommandForth.h"

#include <iostream>

class DoLoop: public CommandForth {

	//Handles the action loop
	void Operation(ExecutionContext& context) override;
};

CommandForth* CreateDoLoop();

void PushCycle(ExecutionContext& context, std::vector<std::string>& cycle);
