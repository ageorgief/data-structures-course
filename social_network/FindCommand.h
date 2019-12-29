#ifndef FINDCOMMAND_H
#define FINDCOMMAND_H

#include "Command.h"

class FindCommand : public Command {
private:

public:
	FindCommand(std::string);
	std::string execute();
	std::string getName() const;

};

FindCommand::FindCommand(std::string name) {
	//do something
}

std::string FindCommand::execute() {
	//do something
}
std::string FindCommand::getName() const {
	return "find";
}
#endif // !FINDCOMMAND_H

