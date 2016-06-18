#pragma once
#include <string>
#include "CSVData.h"

namespace dax {
struct CSVSettings{
	std::string file_name;
	bool headings = false;
	int columns = 1;
};

class ReadCSV {
public:
	static bool fileExists(const std::string& file_name);
	CSVData read(const CSVSettings settings);
private:
};
}
