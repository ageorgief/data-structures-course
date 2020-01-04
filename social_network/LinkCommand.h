#ifndef LINKCOMMAND_H
#define LINKCOMMAND_H

#include "Command.h"

class LinkCommand : public Command {
private:
	std::string lName;
	std::string rName;
	std::string friendshipType;

public:
	LinkCommand(std::string&, std::string&, std::string);
	std::string execute(DataStorage&);
	std::string getName() const;
};

LinkCommand::LinkCommand(std::string &lName, std::string &rName, std::string friendshipType) : lName(lName), rName(rName), friendshipType(friendshipType){}

std::string LinkCommand::execute(DataStorage& storage) {
	if (lName == rName) {
		return lName + " cannot be friend with him\herself.\n";
	}

	std::map<std::string, User>::iterator itLName = storage.getUserData()->find(lName);
	if (itLName == storage.getUserData()->end()) {
		return lName + " not found.\n";
	}
	std::map<std::string, User>::iterator itRName = storage.getUserData()->find(rName);
	if (itRName == storage.getUserData()->end()) {
		return rName + " not found.\n";
	}

	for (std::set<std::string>::iterator it = itLName->second.getBannedUsers().begin(); it != itLName->second.getBannedUsers().end(); it++) {
		if (*it == rName) {
			return lName + " and " + rName + " cannot become friends, because " + lName + " banned " + rName + ".\n";
		}
	}
	for (std::set<std::string>::iterator it = itRName->second.getBannedUsers().begin(); it != itRName->second.getBannedUsers().end(); it++) {
		if (*it == lName) {
			return lName + " and " + rName + " cannot become friends, because " + rName + " banned " + lName + ".\n";
		}
	}
	
	if (!itLName->second.addFriend(rName, friendshipType)) {
		return lName + " and " + rName + " are already friends.\n";
	}
	itRName->second.addFriend(lName, friendshipType);
	return lName + " and " + rName + " became friends.\n";
}
std::string LinkCommand::getName() const {
	return "link";
}

#endif // !LINKCOMMAND_H

