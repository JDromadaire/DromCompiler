#include "EntryPoint.h"
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include <map>

bool EntryPoint::shell() {
	std::string dat;
	std::cout << ">> ";

	std::getline(std::cin, dat);
	if (dat == "exit()") {
		return false;
	}

	this->main(dat.c_str());
	return true;
}

void EntryPoint::main(const char* str) {
	Lexer lex = Lexer(str);

	lex.init();

	std::vector<Token*> tokens = lex.recover();
	if (tokens.size() <= 1) return;

	/*for (int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i]->getType();
		std::cout << ":";
		std::cout << tokens[i]->getValue();
		std::cout << "\n";
	}*/

	Parser* prs = new Parser(tokens);
	prs->build();
	std::vector<Node*> nodes = prs->recover();

	for (int i = 0; i < nodes.size(); i++) {
		//std::cout << nodes[i]->toString();
		//std::cout << "\n";
		Node* node = nodes[i]->evaluate(&ctx);
		if (node != nullptr) {
			std::cout << node->toString();
			std::cout << "\n";
		}
		
	}

	std::cout << "Compiling...\n";
	Compiler* compiler = new Compiler(nodes);
	std::cout << compiler->compile();
}

int main() {
	EntryPoint entry = EntryPoint();

	std::cout << "Welcome to Drom++, the Dromadaire code converter to assembly !\n";

	while (entry.shell()) {}

	return 0;
};