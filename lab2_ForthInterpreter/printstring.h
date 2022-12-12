#pragma once

#include "CommandForth.h"

class PrintString : public CommandForth {
	//Prints the given string
	void Operation(ExecutionContext& context) override;
};

CommandForth* CreatePrintString();