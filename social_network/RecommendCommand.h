#ifndef RECOMMENDCOMMAND_H
#define RECOMMENDCOMMAND_H

#include "Command.h"
#include <queue>
#include <set>
#include "Acquaintance.h"

class RecommendCommand : public Command {
private:
	std::string name;
	int calculateAcquaintanceCoefficent(User&, User&);
	std::list<std::string> collectUsersForRecommendation(User&, DataStorage&);
	std::list<Acquaintance> getUsersWithMostFriends(DataStorage&);
	
public:
	RecommendCommand(std::string&);
	std::string execute(DataStorage&);
	std::string getName() const;
};

RecommendCommand::RecommendCommand(std::string& name) : name(name) {}

std::string RecommendCommand::execute(DataStorage& storage) {
	std::map<std::string, User>::iterator it = storage.getUserData()->find(name);
	if (it == storage.getUserData()->end()) {
		return name + " not found.\n";
	}
	std::list<std::string> usersForRecommendation = collectUsersForRecommendation(it->second, storage);

	std::string result = "";

	for (std::list<std::string>::iterator it = usersForRecommendation.begin(); it != usersForRecommendation.end(); it++) {
		result += *it;
		result += ", ";
	}

	return result.substr(0,result.size()-2) + "\n";
}


std::list<std::string> RecommendCommand::collectUsersForRecommendation(User& user, DataStorage& storage) {
	std::queue<User> toBeVisited;
	std::set<std::string> visitedUsers;
	visitedUsers.insert(user.getName());

	std::set<Acquaintance> usersForRecommendation;
	std::set<std::string> namesOfUsersThatCannotBeRecommended;
	namesOfUsersThatCannotBeRecommended.insert(user.getName());
	
	for (std::set<Friendship>::iterator friendsIterator = user.getFriends().begin(); friendsIterator != user.getFriends().end(); friendsIterator++) {
		toBeVisited.push(storage.getUserData()->find(friendsIterator->getFriendName())->second);
	}
	

	
	while (!toBeVisited.empty() && usersForRecommendation.size() < 30) {
		std::set<std::string>::iterator friendName = visitedUsers.find(toBeVisited.front().getName());
		if (friendName == visitedUsers.end()) {
			User friendOfUser = toBeVisited.front();
			visitedUsers.insert(friendOfUser.getName());

			for (std::set<Friendship>::iterator friendsIterator = friendOfUser.getFriends().begin(); friendsIterator != friendOfUser.getFriends().end(); friendsIterator++) {
				
				if (user.getName() != friendsIterator->getFriendName()) {
					std::set<std::string>::iterator bannedUser = user.getBannedUsers().find(friendsIterator->getFriendName());
					
					if (bannedUser == user.getBannedUsers().end()) {
						std::string friendUserName = friendsIterator->getFriendName();

						std::set<Friendship>::iterator friendOfFriendOfUser = user.getFriends().find(Friendship(friendUserName, "normal"));
						
						if (friendOfFriendOfUser == user.getFriends().end()) {
							User potentialUserForRecommendation = storage.getUserData()->find(friendsIterator->getFriendName())->second;

							int acquaintanceCoefficent = calculateAcquaintanceCoefficent(user, potentialUserForRecommendation);

							std::string potentialUserForRecommendationName = friendsIterator->getFriendName();

							usersForRecommendation.insert(Acquaintance(potentialUserForRecommendationName, acquaintanceCoefficent));
							
							namesOfUsersThatCannotBeRecommended.insert(potentialUserForRecommendation.getName());

							toBeVisited.push(storage.getUserData()->find(friendsIterator->getFriendName())->second);				
						}
					}
					else {
						namesOfUsersThatCannotBeRecommended.insert(*bannedUser);
					}
				}	
			}		
		}
		toBeVisited.pop();
	}
	std::list<std::string> result;
	
	for (std::set<Acquaintance>::iterator it = usersForRecommendation.begin(); it != usersForRecommendation.end(); ++it) {
		result.push_back(it->getName());
	}

	if (usersForRecommendation.size() < 30) {
		std::list<Acquaintance> usersWithMostFriends = getUsersWithMostFriends(storage);
		for (std::list<Acquaintance>::iterator it = usersWithMostFriends.begin(); it != usersWithMostFriends.end(); it++) {
			std::set<std::string>::iterator nameIterator = namesOfUsersThatCannotBeRecommended.find(it->getName());
			if (nameIterator == namesOfUsersThatCannotBeRecommended.end() && result.size() < 30) {
				result.push_back(it->getName());
			}
		}
	}	
	return result;
}

std::list <Acquaintance> RecommendCommand::getUsersWithMostFriends(DataStorage& storage) {
	std::set<Acquaintance> usersWithMostFriends;
	for (std::map<std::string, User>::iterator it = storage.getUserData()->begin(); it != storage.getUserData()->end(); it++){		
		std::string userName = it->second.getName();
		Acquaintance user(userName, it->second.getFriends().size());
		usersWithMostFriends.insert(user);
		if (usersWithMostFriends.size() > 30) {
			std::set<Acquaintance>::iterator lastElementIterator = usersWithMostFriends.end();
			lastElementIterator--;
			usersWithMostFriends.erase(lastElementIterator);
		}
	}
	 
	std::list<Acquaintance> usersWithMostFriendsList;
	for (std::set<Acquaintance>::iterator it = usersWithMostFriends.begin(); it != usersWithMostFriends.end(); it++) {
		usersWithMostFriendsList.push_back(*it);
	}

	return usersWithMostFriendsList;
}

int RecommendCommand::calculateAcquaintanceCoefficent(User& lUser,User& rUser) {
	int acquaintanceCoefficent = 0;
	for (std::set<Friendship>::iterator friendsIterator = rUser.getFriends().begin(); friendsIterator != rUser.getFriends().end(); friendsIterator++) {
		std::set<Friendship>::iterator mutualFriend = lUser.getFriends().find(*friendsIterator);
		if (mutualFriend != lUser.getFriends().end()) {
			if (mutualFriend->getFriendshipType() == "bestie") {
				acquaintanceCoefficent += 3;
			}
			if (mutualFriend->getFriendshipType() == "relative") {
				acquaintanceCoefficent += 2;
			}
			if (mutualFriend->getFriendshipType() == "normal") {
				acquaintanceCoefficent += 3;
			}
		}	
	}
	return acquaintanceCoefficent;
}

std::string RecommendCommand::getName() const {
	return "recommend";
}
#endif // !RECOMMENDCOMMAND_H

