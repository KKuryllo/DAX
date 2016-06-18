#pragma once
#include <array>
#include <cmath>
#include "Line2.h"
#include "Line2Ref.h"
#include "Line.h"
#include "ColumnRef.h"

namespace dax {
inline size_t averageDifference(const std::vector<size_t> nums)
{
	size_t sum = 0;
	for (size_t i = 1; i < nums.size(); ++i)
		sum += nums[i] - nums[i - 1];
	return sum / (nums.size() - 1);
}
template<int columns, typename ContainerType>
inline size_t averageDifference(const ContainerType& segments)
{
	size_t sum = 0;
	for (auto&& segment : segments) {
		sum += segment[0].size();
	}
	return sum / (segments.size());
}
template<typename container_type>
inline container_type absoluteDifference(const container_type& cont1, const container_type& cont2)
{
	container_type result = cont1;
	for (size_t i = 0; i < cont1.size(); i++) {
		result[i] = std::fabs(cont1[i] - cont2[i]);
	}
	return result;
}
inline Line2 movingAverage(const Line2& line, const size_t displacement)
{
	// Generate a new line of the same size as the input line
	auto&& average_line = Line2();
	average_line.resize(line.size());

	// Loop through all points in the line to calculate thier averages
	for (size_t i = 0; i < average_line.size(); ++i) {
		// Determine start point and end point for average calculation
		size_t start, end;			// End is 1 past last
		if (i < displacement)
			start = i;
		else start = i - displacement;
		if (i + displacement > average_line.size() - 1)
			end = average_line.size();
		else end = i + displacement + 1;
		// Sum all points between start - end
		auto&& sum = Vec2(0.0, 0.0);
		for (size_t j = start; j < end; ++j)
			sum += line[j];
		// Calculate average
		average_line[i] = sum / double(end - start);
	}
	return average_line;
}
template<int columns>
inline std::vector<std::array<ColumnRef, columns>> getSegments(const std::vector<Column>& line, std::vector<size_t>& positions)
{
	std::vector<std::array<ColumnRef, columns>> segments;
	for (size_t i = 1; i < positions.size(); ++i) {
		std::array<ColumnRef, columns> refs;	
		for (size_t j = 0; j < refs.size(); j++) {
			auto&& column = line[j];
			refs[j] = { column.begin() + positions[i - 1], column.begin() + positions[i] };
		}
		segments.push_back(refs);
	}
	return segments;
}

template<int num_columns, typename container_type>
inline std::array<Column, num_columns> averageSegments(const container_type& segments, size_t num_points = 0)
{
	// if num points specified use it otherwise determine average and use that instead
	if (num_points == 0)
		num_points = dax::averageDifference<num_columns>(segments);

	std::array<Column, num_columns> averages;
	for (auto&& ave : averages)
		ave.resize(num_points);

	// Go one column at a time
	for (size_t j = 0; j < num_columns; j++) {
		auto&& col = averages[j];
		// sum all movement points at simulary progressions
		for (size_t i = 0; i < num_points; i++) {
			double prop = double(i) / double(num_points);
			for (auto&& segmentRefs : segments) {
				auto&& segment = segmentRefs[j];
				auto&& movement_pos = prop * double(segment.size() - 1);
				col[i] += segment.interpolateAt(movement_pos);
			}
		}
		// divide to get average
		for (size_t i = 0; i < num_points; i++)
			col[i] /= segments.size();
	}
	return averages;
}

inline std::vector<size_t> getMinimumIndexs(const Column& line, const size_t spread = 1)
{
	std::vector<size_t> mins;
	size_t min_pos = 0;
	double last = line[0];
	size_t spread_count = 0;
	bool has_min = true;
	for (size_t i = 1; i < line.size(); ++i) {
		if (has_min) {
			if (line[i] < line[min_pos]) {
				min_pos = i;
				spread_count = 0;
			}
			else if (line[i] > line[min_pos]) {
				++spread_count;
				if (spread_count >= spread) {
					has_min = false;
					mins.push_back(min_pos);
					spread_count = 0;
				}
			}
		}
		else {
			if (line[i] < last) {
				++spread_count;
				if (spread_count >= spread) {
					has_min = true;
					min_pos = i;
					spread_count = 0;
				}
			}
			else spread_count = 0;
		}
		last = line[i];
	}
	if (has_min) mins.push_back(min_pos);
	return mins;
}

inline std::vector<size_t> getMaximumIndexs(const Column& line, const size_t spread = 1)
{
	std::vector<size_t> maxs;
	size_t max_pos = 0;
	double last = line[0];
	size_t spread_count = 0;
	bool has_max = true;
	for (size_t i = 1; i < line.size(); ++i) {
		if (has_max) {
			if (line[i] > line[max_pos]) {
				max_pos = i;
				spread_count = 0;
			} else if (line[i] < line[max_pos]) {
				++spread_count;
				if (spread_count >= spread) {
					has_max = false;
					maxs.push_back(max_pos);
					spread_count = 0;
				}
			}
		} else {
			if (line[i] > last) {
				++spread_count;
				if (spread_count >= spread) {
					has_max = true;
					max_pos = i;
					spread_count = 0;
				}
			} else spread_count = 0;
		}
		last = line[i];
	}
	if (has_max) maxs.push_back(max_pos);
	return maxs;
}

inline Column getMinimumValues(const Column& line, const size_t spread = 1)
{
	Column mins;
	size_t min_pos = 0;
	double last = line[0];
	size_t spread_count = 0;
	bool has_min = true;
	for (size_t i = 1; i < line.size(); ++i) {
		if (has_min) {
			if (line[i] < line[min_pos]) {
				min_pos = i;
				spread_count = 0;
			} else if (line[i] > line[min_pos]) {
				++spread_count;
				if (spread_count >= spread) {
					has_min = false;
					mins.push_back(line[min_pos]);
					spread_count = 0;
				}
			}
		} else {
			if (line[i] < last) {
				++spread_count;
				if (spread_count >= spread) {
					has_min = true;
					min_pos = i;
					spread_count = 0;
				}
			} else spread_count = 0;
		}
		last = line[i];
	}
	if (has_min) mins.push_back(line[min_pos]);
	return mins;
}

inline Column getMaximumValues(const Column& line, const size_t spread = 1)
{
	Column maxs;
	size_t max_pos = 0;
	double last = line[0];
	size_t spread_count = 0;
	bool has_max = true;
	for (size_t i = 1; i < line.size(); ++i) {
		if (has_max) {
			if (line[i] > line[max_pos]) {
				max_pos = i;
				spread_count = 0;
			} else if (line[i] < line[max_pos]) {
				++spread_count;
				if (spread_count >= spread) {
					has_max = false;
					maxs.push_back(line[max_pos]);
					spread_count = 0;
				}
			}
		} else {
			if (line[i] > last) {
				++spread_count;
				if (spread_count >= spread) {
					has_max = true;
					max_pos = i;
					spread_count = 0;
				}
			} else spread_count = 0;
		}
		last = line[i];
	}
	if (has_max) maxs.push_back(line[max_pos]);
	return maxs;
}

template<int num_columns, typename container_type>
inline std::array<double, num_columns> average(const container_type& line)
{
	std::array<double, num_columns> sums{};
	for (size_t i = 0; i < num_columns; i++) {
		auto&& sum = sums[i];
		auto&& column = line[i];
		for (auto&& point : column){
			sum += point;
		}
		sum /= double(column.size());
	}
	return sums;
}
template<typename container_type>
inline double distance(const container_type& first, const container_type& second)
{
	double sum = 0;
	for (size_t i = 0; i < first.size(); i++) {
		auto&& diff = second[i] - first[i];
		sum += diff * diff;
	}
	return std::sqrt(sum);
}
template<typename line_type1, typename line_type2>
inline std::array<double, std::tuple_size<line_type1>::value> averageDistance(const line_type1& line1c, const line_type2& line2c)
{
	std::array<double, std::tuple_size<line_type1>::value> sums{};
	for (size_t i = 0; i < std::tuple_size<line_type1>::value; i++) {
		auto&& line1 = line1c[i];
		auto&& line2 = line2c[i];
		auto&& sum = sums[i];
		// sum all movement points at simulary progressions
		for (size_t j = 0; j < line2.size(); ++j) {
			double prop = double(j) / double(line2.size());
			auto&& movement_pos = prop * double(line1.size() - 1);
			sum += std::fabs(line1.interpolateAt(movement_pos) - line2[j]);
		}
		sum /= double(line2.size());
	}
	return sums;
}
template<typename line_type>
inline Line2 translate(const line_type& line, const Vec2 displacment)
{
	Line2 new_line = line;
	for (auto&& point : new_line)
		point += displacment;
	return new_line;
}
template<typename column_container, typename distance_container>
inline std::array<Column, std::tuple_size<distance_container>::value> negTranslate(const column_container& lines, const distance_container& displacments)
{
	std::array<Column, std::tuple_size<distance_container>::value> outputs;
	{
		for (size_t i = 0; i < std::tuple_size<distance_container>::value; i++) {
			auto&& output = outputs[i];
			auto&& line = lines[i];
			auto&& displacment = displacments[i];
			output.resize(line.size());
			for (size_t j = 0; j < output.size(); ++j)
				output[j] = line[j] - displacment;
		}
	}
	return outputs;
}
template<typename array_type>
inline std::array<Column, std::tuple_size<array_type>::value> transpose(const std::vector<array_type>& container)
{
	std::array<Column, std::tuple_size<array_type>::value> t_d;
	for (auto&& column : t_d)
		column.resize(container.size());
	for (size_t i = 0; i < container.size(); i++) {
		for (size_t j = 0; j < std::tuple_size<array_type>::value; j++)
			t_d[j][i] = container[i][j];
	}
	return t_d;
}
inline Column rangeProportion(const Column& column, const std::pair<double, double>& min_max)
{
	Column output;
	output.resize(column.size());
	double diff = min_max.second - min_max.first;
	for (size_t i = 0; i < column.size(); i++)
		output[i] = (column[i] - min_max.first) / diff;
	return output;
}
}
