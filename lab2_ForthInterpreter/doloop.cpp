#include "doloop.h"

#include <vector>
#include <stdexcept>
#include <sstream>

void DoLoop::Operation(ExecutionContext& context) {
	context.InstructionPopFront();

	std::vector<std::string> cycle;
	int countDo = 0;
	while (context.InstructionSize() > 0) {
		if (context.InstructionFront() == "do") {
			countDo++;
		}
		if (context.InstructionFront() == "loop" && countDo != 0) {
			countDo--;
		}
		else if (context.InstructionFront() == "loop" && countDo == 0) {
			if (context.InstructionSize() > 1) {
				context.InstructionPopFront();
				if (context.InstructionFront() == ";") {
					context.InstructionPopFront();
					PushCycle(context, cycle);
					return;
				}
				else {
					throw std::invalid_argument("Error: unknown command");
				}
			}
			else {
				throw std::invalid_argument("Error: unknown command");
			}
		}
		cycle.push_back(context.InstructionFront());
		context.InstructionPopFront();
		if (context.InstructionSize() == 0) {
			context.ReadLine();
		}
	}
	throw std::invalid_argument("Error: unknown command");
}

CommandForth* CreateDoLoop() {
	return new DoLoop;
}

void PushCycle(ExecutionContext& context, std::vector<std::string>& cycle) {
	if (context.StackSize() < 2) {
		throw std::invalid_argument("Error: Not enough numbers on the stack");
	}

	int i = context.StackTop();
	context.StackPop();
	int end = context.StackTop();;
	context.StackPop();

	if (end < i) {
		throw std::invalid_argument("Error: unknown command");
	}

	while (i < end) { 
		for (int j = cycle.size() - 1; j >= 0; j--) {
			context.InstructionPushFront(cycle[j]);
		}
		i++;
	}
}
