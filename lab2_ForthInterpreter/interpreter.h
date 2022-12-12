#pragma once

#include "executioncontext.h"
#include "Factory.h"
#include "CommandForth.h"

class Interpreter {
public:
Interpreter(std::istream& in = std::cin, std::ostream& out = std::cout): input(in), output(out), context(in, out) {}
~Interpreter() = default;

//Registration Forth`s commands
void Registration();

//
bool IsNumber(const std::string& str);

//
void Parser();

//
void Executor();

private:
std::istream& input;
std::ostream& output;
ExecutionContext context;
Factory<CommandForth, std::string, CommandForth*(*)()> factory;
};