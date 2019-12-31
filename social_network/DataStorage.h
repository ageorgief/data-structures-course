#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "User.h"



class DataStorage {
private:
	std::map<std::string, User> userData;
	std::fstream dataFile;

	std::string composeUser(User&);
	std::list<std::string> tokenGenerator(std::string&,char);
	User parseUser(std::string&);

public:
	std::map<std::string, User>* getUserData();
	void writeUsersDataToFile();
	void loadData();
	void addUser(User&);
};

std::map<std::string, User>* DataStorage::getUserData() {
	return &userData;
}

void DataStorage::addUser(User& user) {
	userData.insert({ user.getName(),user });
}
void DataStorage::loadData() {
	dataFile.open("user_data.txt", std::ios::in);

	if (dataFile.is_open())
	{
		std::string userString;
		while (getline(dataFile, userString)) {		
			User user = parseUser(userString);
			addUser(user);
		}
		dataFile.close();
	}
	else {
		std::cout << "Unable to open the database." << std::endl;
	}
}

User DataStorage::parseUser(std::string& userString) {
	std::list<std::string> tokens = tokenGenerator(userString, ' ');
	
	std::string name = tokens.front();
	tokens.pop_front();
	
	int age = std::stoi(tokens.front());
	tokens.pop_front();

	User parsedUser(name,age);
	if (!tokens.empty()) {
		if (tokens.front().front() == '(') {
			std::list<std::string> friendsTokens = tokenGenerator(tokens.front(), ',');
			
			while (!friendsTokens.empty()) {
				std::string friendString = friendsTokens.front().substr(1, friendsTokens.front().length() - 2);
				friendsTokens.pop_front();

				std::list<std::string> parsedFriend = tokenGenerator(friendString, '-');
				
				if (parsedFriend.back() == "bestie") {
					parsedUser.addFriend(parsedFriend.front(), BESTIE);
				}
				if (parsedFriend.back() == "relative") {
					parsedUser.addFriend(parsedFriend.front(), RELATIVE);
				}
				if (parsedFriend.back() == "normal") {
					parsedUser.addFriend(parsedFriend.front(), NORMAL);
				}
				parsedFriend.pop_front();
			}
			tokens.pop_front();
		}
		if (!tokens.empty()) {
			std::list<std::string> bannedUsersTokens = tokenGenerator(tokens.front(), ',');
			while (!bannedUsersTokens.empty()) {
				parsedUser.addBannedUser(bannedUsersTokens.front());
				bannedUsersTokens.pop_front();
			}
		}
	}	

	return parsedUser;
}

std::list<std::string> DataStorage::tokenGenerator(std::string& input, char delimiter) {
	std::list<std::string> tokens;
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
void DataStorage::writeUsersDataToFile() {
	dataFile.open("user_data.txt", std::ios::out);
	
	if (dataFile.is_open())
	{
		for (std::map<std::string, User>::iterator it = userData.begin(); it != userData.end(); it++)
		{
			dataFile << composeUser(it->second);
		}
		dataFile.close();
	}
	else {
		std::cout << "Unable to open the database." << std::endl;
	}
	
}

std::string DataStorage::composeUser(User& user) {
	std::string result = user.getName();
	result += " ";
	result += std::to_string(user.getAge());
	result += " ";
	
	for (std::set<Friendship>::iterator it = user.getFriends().begin(); it != user.getFriends().end(); it++) {
		result += "(";
		result += it->getFriendName();
		result += ",";

		if (it->getFriendshipType() == BESTIE) {
			result += "bestie";
		}
		if (it->getFriendshipType() == RELATIVE) {
			result += "relative";
		}
		if (it->getFriendshipType() == NORMAL) {
			result += "normal";
		}

		result += ")";
		result += ",";
	}
	
	result[result.size() - 1] = ' ';

	for (std::set<std::string>::iterator it = user.getBannedUsers().begin(); it != user.getBannedUsers().end(); it++) {
		result += *it;
		result += ",";
	}

	result[result.size() - 1] = '\n';
	
	return result;
}


#endif // !DATASTORAGE_H
