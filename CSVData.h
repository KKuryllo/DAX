#pragma once
#include <string>
#include <vector>
#include "Column.h"
#include "Line2.h"

namespace dax {
struct CSVData {
	CSVData(){}
	CSVData(std::string ifile_name) : file_name(ifile_name){}
	std::string file_name;
	std::vector<Column> columns;
	void add(const Line2& line)
	{
		columns.resize(columns.size() + 2);
		for (auto&& vec : line) {
			(*(columns.end() - 2)).push_back(vec.x);
			(*(columns.end() - 1)).push_back(vec.y);
		}
		(*(columns.end() - 2)).title = line.x_title;
		(*(columns.end() - 1)).title = line.y_title;
	}
	inline void add(const Column& column)
	{
		columns.push_back(column);
	}
	inline void add(const std::vector<Column>& cont)
	{
		for (auto&& sub : cont)
			add(sub);
	}
	template<typename array_type>
	inline void add(const std::vector<array_type>& conts)
	{
		for (auto&& cont : conts) {
			Column new_column;
			new_column.resize(cont.size());
			for (size_t i = 0; i < cont.size(); i++)
				new_column[i] = cont[i];
			columns.push_back(new_column);
		}
	}
	template<int array_size>
	inline void add(const std::array<double, array_size> container)
	{
		columns.push_back({ container });
	}
	template<typename container_type>
	inline void add(const container_type& container)
	{
		for (auto&& column : container) {
			columns.push_back(column);
		}
	}
};
}
