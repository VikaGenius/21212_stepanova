#include "printstring.h"

#include <stdexcept>
#include <fstream>
#include <queue>

void PrintString::Operation(ExecutionContext& context) {
	context.InstructionPopFront();
	std::queue<std::string> str;
	std::string word;
	//std::ofstream out;          // поток для записи
    //out.open("out.txt");
	while (context.InstructionSize() > 0) {
		word = context.InstructionFront();
		if (word[word.size() - 1] == '"') {
			word.pop_back();
			str.push(word);
			context.InstructionPopFront();
			while (!str.empty()) {
				context.PrintLine() << str.front() << " ";
				str.pop();
			}
			context.PrintLine() << std::endl;
			return;
		}
		str.push(word);
		//output << instruction.front();
		context.InstructionPopFront();
	}
	throw std::invalid_argument("Error: unknown command");
}

CommandForth* CreatePrintString() {
	return new PrintString;
}