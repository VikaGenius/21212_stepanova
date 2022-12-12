/*#pragma once

#include "Factory.h"
#include "CommandForth.h"

#include <stack>
#include <iostream>

//
void Registration(Factory<CommandForth, std::string, CommandForth*(*)()>& factory);

//
bool IsNumber(const std::string& str);

//
void Parser(Factory<CommandForth, std::string, CommandForth*(*)()>& factory, std::stack<int>& stack1, std::deque<std::string>& instruction, std::istream& input, std::ostream& output);

//
void Executor(std::stack<int>& stack1, std::istream& input = std::cin, std::ostream& output = std::cout);*/


