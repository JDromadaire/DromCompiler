#include "Compiler.h"
#include "ExpressionCompiler.h"

Compiler::Compiler(std::vector<Node*> nodes)
{
	this->nodes = nodes;
}



std::string Compiler::compile() {
	std::string str = "";

	for (int i = 0; i < this->nodes.size(); i++) {
		Node* node = this->nodes[i];

		str += ExpressionCompiler::compile(node);
	}

	return str;
}
