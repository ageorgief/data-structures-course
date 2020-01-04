#ifndef PARSECOMMANDRESULT_H
#define PARSECOMMANDRESULT_H

#include <string>
#include "Command.h"

class ParseCommandResult {
private:
	std::string errorMessage;
	Command * command;
	
public:
	ParseCommandResult(std::string , Command*);
	bool isError() const;
	std::string getErrorMessage() const;
	Command* getCommand() const;
};

ParseCommandResult::ParseCommandResult (std::string errorMessage = "", Command* command = nullptr) : errorMessage(errorMessage), command(command) {}

bool ParseCommandResult::isError() const {
	return !errorMessage.empty();
}
std::string ParseCommandResult::getErrorMessage() const {
	return errorMessage + "\n";
}
Command* ParseCommandResult::getCommand() const {
	return command;
}

#endif // !DELINKCOMMAND_H

