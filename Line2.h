#pragma once
#include <vector>
#include "Vec2.h"
#include "Column.h"

namespace dax {
struct Line2 {
public:
	Line2() {}
	Line2(std::vector<double>::const_iterator& x_begin, std::vector<double>::const_iterator& x_end,
		std::vector<double>::const_iterator& y_begin, std::vector<double>::const_iterator& y_end)
	{
		data.resize(x_end - x_begin);
		auto&& x_current = x_begin;
		auto&& y_current = y_begin;
		auto&& vec_iter = data.begin();
		while (y_current != y_end && vec_iter != data.end()) {
			*vec_iter = { *x_current, *y_current };
			++x_current;
			++y_current;
			++vec_iter;
		}
	}
	Line2(const Column& x_vals, const Column& y_vals)
	{
		auto&& size = x_vals.size() >= y_vals.size() ? x_vals.size() : y_vals.size();
		data.resize(size);
		auto&& x_current = x_vals.begin();
		auto&& y_current = y_vals.begin();
		auto&& vec_iter = data.begin();
		while (vec_iter != data.end()) {
			*vec_iter = { *x_current, *y_current };
			++x_current;
			++y_current;
			++vec_iter;
		}
	}
	template<typename line_type>
	Line2(const line_type line)
	{
		data.resize(line.size());
		for (size_t i = 0; i < data.size(); ++i)
			data[i] = line[i];
	}
	Line2& operator/=(const double scalar)
	{
		for (auto&& val : data)
			val /= scalar;
		return *this;
	}
	inline const std::vector<Vec2>::const_iterator begin() const
	{
		return data.begin();
	}
	inline std::vector<Vec2>::iterator begin()
	{
		return data.begin();
	}
	inline const std::vector<Vec2>::const_iterator end() const
	{
		return data.end();
	}
	inline std::vector<Vec2>::iterator end()
	{
		return data.end();
	}
	inline const Vec2& operator[](const size_t i) const
	{
		return data[i];
	}
	inline Vec2& operator[](const size_t i)
	{
		return data[i];
	}
	inline void resize(const size_t new_size)
	{
		data.resize(new_size);
	}
	inline size_t size() const
	{
		return data.size();
	}
	inline Vec2 interpolateAt(const double val) const
	{
		auto&& start = size_t(val);
		auto&& prop = std::fmod(val, 1.0f);
		return data[start] + (data[start + 1] - data[start]) * prop;
	}
	inline void name(const std::string x_t, const std::string y_t)
	{
		x_title = x_t;
		y_title = y_t;
	}
	inline void push_back(const Vec2& point)
	{
		data.push_back(point);
	}
	std::string x_title;
	std::string y_title;
private:
	std::vector<Vec2> data; // finish
};
}
