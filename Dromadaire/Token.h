#pragma once
#include <vector>
#include <string>

class Token {
private:
	std::string value;
	std::string type;
public:
	const std::string getType();
	const std::string getValue();
	Token(const std::string type, const std::string val);
};