#pragma once

//#include "CommandForth.h"
#include "arithmetic.h"
#include "division.h"
#include "internalcommands.h"
#include "logicaloperations.h"
#include "printstring.h"

#include <map>
#include <stdexcept>


class Factory {
public:
	CommandForth* CreateCommand(const std::string& name) {
		if (creators_.count(name) == 0) {
			return nullptr;
		}
		return creators_[name]();
	}
	void RegisterCommand(const std::string& name, CommandForth* (*creator)()) {
		creators_[name] = creator;
	}
	void Registration() {
		RegisterCommand("+", CreateArithmeticOperation);
		RegisterCommand("-", CreateArithmeticOperation);
		RegisterCommand("*", CreateArithmeticOperation);
		RegisterCommand("/", CreateOperationDivision);
		RegisterCommand("mod", CreateOperationDivision);
		RegisterCommand(">", CreateLogicalOperation);
		RegisterCommand("<", CreateLogicalOperation);
		RegisterCommand("=", CreateLogicalOperation);
		RegisterCommand("drop", CreateInternalCommands);
		RegisterCommand("cr", CreateInternalCommands);
		RegisterCommand("dup", CreateInternalCommands);
		RegisterCommand(".", CreateInternalCommands);
		RegisterCommand("emit", CreateInternalCommands);
		RegisterCommand("swap", CreateInternalCommands);
		RegisterCommand("rot", CreateInternalCommands);
		RegisterCommand("over", CreateInternalCommands);
		RegisterCommand("drop", CreateInternalCommands);
	}
	CommandForth* createCommandByName(const std::string& name) {
		if (CreateCommand(name) == nullptr) {
			throw std::invalid_argument("Error: unknown command");
		}
		return CreateCommand(name);

	}

private:
	std::map<std::string, CommandForth* (*)()> creators_;
};


