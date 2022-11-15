#include "doloop.h"

#include <vector>
#include <stdexcept>

void DoLoop::Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) {
	instruction.pop_front();

	std::vector<std::string> cycle;
	size_t index = 0;

	while (index < instruction.size() && instruction[index] != "loop") {
		cycle.push_back(instruction[index]);
		index++;
	}
	if (index + 1 != instruction.size() && instruction[index] == "loop" && instruction[index + 1] == ";") {
		instruction.erase(instruction.begin() + index);
		instruction.erase(instruction.begin() + index);
	}
	else {
		throw std::invalid_argument("Error: unknown command");
	}
	
	if (stack1.size() < 2) {
		throw std::invalid_argument("Error: unknown command");
	}

	int i = stack1.top();
	stack1.pop();
	int end = stack1.top();
	stack1.pop();

	if (end < i) {
		throw std::invalid_argument("Error: unknown command");
	}

	while (i < end - 1) {
		for (int j = cycle.size() - 1; j >= 0; j--) {
			instruction.push_front(cycle[j]);
		}
		i++;
	}
}

CommandForth* CreateDoLoop() {
	return new DoLoop;
}
