#pragma once
#include "Column.h"
namespace dax {
struct ColumnRef {
	ColumnRef(const std::vector<double>::const_iterator i_begin, const std::vector<double>::const_iterator i_end) : _begin(i_begin), _end(i_end) {}
	ColumnRef(){}
	inline std::vector<double>::const_iterator begin() const
	{
		return _begin;
	}
	inline std::vector<double>::const_iterator end() const
	{
		return _end;
	}
	inline size_t size() const
	{
		return _end - _begin;
	}
	inline double interpolateAt(const double val) const
	{
		auto&& start = _begin + size_t(val);
		auto&& prop = std::fmod(val, 1.0f);
		return  *start + (*(start + 1) - *start) * prop;
	}
	inline const double& operator[](const size_t position) const
	{
		return *(_begin + position);
	}
private:
	std::vector<double>::const_iterator _begin;
	std::vector<double>::const_iterator _end;
};
}
