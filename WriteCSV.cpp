#include "stdafx.h"
#include "WriteCSV.h"
#include <iostream>
#include <fstream>
using namespace dax;
namespace _write_csv_stuff {
void writeHeaders(std::ofstream& file, const CSVData& data)
{
	for (size_t i = 0; i < data.columns.size() - 1; ++i)
		file << data.columns[i].title << ',';
	file << (*(data.columns.end() - 1)).title << "\n";  // line end character for last line instead of ,
}
}
using namespace _write_csv_stuff;

bool WriteCSV::write(const CSVData& data)
{
	// create file
	std::ofstream file;
	file.open(data.file_name);
	// write headers if any exist
	for (auto&& column : data.columns) {
		if (!column.title.empty()) {
			writeHeaders(file, data);
			break;
		}
	}
	// determine the number of rows
	size_t max_rows = 0;
	for (auto&& column : data.columns)
		if (column.size() > max_rows) max_rows = column.size();
	// write all rows
	for (size_t i = 0; i < max_rows; ++i) {
		for (size_t j = 0; j < data.columns.size() - 1; ++j) {
			if (i < data.columns[j].size())	// if data exists for this column write it
				file << data.columns[j][i] << ',';
			else file << ','; // else write a blank
		}
		// do once more for last column
		if (i < (*(data.columns.end() -1)).size())	// if data exists for this column write it
			file << (*(data.columns.end() - 1))[i] << "\n";
		else file << "\n"; // else write a blank
	}
	file.close();
	return true;
}