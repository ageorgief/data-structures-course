#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "Command.h"


class DeleteCommand : public Command {
private:
	std::string name;
public:
	DeleteCommand(std::string&);
	std::string execute(DataStorage&);
	std::string getName() const;
};

DeleteCommand::DeleteCommand(std::string& name) : name(name){}

std::string DeleteCommand::execute(DataStorage& storage) {
	std::map<std::string, User>::iterator it = storage.getUserData()->find(name);
	if (it == storage.getUserData()->end()) {
		return name + " not found.\n";
	}

	storage.getUserData()->erase(it);
	return name + " successfully deleted\n";
}

std::string DeleteCommand::getName() const {
	return "delete";
}
#endif // !DELETECOMMAND_H

