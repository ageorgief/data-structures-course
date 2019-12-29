#ifndef LINKCOMMAND_H
#define LINKCOMMAND_H

#include "Command.h"
#include "FriendshipType.h"

class LinkCommand : public Command {
private:

public:
	LinkCommand(std::string, std::string, FriendshipType);
	std::string execute();
	std::string getName() const;

};

LinkCommand::LinkCommand(std::string lName, std::string rName, FriendshipType friendShipType) {
	//do something
}

std::string LinkCommand::execute() {
	//do something
}
std::string LinkCommand::getName() const {
	return "link";
}

#endif // !LINKCOMMAND_H

