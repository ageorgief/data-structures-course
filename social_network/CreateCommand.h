#ifndef CREATECOMMAND_H
#define CREATECOMMAND_H

#include "Command.h"

class CreateCommand : public Command {
private:
	std::string name;
	int age;
public:
	CreateCommand(std::string&, int);
	std::string execute(DataStorage&);
	std::string getName() const;
};

CreateCommand::CreateCommand(std::string& name, int age) : name(name), age(age) {}

std::string CreateCommand::execute(DataStorage& storage) {
	User user(name, age);
	std::string message = "";
	if (!storage.addUser(user)) {
		message += name;
		message += " already exists.\n";
		return message;
	}
	message += this->getName();
	message += " successfully executed.\n";
	return message;
}

std::string CreateCommand::getName() const {
	return "Create";
}

#endif // !CREATECOMMAND_H

