#ifndef CREATECOMMAND_H
#define CREATECOMMAND_H

#include "Command.h"

class CreateCommand : public Command {
private:

public:
	CreateCommand(std::string, int);
	std::string execute();
	std::string getName() const;
};

CreateCommand::CreateCommand(std::string name, int age) {
	//do something
}

std::string CreateCommand::execute() {
	//do something
}

std::string CreateCommand::getName() const {
	return "create";
}

#endif // !CREATECOMMAND_H

