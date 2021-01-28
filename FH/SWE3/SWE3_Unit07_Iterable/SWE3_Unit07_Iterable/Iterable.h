#ifndef ITERABLE_H
#define ITERABLE_H

template<typename T, typename U>
struct Iterable
{
	typedef T iter_t;
	typedef U value_t;

	virtual iter_t begin() const = 0;
	virtual iter_t end() const = 0;
	virtual value_t& get(iter_t it) = 0;
	virtual value_t const get(iter_t it) = 0 const;
	virtual void next(iter_t& it) = 0 const;
};

#endif