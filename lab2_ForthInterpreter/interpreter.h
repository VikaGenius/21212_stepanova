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

// We check the words that came to the input. If an integer number, 
// we put it on the stack, otherwise we check if there is a word among 
// the language commands in the factory (if not, we throw an exception)
void Parser();

//Starts the language command registration function. Splits input lines and queues words, starts parser.
void Executor();

private:
std::istream& input;
std::ostream& output;
ExecutionContext context;
Factory<CommandForth, std::string, CommandForth*(*)()> factory;
};