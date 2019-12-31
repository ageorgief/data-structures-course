#ifndef FRIENDSHIP_H
#define FRIENDSHIP_H
#include <string>
#include "FriendshipType.h"
class Friendship {
private:
	std::string name;
	FriendshipType friendshipType;
public:
	Friendship(std::string&, FriendshipType);
	std::string getFriendName() const;
	FriendshipType getFriendshipType() const;
	friend bool operator< (const Friendship& lhs, const Friendship& rhs);
};

Friendship::Friendship(std::string& name, FriendshipType friendshipType) : name(name), friendshipType(friendshipType) {}

std::string Friendship::getFriendName() const {
	return name;
}

FriendshipType Friendship::getFriendshipType() const {
	return friendshipType;
}

bool operator<(const Friendship& lhs, const Friendship& rhs) {
	return lhs.getFriendName() < rhs.getFriendName();
};
#endif // !FRIENDSHIP_H
