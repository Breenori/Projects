#ifndef point_h
#define point_h
#include<iostream>
using std::cout;

template<typename T>
class Point {

private:
	T val_x;
	T val_y;

public:
	Point() : val_x(T()), val_y(T()) 
	{

	}

	Point(Point<T> const& other)
	{
		val_x(other.val_x);
		val_y(other.val_y);
	}

	Point(T const& x, T const& y) : val_x(x), val_y(y)
	{
		cout << "Instantiating general template: x=" << val_x << ", y=" << val_y << std::endl;
	}

	T& x()
	{
		return val_x;
	}

	T& y()
	{
		return val_y;
	}

	T x() const
	{
		return val_x;
	}

	T y() const
	{
		return val_y;
	}
};

// explicit template specialization for type int
template<>
class Point<int> {
private:
	int val_x;
	int val_y;

public:
	Point() : val_x(0), val_y(0)
	{

	}

	Point(int x, int y) : val_x(x), val_y(y)
	{
		cout << "Instantiating specialization template: x=" << val_x << ", y=" << val_y << std::endl;
	}

	Point(Point<int> const& other)
	{
		val_x = other.val_x;
		val_y =other.val_y;
	}

	int& x()
	{
		return val_x;
	}

	int& y()
	{
		return val_y;
	}

	int x() const
	{
		return val_x;
	}

	int y() const
	{
		return val_y;
	}
};

#endif