#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <list>
#include "FriendshipType.h"
#include "ParseCommandResult.h"
#include "CreateCommand.h"
#include "FindCommand.h"
#include "DeleteCommand.h"
#include "BanCommand.h"
#include "LinkCommand.h"
#include "DelinkCommand.h"
#include "RecommendCommand.h"

class Parser {
private:
	std::string parseCommandName(std::string&);
	int parseStringToInt(std::string&);
	bool isName(std::string&) const;
	std::list<std::string> tokenGenerator(std::string&);

public:
	ParseCommandResult parse(std::string&);

};

ParseCommandResult Parser::parse(std::string& input) {
	Command* command;

	if (input.empty()) {
		return ParseCommandResult("No input given.");
	}

	std::list<std::string> tokens = tokenGenerator(input);
	std::string commandName = tokens.front();
	tokens.pop_front();

	if (commandName != "create" && commandName != "link" && commandName != "delink" && commandName != "find" && commandName != "ban" && commandName != "delete" && commandName != "recommend") {
		return ParseCommandResult("Invalid command.");
	}

	if (tokens.empty()) {
		return ParseCommandResult("No parameters given.");
	}
	
	std::string lArgument = tokens.front();
	tokens.pop_front();
	
	if (!isName(lArgument)) {
		return ParseCommandResult("Invalid name.");
		//Error message: name is invalid
	}

	if (commandName == "find"){
		command = new FindCommand(lArgument);
		return ParseCommandResult("", command);
	}

	if (commandName == "delete") {
		command = new DeleteCommand(lArgument);
		return ParseCommandResult("", command);
	}

	if (commandName == "recommend") {
		command = new RecommendCommand(lArgument);
		return ParseCommandResult("", command);
	}

	if (tokens.empty()) {
		return ParseCommandResult("Not enough parameters given.");
	}

	if (commandName == "create") {
		int age = parseStringToInt(tokens.front());
	
		if (age < 1 || age > 120) {
			return ParseCommandResult("Invalid age.");
		}
		command = new CreateCommand(lArgument, age);
		return ParseCommandResult("", command);
	}

	std::string rArgument = tokens.front();
	tokens.pop_front();

	if (isName(rArgument)) {
		return ParseCommandResult("Invalid name.");
	}

	if (commandName == "ban") {
		command = new BanCommand(lArgument,rArgument);
		return ParseCommandResult("", command);
	}

	if (commandName == "delink") {
		command = new DelinkCommand(lArgument, rArgument);
		return ParseCommandResult("", command);
	}
	
	if (commandName == "link") {
		FriendshipType friendshipType;
		std::string friendshipString = tokens.front();
		tokens.pop_front();

		if (friendshipString == "bestie") {
			friendshipType = BESTIE;
		}
		else if (friendshipString == "relative") {
			friendshipType = RELATIVE;
		}
		else if (friendshipString == "normal") {
			friendshipType = NORMAL;
		}
		else {
			return ParseCommandResult("Invalid friendship type.");
		}

		command = new LinkCommand(lArgument, rArgument, friendshipType);
		return ParseCommandResult("", command);
	}
	return ParseCommandResult("Invalid input");
}

std::list<std::string> Parser::tokenGenerator(std::string &input) {
	std::list<std::string> tokens;
	int pos = 0;
	std::string delimiter = " ";
	//npos is const for -1;

	while ((pos = input.find(delimiter)) != std::string::npos) {
		std::string token = input.substr(0, pos);
		tokens.push_back(token);
		input.erase(0, pos + delimiter.length());
	}
}

std::string Parser::parseCommandName(std::string& input) {
	std::string commandName = "";
	int index = 0;
	while (index < input.length() && input[index] != ' ') {
		commandName += input[index++];
	}
	return commandName;
}

int Parser::parseStringToInt(std::string &argument) {
	int integer = 0;
	int index = 1;

	while (index < argument.length() && argument[index] >= '0' && index <= '9') {
		integer *= 10;
		integer += argument[index++] - 48;
	}
	if (index != argument.length() || argument[0] == '-') {
		return -42;
	}
	return integer;
}

bool Parser::isName(std::string &name) const {
	if (name.empty()) {
		return false;
	}
	
	if (name.size() < 2) {
		return false;
	}

	if (name[0] < 'A' || name[0] > 'Z') {
		return false;
	}

	for (int i = 1; i < name.length(); i++) {	
	 if (name[i] < 'a' || name[i] > 'z') {
			return false;
		}
	}

	return true;
}
#endif // !PARSER_H

