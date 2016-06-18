#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ReadCSV.h"
#include "StringTools.h"
using namespace dax;

bool ReadCSV::fileExists(const std::string& file_name)
{
	std::ifstream file;
	file.open(file_name);
	return file.is_open();
}

CSVData ReadCSV::read(const CSVSettings settings)
{
	auto&& csv = CSVData();

	auto&& assignHeadings = [](CSVData& csv, const std::vector<SubString>& headings) {
		for (size_t i = 0; i < csv.columns.size(); ++i) {
			if (i >= headings.size()) break;
			else csv.columns[i].title = headings[i].getString();
		}
	};

	auto&& assignValues = [](CSVData& csv, const std::vector<SubString>& values) {
		auto&& column_iter = csv.columns.begin();
		for (auto&& value : values) {
			if (column_iter == csv.columns.end()) column_iter = csv.columns.begin();
			(*column_iter).push_back(std::stod(value.getString(), nullptr));
			++column_iter;
		}
	};

	csv.file_name = settings.file_name;
	std::ifstream file;
	file.open(csv.file_name);
	std::string line;
	if (file.is_open()) {
		if (settings.columns == 0) {
			// get first line to determine number of columns if columns not specified
			std::getline(file, line);
			auto&& sub_strings = StringTools::splitString(line, ',');
			csv.columns.resize(sub_strings.size());
			if (settings.headings)	// assign headings
				assignHeadings(csv, sub_strings);
			else assignValues(csv, sub_strings);
		}
		else {
			csv.columns.resize(settings.columns);
			if (settings.headings) {	// assign headings
				std::getline(file, line);
				auto&& sub_strings = StringTools::splitString(line, ',');
				assignHeadings(csv, sub_strings);
			}
		}
		while (std::getline(file, line)) {
			auto&& sub_strings = StringTools::splitString(line, ',');
			assignValues(csv, sub_strings);
		}
	}
	file.close();
	return csv;
}