#pragma once
#include <stack>
#include <string>
#include <memory>

class CommandForth {
public:
	//virtual void Operation() = 0;
	virtual void Operation(const std::string& oper, std::stack <int>& stack1) = 0;
	//std::stack <int> stack1; 
};
