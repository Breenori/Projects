#include<iostream>
#include<vector>
#include<map>
#include<string>

using std::vector;
using std::map;
using std::cout;
using std::string;

void test_vector_iterator()
{
	// Declaring vector
	vector<int> v = { 5, 7, 21, 13, 37 };
	vector<int>::iterator i;

	for (i = v.begin(); i != v.end(); ++i)
	{
		if (*i == 7)
		{
			v.erase(i);
		}
		else
		{
			cout << *i << " ";
		}
	}
	cout << std::endl;

}

void main()
{
	//test basxic usage of an iterator
	test_vector_iterator();
}