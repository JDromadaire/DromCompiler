#include "Token.h"

const std::string Token::getValue() {
	return this->value;
}
const std::string Token::getType() {
	return this->type;
}
Token::Token(const std::string type, const std::string value) {
	this->type = type;
	this->value = value;
}