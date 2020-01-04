#ifndef USER_H
#define USER_H
#include <string>
#include <list>
#include <set>
#include "Friendship.h"


class User {
private:
	std::string name;
	int age;
	std::set<Friendship> friends;
	std::set<std::string> bannedUsers;
public:
	User(std::string, int);

	std::string getName() const;
	int getAge() const;
	std::set<Friendship>& getFriends();
	std::set<std::string>& getBannedUsers();
	
	bool addFriend(std::string&, std::string);
	bool addBannedUser(std::string&);
	
};

User::User(std::string name, int age) : name(name), age(age){}

std::string User::getName() const {
	return name;
}

int User::getAge() const {
	return age;
}

std::set<Friendship>& User::getFriends(){
	return friends;
}

std::set<std::string>& User::getBannedUsers(){
	return bannedUsers;
}

bool User::addFriend(std::string& name, std::string friednshipType) {
	return friends.insert(Friendship(name,  friednshipType)).second;
}
bool User::addBannedUser(std::string& name) {
	return bannedUsers.insert(name).second;
}

#endif // !USER_H
