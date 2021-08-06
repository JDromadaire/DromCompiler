#pragma once


#include "Token.h"
#include "Node.h"
#include <vector>

class Parser {
private:
	std::vector<Token*> tokens;
	std::vector<Node*> nodes;
	int token_idx;
	Token* tok;
	Token* next();
	bool advance();
	bool advanced;
public:
	Parser(std::vector<Token*> tokens);

	void init();
	void build();
	std::vector<Node*> recover();

	Node* factor();
	Node* expr();
	Node* mult_div();
	Node* comparison();
	Node* bool_expr();

	Node* choose_build();

	typedef Node*(*next_expr_func)(Parser* prs);
	Node* generic_expr(next_expr_func func, int count, ...);
};
