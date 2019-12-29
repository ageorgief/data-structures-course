#ifndef RECOMMENDCOMMAND_H
#define RECOMMENDCOMMAND_H

#include "Command.h"

class RecommendCommand : public Command {
private:

public:
	RecommendCommand(std::string);
	std::string execute();
	std::string getName() const;

};

RecommendCommand::RecommendCommand(std::string name) {
	//do something
}

std::string RecommendCommand::execute() {
	//do something
}
std::string RecommendCommand::getName() const {
	return "recommend";
}
#endif // !RECCOMENDCOMMAND_H

