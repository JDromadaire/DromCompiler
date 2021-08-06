#include "Lexer.h"
#include <stdio.h>
#include <iostream>

#include "StringUtils.h"

// Advance to next character
bool Lexer::advance() {
	this->advanced = false;
	if (this->index + 1 < this->length) {
		this->index += 1;
		this->advanced = true;
		this->act = chr[this->index];
	}
	return this->advanced;
}

const char* Lexer::next() {
	if (this->index + 1 < this->length) {
		return &chr[index + 1];
	}
	return nullptr;
}

// Initialize Lexer
void Lexer::init() {
	this->length = strlen(this->chr);
	this->index = -1;
	this->advance();

	this->build();
}

// Build Lexer
void Lexer::build() {
	// Const for numbers, eof strings and ignored strings
	const char* NUMBER_STRING = "0123456789";
	const char* NAME_STRING = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	const char* END_NAME_STRING = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	const char* IGNORED_STRING = " \t\r";
	const char* EOF_STRING = ";\n";

	// Main loop
	while (this->advanced) {
		// Boolean to check if system already advanced too far
		bool advanced = false;

		// If it is a number, build a new token in a different function
		if (StringUtils::includes(this->act, NUMBER_STRING)) {
			advanced = this->buildNumber(NUMBER_STRING);
		}
		else if (this->buildName(NAME_STRING, END_NAME_STRING)) {
			advanced = true;
		} else if (this->buildOperator()) {}
		// Build EOF Tokens
		else if (StringUtils::includes(this->act, EOF_STRING)) {
			if (this->data.size() == 0 
				|| this->data[this->data.size() - 1]->getType() != "EOF") {
				this->data.push_back(new Token("EOF", ""));
			}
		}
		// Search for unknown chars
		else if (!StringUtils::includes(this->act, IGNORED_STRING)) {
			std::cout << "Could not find the requested char : ";
			std::cout << this->act;
			std::cout << "\n";
		}

		// Advance if needed
		if (!advanced)
			this->advance();
	}

	// Add final EOF at the end of program
	if (this->data.size() == 0
		|| this->data[this->data.size() - 1]->getType() != "EOF") {
		this->data.push_back(new Token("EOF", ""));
	}
}

// Generate name from actual string
bool Lexer::buildName(const char * NAME_STRING, const char * END_NAME_STRING) {
	if (!StringUtils::includes(this->act, NAME_STRING))
		return false;

	this->buildGeneric(END_NAME_STRING, "name");

	return true;
}

// Generate number token from actual string
bool Lexer::buildNumber(const char* NUMBER_STRING) {
	return this->buildGeneric(NUMBER_STRING, "number");
}

// Generate generic token from allowed data and type object
bool Lexer::buildGeneric(const char* STRING, const char* type) {
	std::string str = *(new std::string());

	while (this->advanced && StringUtils::includes(this->act, STRING)) {
		str += this->act;
		this->advance();
	}

	this->data.push_back(new Token(type, str));

	return true;
}

bool Lexer::buildOperator() {
	if (!this->buildOperator_possible())
		return false;

	const char* type = this->buildOperator_type();
	this->data.push_back(new Token(type, ""));

	return true;
}

const char * Lexer::buildOperator_type() {
	if (this->act == *"=") {
		if (this->next() == "=") return "EQEQ";
		return "EQUALS";
	}
	if (this->act == *"+") return "PLUS";
	if (this->act == *"-") return "MINUS";
	if (this->act == *"*") return "MULTIPLY";
	if (this->act == *"/") return "DIVIDE";
	if (this->act == *"^") return "POWER";
	if (this->act == *"!") return "NEGATE";
	if (this->act == *".") return "DOT";

	return nullptr;
}

bool Lexer::buildOperator_possible() {
	return this->act == *"="
		|| this->act == *"+"
		|| this->act == *"-"
		|| this->act == *"*"
		|| this->act == *"/"
		|| this->act == *"^"
		|| this->act == *"!"
		|| this->act == *".";
}


// Create Lexer
Lexer::Lexer(const char* chr) {
	this->chr = chr;
}


std::vector<Token*> Lexer::recover() {
	return this->data;
}