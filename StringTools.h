#pragma once
#include <vector>
#include "SubString.h"

namespace dax {
namespace StringTools {
std::vector<SubString> splitString(const std::string& string, const char splitter)
{
	std::vector<SubString> splits;
	auto&& begin = string.begin();
	auto&& current = string.begin();
	while (current != string.end()) {
		if (*current == splitter) {
			splits.push_back({ begin, current });
			++current;
			begin = current;
		}
		else ++current;
	}
	if ( begin != current) splits.push_back({ begin, current });
	return splits;
}
}
}
