#ifndef operations_h
#define operations_h

namespace operations {

	template<typename T>
	T abs(T x) {
		cout << "abs<T>():";
		return x < 0 ? -x : x;
	}


	template<typename S>
	Point<S> negate(Point<S> const& p)
	{
		cout << "negate<Point<T>>(): ";
		return Point<S>(p.x() * -1, p.y() * -1);
	}

}

#endif