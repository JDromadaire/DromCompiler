#pragma once

#include <map>
#include "Node.h"

class EntryPoint {
private:
	std::map<std::string, Node*> ctx;
public:
	bool shell();
	void file(char* fname);
	void main(const char* str);
};