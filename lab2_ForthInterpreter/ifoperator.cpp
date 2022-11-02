#include "ifoperator.h"

#include <stdexcept>

void OperatorIf::Operation(std::stack<int>& stack1, std::deque<std::string>& instruction) {
	if (stack1.empty()) {
		throw std::invalid_argument("Error: stack is empty");
	}
	instruction.pop_front();
	if (stack1.top() != 0) { //���� ������� ����� �� ����� 0
		int countIf = 0; // ������� ��������� if
		for (size_t i = 0; i < instruction.size(); i++) {
			if (instruction[i] == "if") {
				countIf++;
			}
			if (instruction[i] == "then") {
				if (instruction[i + 1] == ";") {
					if (countIf == 0) { // ����� if, ������� ����� � ��� �������. ��� ���������� else ������ ������� then ;
						instruction.erase(instruction.begin() + i);
						instruction.erase(instruction.begin() + i);
						return;
					}
					countIf--;
					
				}
				else {
					throw std::invalid_argument("Error: unknown command");
				}
			}
			if (instruction[i] == "else") {
				if (countIf == 0) { //else ��������� if. �� ������� ����� �� ����� 0, �������� ���������� "else"
					while (i < instruction.size() && instruction[i] != "then") {
						instruction.erase(instruction.begin() + i);
						i++;
					}
					if (instruction[i] == "then" && instruction[i + 1] == ";") {
						instruction.erase(instruction.begin() + i);
						instruction.erase(instruction.begin() + i);
						return;
					}
					throw std::invalid_argument("Error: unknown command");

				}
			}
		}
	}
	else { //������� ����� ����� 0
		int countIf = 0; // ������� ��������� if
		int index = 0;
		while (!instruction.empty()) {
			if (instruction[index] == "else" && countIf == 0) { //��������� else ������ if, �������� else � then ;
				instruction.pop_front();
				size_t size = instruction.size();
				while (index < size && instruction[index] != "then") {
					index++;
				}
				if (instruction[index] == "then" && instruction[index + 1] == ";") {
					instruction.erase(instruction.begin() + index);
					instruction.erase(instruction.begin() + index);
					return;
				}
				throw std::invalid_argument("Error: unknown command");
			}
			if (instruction[index] == "then" && countIf == 0) { // ��������� then ������ if, �������� then ;
				if (instruction[index + 1] == ";") {
					instruction.pop_front();
					instruction.pop_front();
					return;
				}
				throw std::invalid_argument("Error: unknown command");
			}
			instruction.pop_front(); // �������� �� else (� ������ ���������� - �� then)
		}
	}
	throw std::invalid_argument("Error: unknown command"); //����� �� ����� ������ � �� ���������� then ;
}

std::unique_ptr<CommandForth> CreateOperatorIf() {
	return std::unique_ptr<CommandForth>(new OperatorIf);
}




