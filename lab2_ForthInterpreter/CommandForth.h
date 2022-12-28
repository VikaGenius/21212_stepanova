#pragma once

#include "executioncontext.h"

#include <stack>
#include <string>
#include <memory>
#include <queue>

class CommandForth {
public:

	virtual ~CommandForth() = default;
	virtual void Operation(ExecutionContext& context) = 0;
};
