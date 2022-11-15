#include "printstring.h"

#include <stdexcept>
#include <fstream>



void PrintString::Operation(std::stack<int>&, std::deque<std::string>& instruction) {
	instruction.pop_front();
	std::ofstream out;          // поток для записи
    out.open("out.txt");
	while (instruction.size() > 0 && instruction.front() != "\"") {
		out << instruction.front();
		instruction.pop_front();
	}
	if (!instruction.empty() && instruction.front() == "\"") {
		instruction.pop_front();
		out << std::endl;
		return;
	}
	throw std::invalid_argument("Error: unknown command");
}

CommandForth* CreatePrintString() {
	return new PrintString;
}