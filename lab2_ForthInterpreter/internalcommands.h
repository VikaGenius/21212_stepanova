#pragma once

#include "CommandForth.h"

class InternalCommands : public CommandForth {

	//Commands working with stack
	//dup - copy the top of the stack and put it on the stack
	//drop - remove the top number from the stack
	//. - print the top number on the stack, remove from the stack
	//swap - swap the top and second numbers on the stack
    //rot - cyclically shift the top three numbers
    //over - copy the second number and put a copy over the top one
	//emit - print the top number on the stack as an ascii code and remove it from the stack
	//cr - line break
	void Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) override;

};

std::unique_ptr<CommandForth> CreateInternalCommands();
