#include "interpreter.h"
#include "arithmetic.h"
#include "division.h"
#include "internalcommands.h"
#include "logicaloperations.h"
#include "printstring.h"
#include "ifoperator.h"
#include "doloop.h"

#include <algorithm>
#include <string>
#include <sstream>

void Interpreter::Registration() {
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

bool Interpreter::IsNumber(const std::string& str) { //часть функции взята с стековерфлоу :D
    if ((str[0] == '-' || str[0] == '+') && str[1]) { 
        return std::all_of(str.begin() + 1, str.end(), [](const char& ch) { return isdigit(ch); });
    }
    return std::all_of(str.begin(), str.end(), [](const char& ch) { return isdigit(ch); });
}

void Interpreter::Parser() {
    while (!context.InstructionIsEmpty()) {
        if (IsNumber(context.InstructionFront())) {
            int val = std::stoi(context.InstructionFront());
            context.StackPush(val);
            context.InstructionPopFront();
        }
        else {
            auto oper = std::unique_ptr<CommandForth>(factory.CreateCommand(context.InstructionFront()));
            oper->Operation(context);
        }
    }
}

void Interpreter::Executor() {
    std::string str, word;
    std::stringstream stream;
    Registration();
    while (std::getline(input, str)) {
            stream.clear();
            stream << str;
            while (stream >> word) {
                context.InstructionPushBack(word);
            }
            Parser();
        }
}