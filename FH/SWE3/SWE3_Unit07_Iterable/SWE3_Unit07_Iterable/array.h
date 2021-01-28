#ifndef array_h
#define array_h

#include<vector>
#include "Iterable.h"

template<typename T>
class Array : public Iterable<T*, T>
{
public:
	typedef typename Iterable<T*, T>::iter_t iter_t;
	typedef typename Iterable<T*, T>::value_t value_t;

	Array(const std::vector<T>& v) : p_data(new T[v.size()]), _size(v.size())
	{
		int i(0);
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			p_data[i++] = *it;
		}
	}

	~Array()
	{
		delete[] p_data;
	}

	iter_t begin() const override
	{
		return p_data;
	}
	iter_t end() const override
	{
		return p_data + _size;
	}

	value_t& get(iter_t it) override
	{
		return *it;
	}

	value_t const get(iter_t it) const override
	{
		return *it;
	}

	void next(iter_t& it) const override
	{
		++it;
	}

private:
	size_t _size;
	value_t* p_data;
};

#endif