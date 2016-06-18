#pragma once
#include <array>
#include <vector>
namespace dax {
struct Column {
public:
	Column(){}
	Column(const std::string ititle)
	{
		title = ititle;
	}
	template<int array_size>
	Column(const std::array<double, array_size>& container)
	{
		data.resize(container.size());
		for (size_t i = 0; i < container.size(); i++)
			data[i] = container[i];
	}
	inline std::vector<double>::const_iterator begin() const
	{
		return data.begin();
	}
	inline std::vector<double>::const_iterator end() const
	{
		return data.end();
	}
	inline std::vector<double>::iterator begin()
	{
		return data.begin();
	}
	inline std::vector<double>::iterator end()
	{
		return data.end();
	}
	inline void push_back(const double _value)
	{
		data.push_back(_value);
	}
	inline void resize(const size_t _size)
	{
		data.resize(_size);
	}
	inline const double& operator[](const size_t _position) const
	{
		return data[_position];
	}
	inline double& operator[](const size_t _position)
	{
		return data[_position];
	}
	inline size_t size() const
	{
		return data.size();
	}
	inline double interpolateAt(const double val) const
	{
		auto&& start = data.begin() + size_t(val);
		auto&& prop = std::fmod(val, 1.0f);
		return  *start + (*(start + 1) - *start) * prop;
	}
	inline double average()
	{
		if (data.empty()) return 0.0;
		auto&& sum = 0.0;
		for (auto&& val : data)
			sum += val;
		sum /= data.size();
		return sum;
	}
	std::string title;
private:
	std::vector<double> data;
};
}
