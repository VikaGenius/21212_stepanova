#pragma once

#include "CommandForth.h"

class LogicalOperation : public CommandForth {
	//Boolean operations (>, <, =)
	void Operation(ExecutionContext& context) override;
};

CommandForth* CreateLogicalOperation();

