
#include "executioncontext.h"

#include <algorithm>
#include <sstream>

void ExecutionContext::StackPush(int a) {
    stack1.push(a);
}

void ExecutionContext::StackPop() {
    stack1.pop();
}

int ExecutionContext::StackTop() {
    return stack1.top();   
}

size_t ExecutionContext::StackSize() {
    return stack1.size();   
}

bool ExecutionContext::StackIsEmpty() {
    return stack1.empty();
}

void ExecutionContext::InstructionPushBack(const std::string& a) {
    instruction.push_back(a);
}

void ExecutionContext::InstructionPushFront(const std::string& a) {
    instruction.push_front(a);
}

void ExecutionContext::InstructionPopFront() {
    instruction.pop_front();
}

std::string ExecutionContext::InstructionFront() {
    return instruction.front();
}

bool ExecutionContext::InstructionIsEmpty() {
    return instruction.empty();
}

size_t ExecutionContext::InstructionSize(){
    return instruction.size();
}

std::ostream& ExecutionContext::PrintLine() {
    return output;
}

void ExecutionContext::ReadLine() { 
	std::string str, word;
    std::stringstream stream;
	if (std::getline(input, str)) {
		stream << str;
   		while (stream >> word) {
        	instruction.push_back(word);
    	}
	}
}

