#pragma once

#include "CommandForth.h"

#include <iostream>

class OperatorIf : public CommandForth {
	void Operation(ExecutionContext& context) override;
};

CommandForth* CreateOperatorIf();

void AfterElse(ExecutionContext& context, int countIf, std::stack<std::string>& stackIf, int isPush);

int Then (ExecutionContext& context, int& countIf, std::stack<std::string>& stackIf, int isPush);

void Push (ExecutionContext& context, std::stack<std::string>& stackIf);