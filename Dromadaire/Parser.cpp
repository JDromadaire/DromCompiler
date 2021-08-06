
#include "Parser.h"
#include <iostream>

Token * Parser::next()
{
	if (this->token_idx + 1 < this->tokens.size()) {
		return this->tokens[this->token_idx + 1];
	}
	return nullptr;
}

bool Parser::advance()
{
	this->advanced = false;
	if (this->token_idx + 1 < this->tokens.size()) {
		this->advanced = true;
		this->token_idx += 1;
		this->tok = this->tokens[this->token_idx];
		return true;
	}
	return false;
}

Parser::Parser(std::vector<Token*> tokens) {
	this->tokens = tokens;
	this->init();
}

void Parser::init() {
	this->token_idx = -1;
	this->advance();
}

Node* Parser::factor() {
	if (this->tok->getType() == "number") {
		Node* node = new IntNode(std::stoi(this->tok->getValue()));
		this->advance();
		return node;
	}
	if (this->tok->getType() == "name") {
		Node* node = new NameNode(this->tok->getValue());
		this->advance();
		return node;
	}
	return nullptr;
}

Node* ext_factor(Parser* parser) {
	return parser->factor();
}
Node* ext_mult_div(Parser* parser) {
	return parser->mult_div();
}
Node* ext_expr(Parser* parser) {
	return parser->expr();
}

Node* Parser::expr() {
	return this->generic_expr((next_expr_func)ext_mult_div, 2, "PLUS", "MINUS");
}
Node* Parser::mult_div() {
	return this->generic_expr((next_expr_func)ext_factor, 3, "MULTIPLY", "DIVIDE", "POWER");
}

#include <stdarg.h>
Node* Parser::generic_expr(next_expr_func func, int count, ...) {
	va_list ap;
	std::vector<const char*> chars;

	va_start(ap, count);
	for (int j = 0; j < count; j++)
		chars.push_back(va_arg(ap, const char*));
	va_end(ap);

	Node* left = func(this);
	while (this->advanced) {
		const std::string chr = this->tok->getType();

		bool found = false;
		for (int j = 0; j < count; j++) {
			if (chr == chars[j]) {
				found = true;
				break;
			}
		}

		if (!found)
			break;

		this->advance();

		left = new OperatorNode(left, func(this), chr);
	};

	return left;
}

#include <iostream>

void Parser::build() {


	while (this->advanced) {
		
		Node* data = this->choose_build();
		if (data != nullptr)
			this->nodes.push_back(data);
		else {
			this->nodes.clear();
			return;
		}

		if (this->tok->getType() != "EOF") {
			std::cout << "Couldn't find EOF after expression";
			this->nodes.clear();
			return;
		}

		this->advance();

	}


}

Node* Parser::choose_build() {
	Token* next = this->next();
	
	if (this->tok->getType() == "name" && next != nullptr && next->getType() == "EQUALS") {
		Token* tok = this->tok;
		this->advance();
		this->advance();
		if (!this->advanced) {
			std::cout << "Could not find expression after the set expression \"";
			std::cout << tok->getType();
			std::cout << "=...\"\n";
			return nullptr;
		}
		return new SetNode(tok->getValue(), this->expr());
	}

	return this->expr();
}

std::vector<Node*> Parser::recover() {
	return this->nodes;
}
