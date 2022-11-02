#pragma once

#include "CommandForth.h"

class DoLoop: public CommandForth {

	//Handles the action loop
	void Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) override;
};

std::unique_ptr<CommandForth> CreateDoLoop();

