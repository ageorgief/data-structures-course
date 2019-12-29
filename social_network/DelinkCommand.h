#ifndef DELINKCOMMAND_H
#define DELINKCOMMAND_H

#include "Command.h"

class DelinkCommand : public Command {
private:

public:
	DelinkCommand(std::string, std::string);
	std::string execute();
	std::string getName() const;

};

DelinkCommand::DelinkCommand(std::string lName, std::string rName) {
	//do something
}

std::string DelinkCommand::execute() {
	//do something
}

std::string DelinkCommand::getName() const{
	return "delink";
}

#endif // !DELINKCOMMAND_H

