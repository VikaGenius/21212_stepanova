#pragma once

#include "Factory.h"
#include "CommandForth.h"

#include <stack>

//
void Registration(Factory<CommandForth, std::string, CommandForth*(*)()>& factory);

//
bool IsNumber(const std::string& str);

//
void Parser(Factory<CommandForth, std::string, CommandForth*(*)()>& factory, std::stack<int>& stack1, std::deque<std::string>& instruction);

//
void Executor(int isFile, std::stack<int>& stack1, std::string& file);


