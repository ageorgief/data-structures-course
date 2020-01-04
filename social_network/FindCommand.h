#ifndef FINDCOMMAND_H
#define FINDCOMMAND_H

#include "Command.h"
#include <set>
#include <string>

class FindCommand : public Command {
private:
	std::string name;
	std::string getUserData(User&);

public:
	FindCommand(std::string&);
	std::string execute(DataStorage&);
	std::string getName() const;

};

FindCommand::FindCommand(std::string& name) : name(name) {}

std::string FindCommand::execute(DataStorage& storage) {
	std::map<std::string, User>::iterator it = storage.getUserData()->find(name);
	if (it == storage.getUserData()->end()) {
		return name + " not found.\n";
	}

	return "\n" +name + " found:" + "\n" + getUserData(it->second);

}
std::string FindCommand::getUserData(User& user) {
	std::string data = "Name: ";
	data += user.getName();
	data += "\n";
	data += "Age: ";
	data += std::to_string(user.getAge());
	data += "\n";
	data += "Friends(";
	if (user.getFriends().size() == 0) {
		data += "0): Doesn't have any friends.\n";
	}
	else {
		data += std::to_string(user.getFriends().size());
		data += "): ";
		for (std::set<Friendship>::iterator it = user.getFriends().begin(); it != user.getFriends().end(); it++) {
			data += it->getFriendName();
			data += ", ";
		}
		data = data.substr(0, data.length() - 2);
		data += "\n";
	}
	return data;
}
std::string FindCommand::getName() const {
	return "find";
}
#endif // !FINDCOMMAND_H

