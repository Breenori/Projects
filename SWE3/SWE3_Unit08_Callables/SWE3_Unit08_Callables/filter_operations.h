#ifndef filter_operations_h
#define filter_operations_h

#include<vector>
#include<functional>
#include<string>
#include "car.h"

using std::string;
using std::vector;

namespace filter_ops
{
	// Functor! --> Overloads () operator. Type secure function pointer!
	class ColorPredicate
	{
	private:
		string _color;
	public:
		ColorPredicate(string color) : _color(color) {}

		bool operator() (Car const& other) const {
			return _color == other.get_color();
		}
	};

	// Version 1: naiive approach to combine algorithms and containers
	void filter_color(vector<Car*>& cars, string const& color)
	{
		vector<Car*>::iterator it = cars.begin();
		while (it != cars.end())
		{
			if ((*it)->get_color() == color)
			{
				it = cars.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	typedef bool(*fun_t) (string);
	// Version 2: better approach using function pointer
	void filter_color(vector<Car*>& cars, fun_t const& fn)
	{
		vector<Car*>::iterator it = cars.begin();
		while (it != cars.end())
		{
			if (fn( (*it)->get_color() ) )
			{
				it = cars.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	// Version 3: Use functor
	void filter_color(vector<Car*>& cars, ColorPredicate const & pr)
	{
		vector<Car*>::iterator it = cars.begin();
		while (it != cars.end())
		{
			if ( pr(**it))
			{
				it = cars.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	typedef bool (*lambda_t) (Car&);
	void filter_color(vector<Car*>& cars, lambda_t const& lambda)
	{
		vector<Car*>::iterator it = cars.begin();
		while (it != cars.end())
		{
			if (lambda(**it))
			{
				it = cars.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

}

#endif