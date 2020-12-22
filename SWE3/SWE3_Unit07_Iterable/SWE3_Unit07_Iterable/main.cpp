#include<iostream>
#include<vector>
#include "array.h"
#include "list.h"
#include "algorithms.h"


using std::cout;
using std::string;
using std::vector;
using std::vector;

int main()
{
	// Version 1
	//Array<int> a({ 1,2,3,4,5,6,7,8,9,10 });
	//Array<int>::iter_t it;

	// Version 2
	List<int> a({ 1,2,3,4,5,6,7,8,9,10 });
	List<int>::iter_t it;

	for (it = a.begin(); it != a.end(); a.next(it))
	{
		cout << a.get(it) << " ";
	}
	cout << std::endl;

	vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	Array<int> arr(v);
	List<int> lis(v);

	cout << "samples for iterator-based algorithms:\n";
	cout << " - Array: ";
	algorithms::print(arr);
	cout << " - List: ";
	algorithms::print(lis);
	cout << " - sum in Array: " << algorithms::sum(arr) << "\n";
	cout << " - sum in Liste: " << algorithms::sum(lis) << "\n";

	return 0;
}