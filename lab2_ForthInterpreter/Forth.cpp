// Forth.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Factory.h"
#include "arithmetic.h"
#include "division.h"
#include "internalcommands.h"
#include "logicaloperations.h"
#include "printstring.h"
#include "ifoperator.h"
#include "doloop.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <deque>
#include <memory>

void Registration(Factory<std::unique_ptr<CommandForth>, std::string, std::unique_ptr<CommandForth>(*)()>& factory) {
    factory.RegisterCommand("+", CreateArithmeticOperation);
    factory.RegisterCommand("-", CreateArithmeticOperation);
    factory.RegisterCommand("*", CreateArithmeticOperation);
    factory.RegisterCommand("/", CreateOperationDivision);
    factory.RegisterCommand("mod", CreateOperationDivision);
    factory.RegisterCommand(">", CreateLogicalOperation);
    factory.RegisterCommand("<", CreateLogicalOperation);
    factory.RegisterCommand("=", CreateLogicalOperation);
    factory.RegisterCommand("drop", CreateInternalCommands);
    factory.RegisterCommand("cr", CreateInternalCommands);
    factory.RegisterCommand("dup", CreateInternalCommands);
    factory.RegisterCommand(".", CreateInternalCommands);
    factory.RegisterCommand("emit", CreateInternalCommands);
    factory.RegisterCommand("swap", CreateInternalCommands);
    factory.RegisterCommand("rot", CreateInternalCommands);
    factory.RegisterCommand("over", CreateInternalCommands);
    factory.RegisterCommand("drop", CreateInternalCommands);
    factory.RegisterCommand("if", CreateOperatorIf);
    factory.RegisterCommand(".\"", CreatePrintString);
    factory.RegisterCommand("do", CreateDoLoop);
}

bool IsNumber(const std::string& str) { //часть функции взята с стековерфлоу :D
    if (str[0] == '-') {
        return std::all_of(str.begin() + 1, str.end(), [](const char& ch) { return isdigit(ch); });
    }
    return std::all_of(str.begin(), str.end(), [](const char& ch) { return isdigit(ch); });
}

void Parser(Factory<std::unique_ptr<CommandForth>, std::string, std::unique_ptr<CommandForth>(*)()>& factory, std::stack<int>& stack1, std::deque<std::string>& instruction) {
    while (!instruction.empty()) {
        if (IsNumber(instruction.front())) {
            stack1.push(std::stoi(instruction.front()));
            instruction.pop_front();
        }
        else {
            factory.createCommandByName(instruction.front())->Operation(stack1, instruction);
        }
    }
}

int main() {
    std::ifstream file("file.txt");
    std::string str, word;
    std::stringstream stream;

    Factory<std::unique_ptr<CommandForth>, std::string, std::unique_ptr<CommandForth> (*)()> factory;
    Registration(factory);

    std::deque<std::string> instruction;
    while (std::getline(file, str)) {
        stream.clear();
        stream << str;
        while (stream >> word) {
            instruction.push_back(word);
        }
        std::stack <int> stack1;
        Parser(factory, stack1, instruction);
    }
    return 0;
}

