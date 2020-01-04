#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "DataStorage.h"

class Command {
private:
public:
	virtual std::string getName() const = 0;
	virtual std::string execute(DataStorage&) = 0;
};

#endif // !COMMAND_H

