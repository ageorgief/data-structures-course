#ifndef BANCOMMAND_H
#define BANCOMMAND_H

#include "Command.h"

class BanCommand : public Command {
private:
	std::string banningUser;
	std::string bannedUser;

public:
	BanCommand(std::string&, std::string&);
	std::string execute(DataStorage&);
	std::string getName() const;
};

BanCommand::BanCommand(std::string &banningUser, std::string &bannedUser) : banningUser(banningUser), bannedUser(bannedUser) {}

std::string BanCommand::execute(DataStorage& storage) {
	if (banningUser == bannedUser) {
		return banningUser + " cannot ban his|herself.\n";
	}

	std::map<std::string, User>::iterator itBanning = storage.getUserData()->find(banningUser);
	if (itBanning == storage.getUserData()->end()) {
		return banningUser + " not found.\n";
	}
	std::map<std::string, User>::iterator itBanned = storage.getUserData()->find(bannedUser);
	if (itBanned == storage.getUserData()->end()) {
		return bannedUser + " not found.\n";
	}

	if (!itBanning->second.addBannedUser(bannedUser)) {
		return banningUser + " already banned " + bannedUser + ".\n";
	}
	else {
		std::set<Friendship>::iterator it = itBanning->second.getFriends().find(Friendship(bannedUser, "normal"));
		if (it != itBanning->second.getFriends().end()) {
			itBanning->second.getFriends().erase(it);
			it = itBanned->second.getFriends().find(Friendship(banningUser, "normal"));
			itBanned->second.getFriends().erase(it);
		}
	}
	return banningUser + " successfully banned " + bannedUser + ".\n";
}

std::string BanCommand::getName() const {
	return "ban";
}
#endif // !BANCOMMAND_H

