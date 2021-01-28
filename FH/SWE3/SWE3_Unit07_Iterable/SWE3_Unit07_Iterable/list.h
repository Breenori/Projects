#ifndef list_h
#define list_h

#include<vector>
#include "iterable.h"

template<typename T> struct node_t
{
	typedef T value_t;

	value_t p_data;
	node_t* p_next;
};

template<typename T> class List : public Iterable<node_t<T>*, T>
{
public:
	typedef typename Iterable<node_t<T>*, T>::iter_t iter_t;
	typedef typename Iterable<node_t<T>*, T>::value_t value_t;

	List(const std::vector<T> v) : _size(v.size()), p_head(nullptr)
	{
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			node_t<value_t>* const p(new node_t<value_t>);
			p->p_data = *it;
			p->p_next = p_head;
			p_head = p; // prepend elements
		}
	}

	virtual ~List()
	{
		while (p_head != nullptr)
		{
			node_t<value_t>* const p(p_head);
			p_head = p_head->p_next;
			delete p;
		}
	}

	iter_t begin() const override
	{
		return p_head;
	}

	iter_t end() const override
	{
		return nullptr;
	}

	value_t& get(iter_t it) override
	{
		return it.p_data;
	}
	value_t const get(iter_t it) const override
	{
		return it.p_data;
	}

	void next(iter_t& it) const override
	{
		i = i->p_next;
	}

	std::size_t size() const
	{
		return _size;
	}

private:
	size_t size;
	node_t<value_t>* p_head;
};

#endif