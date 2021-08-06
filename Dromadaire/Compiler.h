#pragma once

#include <vector>
#include "Node.h"

class Compiler {
private:
	std::vector<Node*> nodes;
public:
	Compiler(std::vector<Node*> nodes);
	std::string compile();
};
