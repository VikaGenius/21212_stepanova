#include "ifoperator.h"

#include <stdexcept>
#include <sstream>

void OperatorIf::Operation(ExecutionContext& context) {
	if (context.StackIsEmpty()) {
		throw std::invalid_argument("Error: stack is empty");
	}
	context.InstructionPopFront();

	int countIf = 0;
	std::stack<std::string> stackIf;
	if (context.StackTop() == 0) {
		while (context.InstructionSize() > 0) {
			if (context.InstructionFront() == "if") {
				countIf++;
			}
			if (context.InstructionFront() == "else" && countIf == 0) {
				context.InstructionPopFront();
				int isPush = 1;
				AfterElse(context, countIf, stackIf, isPush);
				Push(context, stackIf);
				return;
			} 
			if (context.InstructionFront() == "then") {
				int isPush = 0;
				if (Then(context, countIf, stackIf, isPush) == 0) {
					Push(context, stackIf);
					return;
				}
			}
			context.InstructionPopFront();
			if (context.InstructionIsEmpty()) {
				context.ReadLine();
			}
		}
	}
	else {
		while (context.InstructionSize() > 0) {
			if (context.InstructionFront() == "if") {
				countIf++;
			}
			if (context.InstructionFront() == "else" && countIf == 0) {
				context.InstructionPopFront();
				int isPush = 0;
				AfterElse(context, countIf, stackIf, isPush);
				Push(context, stackIf);
				return;
			}
			if (context.InstructionFront() == "then") {
				int isPush = 1;
				if (Then(context, countIf, stackIf, isPush) == 0) {
					Push(context, stackIf);
					return;
				}
			}
			stackIf.push(context.InstructionFront());
			context.InstructionPopFront();

			if (context.InstructionIsEmpty()) {
				context.ReadLine();
			}
		}
	}
	throw std::invalid_argument("Error: unknown command");
}

CommandForth* CreateOperatorIf() {
	return new OperatorIf;
}

void AfterElse(ExecutionContext& context, int countIf, std::stack<std::string>& stackIf, int isPush) {
	while (!context.InstructionIsEmpty()) {
		if (context.InstructionFront() == "if") {
			countIf++;
		}
		if (context.InstructionFront() == "then") {
			if (Then(context, countIf, stackIf, isPush) == 0) {
				return;
			}
		}
		if (isPush == 1) {
			stackIf.push(context.InstructionFront());
		}
		context.InstructionPopFront();

		if (context.InstructionIsEmpty()) {
			context.ReadLine();
		}
	}
}

int Then (ExecutionContext& context, int& countIf, std::stack<std::string>& stackIf, int isPush) {
	context.InstructionPopFront(); 
	if (!context.InstructionIsEmpty() && context.InstructionFront() == ";") {
		if (countIf == 0) {
			context.InstructionPopFront(); 
			return 0;
		}
		else {
			if (isPush == 1) {
				stackIf.push("then");
			}
			countIf--;
		}
	}
	else {
		throw std::invalid_argument("Error: unknown command");
	}
	return 1;
}

void Push (ExecutionContext& context, std::stack<std::string>& stackIf) {
	while (!stackIf.empty()) {
		context.InstructionPushFront(stackIf.top());
		stackIf.pop();
	}
}







