#ifndef DELINKCOMMAND_H
#define DELINKCOMMAND_H

#include "Command.h"

class DelinkCommand : public Command {
private:
	std::string lName;
	std::string rName;
public:
	DelinkCommand(std::string&, std::string&);
	std::string execute(DataStorage&);
	std::string getName() const;

};

DelinkCommand::DelinkCommand(std::string& lName, std::string& rName) :lName(lName), rName(rName) {}

std::string DelinkCommand::execute(DataStorage& storage) {
	if (lName == rName) {
		return lName + " cannot unfriend him\herself.\n";
	}

	std::map<std::string, User>::iterator itLName = storage.getUserData()->find(lName);
	if (itLName == storage.getUserData()->end()) {
		return lName + " not found.\n";
	}

	std::map<std::string, User>::iterator itRName = storage.getUserData()->find(rName);
	if (itRName == storage.getUserData()->end()) {
		return rName + " not found.\n";
	}
	
	std::set<Friendship>::iterator it = itLName->second.getFriends().find(Friendship(rName,"normal"));
	
	if (it == itLName->second.getFriends().end()) {
		return lName + " and " + rName + " are not friends.\n";
	}

	itLName->second.getFriends().erase(it);
	it = itRName->second.getFriends().find(Friendship(lName, "normal"));
	itRName->second.getFriends().erase(it);

	return lName + " successfully unfirended " + rName + ".\n";
}

std::string DelinkCommand::getName() const{
	return "delink";
}

#endif // !DELINKCOMMAND_H

