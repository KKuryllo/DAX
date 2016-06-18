#pragma once
namespace dax {
template<typename ContainerType>
class ContainerRef {
public:
	ContainerRef(ContainerType& container) : data(&container){}
	inline typename ContainerType::const_iterator begin() const
	{
		return data->begin();
	}
	inline typename ContainerType::const_iterator end() const
	{
		return data->end();
	}
	inline const typename ContainerType::value_type& operator[](const size_t position) const
	{
		return *(data->begin() + position);
	}
private:
	ContainerType* data;
};
}