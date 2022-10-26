#include "printstring.h"

#include <iostream>



void PrintString::Operation(const std::string& oper, std::stack<int>& stack1) {
	std::cout << oper;
}

CommandForth* CreatePrintString() {
	return new PrintString;
}