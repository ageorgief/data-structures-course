#ifndef BANCOMMAND_H
#define BANCOMMAND_H

#include "Command.h"

class BanCommand : public Command {
private:

public:
	BanCommand(std::string, std::string);
	std::string execute();
	std::string getName() const;
};

BanCommand::BanCommand(std::string lName, std::string rName) {
	//do something
}

std::string BanCommand::execute() {
	//do something
}

std::string BanCommand::getName() const {
	return "ban";
}
#endif // !BANCOMMAND_H

