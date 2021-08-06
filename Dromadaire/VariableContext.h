#pragma once

#include <map>
#include "Node.h"

class VariableContext {
public:
	std::map<std::string, Node*> map;
};
