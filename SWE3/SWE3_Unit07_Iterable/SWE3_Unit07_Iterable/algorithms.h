#ifndef algorithms_h
#define algorithms_h

#include "iterable.h"
#include<iostream>

using std::cout;

namespace algorithms
{
	template<typename I, typename V> void print(Iterable<I, V> const& container)
	{
		I it(container.begin());
		while (it != container.end())
		{
			cout << container.get(it) << " ";
			container.next(it);
		}
		cout << "\n";
	}

	template<typename I, typename V> V sum(Iterable<I, V> const& container)
	{
		V s(0);
		I it(container.begin());
		while (it != container.end())
		{
			s += container.get(it);
			container.next(it);
		}
		cout << "\n";
	}
}

#endif