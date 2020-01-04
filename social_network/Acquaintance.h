#ifndef ACQUAINTANCE_H
#define ACQUAINTANCE_H

#include <string>

class Acquaintance {
private:
	std::string name;
	int coefficient;
public:
	Acquaintance(std::string&, int);
	friend bool operator < (const Acquaintance& a1, const Acquaintance& a2);
	std::string getName() const;
	int getCoefficient() const;
};

Acquaintance::Acquaintance(std::string &name, int coefficient) : name(name), coefficient(coefficient) {}

std::string Acquaintance::getName() const {
	return name;
}
int Acquaintance::getCoefficient() const {
	return coefficient;
}

bool operator<(const Acquaintance& a1, const Acquaintance& a2) {
	if (a1.name == a2.name) {
		return false;
	}
	if (a1.coefficient == a2.coefficient) {
		return a1.name < a2.name;
	}
	return a1.coefficient > a2.coefficient;
}

#endif // !ACQUAINTANCE_H
