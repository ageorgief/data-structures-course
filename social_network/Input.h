#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>

class Input {
public:
	std::string read();
};

std::string Input::read() {
	std::string input;
	std::getline(std::cin, input);
	return input;
}

#endif // !INPUT_H

