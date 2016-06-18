#pragma once
#include <string>
namespace dax {
struct SubString {
	SubString(std::string::const_iterator i_begin, std::string::const_iterator i_end) : _begin(i_begin), _end(i_end) {}
	std::string	getString() const
	{
		return std::string(_begin, _end);
	}
	std::string::const_iterator begin() { return _begin; }
	std::string::const_iterator end() { return _end; }
private:
	std::string::const_iterator _begin;
	std::string::const_iterator _end;
};
}
