#ifndef OUTPUT_H
#define OUTPUT_H
#include <string>
class Output {
public:
	void print(std::string& ) const;
};

void Output::print(std::string& output) const {
	std::cout << output << std::endl;
}

#endif // !OUTPUT_H

