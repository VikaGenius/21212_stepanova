#pragma once

#include <iostream>
#include <deque>
#include <stack>

class ExecutionContext {
public:
ExecutionContext(std::istream& in = std::cin, std::ostream& out = std::cout): input(in), output(out) {}
~ExecutionContext() = default;

//read next line of programm
void ReadLine();

//
std::ostream& PrintLine();

//operation with stack
void StackPush(int a);
void StackPop();
int StackTop();
bool StackIsEmpty();
size_t StackSize();

//operation with instruction
void InstructionPushBack(const std::string& a);
void InstructionPushFront(const std::string& a);
void InstructionPopFront();
std::string InstructionFront();
bool InstructionIsEmpty();
size_t InstructionSize();

private:
    std::stack<int> stack1;
    std::istream& input;
    std::ostream& output;
    std::deque<std::string> instruction;
};
