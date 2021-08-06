#pragma once
#include <vector>
#include "Token.h"

class Lexer {
private:
	const char* chr;
	int index;
	int length;
	char act;
	bool advanced;
	bool advance();
	const char* next();
	std::vector<Token*> data;
	const char* buildOperator_type();
	bool buildOperator_possible();
public:
	Lexer(const char* chr);
	void init();
	void build();
	bool buildNumber(const char* NUMBER_STRING);
	bool buildName(const char* NAME_STRING, const char* END_NAME_STRING);
	bool buildGeneric(const char* STRING, const char* token_type);
	bool buildOperator();
	std::vector<Token*> recover();
};