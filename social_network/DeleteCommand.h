#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "Command.h"

class DeleteCommand : public Command {
private:

public:
	DeleteCommand(std::string);
	std::string execute();
	std::string getName() const;
};

DeleteCommand::DeleteCommand(std::string name) {
	//do something
}

std::string DeleteCommand::execute() {
	//do something
}
std::string DeleteCommand::getName() const {
	return "delete";
}
#endif // !DELETECOMMAND_H

