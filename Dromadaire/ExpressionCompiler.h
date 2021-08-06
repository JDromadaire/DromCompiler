#pragma once

#include <string.h>
#include "Node.h"


class ExpressionCompiler {
public:
	static std::string compile(Node* uk_node);
	static std::string getValue(Node* node);
};
