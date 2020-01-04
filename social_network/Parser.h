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
	std::string isValidName(std::string&) const;
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
	
	std::string nameValidationString = isValidName(lArgument);
	
	if (nameValidationString != "valid") {
		return ParseCommandResult(nameValidationString);
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
		std::string ageString = tokens.front();
		if (ageString[0] == '0') {
			return ParseCommandResult("Invalid age.");
		}
		for (int i = 0; i < ageString.length(); i++) {
	
			if (ageString[i] < '0' || ageString[i] > '9' || i > 2) {
				return ParseCommandResult("Invalid age.");
			}
		}
		int age = stoi(tokens.front());
	
		if (age > 120) {
			return ParseCommandResult("Invalid age.");
		}
		command = new CreateCommand(lArgument, age);
		return ParseCommandResult("", command);
	}

	std::string rArgument = tokens.front();
	tokens.pop_front();

	nameValidationString = isValidName(rArgument);

	if (nameValidationString != "valid") {
		return ParseCommandResult(nameValidationString);
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
		if (tokens.empty()) {
			return ParseCommandResult("No friendship type has been entered.");
		}
	
		std::string friendshipType = tokens.front();
		tokens.pop_front();

		if (friendshipType != "bestie" && friendshipType != "relative" && friendshipType != "normal") {
			return ParseCommandResult("Invalid friendship type.");
		}
		
		command = new LinkCommand(lArgument, rArgument, friendshipType);
	
		return ParseCommandResult("", command);
	}
	return ParseCommandResult("Invalid input");
}

std::list<std::string> Parser::tokenGenerator(std::string &input) {
	std::list<std::string> tokens;
	char delimiter = ' ';
	int current, previous = 0;
	current = input.find(delimiter);

	while (current != std::string::npos) {
		tokens.push_back(input.substr(previous, current - previous));
		previous = current + 1;
		current = input.find(delimiter, previous);
	}
	tokens.push_back(input.substr(previous, current - previous));

	return tokens;
}

std::string Parser::parseCommandName(std::string& input) {
	std::string commandName = "";
	int index = 0;
	while (index < input.length() && input[index] != ' ') {
		commandName += input[index++];
	}
	return commandName;
}

std::string Parser::isValidName(std::string &name) const{
	if (name.empty()) {
		return "You have not entered name.";
	}
	
	if (name.size() < 2) {
		return "Name cannot contain less than 2 characters.";
	}

	if (name[0] < 'A' || name[0] > 'Z') {
		return "Name should start with uppercase latin letter.";
	}

	for (int i = 1; i < name.length(); i++) {	
	 if (name[i] < 'a' || name[i] > 'z') {
		 return "Name cannot contain characters different than latin letters.";
		}
	}

	return "valid";
}
#endif // !PARSER_H

