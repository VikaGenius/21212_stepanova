#pragma once

#include "doloop.h"

#include <vector>
#include <stdexcept>



void DoLoop::Operation(std::stack <int>& stack1, std::deque<std::string>& instruction) {
	instruction.pop_front();

	std::vector<std::string> cycle;
	size_t index = 0;

	while (index < instruction.size() && instruction[index] != "loop") {
		cycle.push_back(instruction[index]);
	}
	if (instruction[index] == "loop") {
		if (index + 1 != instruction.size() && instruction[index + 1] == ";") {
			instruction.erase(instruction.begin() + index);
			instruction.erase(instruction.begin() + index);
		}
		else {
			throw std::invalid_argument("Error: unknown command");
		}
	}
	int i = stack1.top();
	stack1.pop();
	int end = stack1.top();
	stack1.pop();
	for (i; i < end - 1; i++) {
		for (size_t j = cycle.size() - 1; j >= 0; j--) {
			instruction.push_front(cycle[j]);
		}
	}
}

std::unique_ptr<CommandForth> CreateDoLoop() {
	return std::unique_ptr<CommandForth>(new DoLoop);
}
