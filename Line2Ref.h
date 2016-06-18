#pragma once
#include "Line2.h"
namespace dax {
struct Line2Ref {
	Line2Ref(const std::vector<Vec2>::const_iterator i_begin, const std::vector<Vec2>::const_iterator i_end) : _begin(i_begin), _end(i_end) {}
	inline std::vector<Vec2>::const_iterator begin() const
	{
		return _begin;
	}
	inline std::vector<Vec2>::const_iterator end() const
	{
		return _end;
	}
	inline size_t size() const
	{
		return _end - _begin;
	}
	inline Vec2 interpolateAt(const double val) const
	{
		auto&& start = _begin + size_t(val);
		auto&& prop = std::fmod(val, 1.0f);
		return  *start + (*(start + 1) - *start) * prop;
	}
	inline const Vec2& operator[](const size_t position) const
	{
		return *(_begin + position);
	}
private:
	std::vector<Vec2>::const_iterator _begin;
	std::vector<Vec2>::const_iterator _end;
};
}
