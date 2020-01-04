#ifndef FRIENDSHIP_H
#define FRIENDSHIP_H
#include <string>
#include "FriendshipType.h"
class Friendship {
private:
	std::string name;
	std::string friendshipType;
public:
	Friendship(std::string&, std::string);
	std::string getFriendName() const;
	std::string getFriendshipType() const;
	friend bool operator< (const Friendship& lhs, const Friendship& rhs);
};

Friendship::Friendship(std::string& name, std::string friendshipType) : name(name), friendshipType(friendshipType){}

std::string Friendship::getFriendName() const {
	return name;
}

std::string Friendship::getFriendshipType() const {
	return friendshipType;
}

bool operator<(const Friendship& lhs, const Friendship& rhs) {
	return lhs.getFriendName() < rhs.getFriendName();
};
#endif // !FRIENDSHIP_H
