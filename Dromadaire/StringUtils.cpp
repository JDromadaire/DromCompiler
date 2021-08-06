

#include "StringUtils.h"

#include <stdio.h>
#include <iostream>


bool StringUtils::includes(char chr, const char* chars) {
	if (strlen(&chr) != 1)
		return false;

	int len = strlen(chars);
	for (int i = 0; i < len; i++) {
		if (chr == chars[i])
			return true;
	}

	return false;
}

