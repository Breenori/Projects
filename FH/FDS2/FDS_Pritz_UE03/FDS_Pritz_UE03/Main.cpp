#include "slist.h"
#include<cassert>
//#include <vld.h>

// Multiplies value by 2
void multiply(slist::value_t& value);
// Tests all functions with valid parameters
void valid_test(slist::value_t ex1, slist::value_t ex2);
// Tests all functions for empty lists
void empty_test();
// Tests what happens if a negative index is accessed.
void negative_index_test();
// Tests whether the allocated memory is being freed accordingly
void stack_test();
void stack_test_helper(slist help);


void main()
{
	std::cout << std::endl;
	valid_test(3, 10);
	//empty_test();
	//negative_index_test();
	//stack_test();
	std::cout << std::endl;
}

void multiply(slist::value_t& value)
{
	value *= 2;
}

void valid_test(slist::value_t ex1, slist::value_t ex2)
{
	if (ex1 == ex2)
	{
		ex2 = ex1 + 1;
	}
	slist list;
	list.push_back(ex2);
	list.push_back(ex1);
	// add some random values to show that sorting works later
	list.push_front(13);
	list.push_back(2);
	list.push_back(8);

	list.push_front(ex1);
	list.push_back(ex2);

	slist::value_t v1;
	slist::value_t v2;

	// Judging by the last two pushes and use of back/front, ex1 should be first and ex2 should be last.
	if (list.at(0, v1) && list.at(list.size() - 1, v2))
	{
		assert(v1 == ex1 && v2 == ex2);
	}


	// count should return 2, since I added the parameter ex2 two times and chose the random numbers differently.
	assert(list.count(ex1) == 2);

	slist copy(list);

	// When making a copy, equals should return true
	assert(list.equal(copy));

	std::cout << "List: ";
	list.print();
	std::cout << "Copy: ";
	copy.print();
	std::cout << std::endl;


	list.insert_sorted(6);
	std::cout << "Inserted 6 and sorted: ";
	list.print();
	std::cout << std::endl;

	// Since we changed the list, it should differ from the copy 
	// (making sure that elements have been copied instead of a shared pointer)
	assert(!list.equal(copy));

	list.remove_all(ex1);
	std::cout << "Remove all " << ex1 << "s: ";
	list.print();
	std::cout << std::endl;

	// After deleting all occurences of "ex1"s contains should return false.
	assert(!list.contains(ex1));

	slist half_copy(list);
	list.apply(multiply);
	std::cout << "Applied function: ";
	list.print();
	std::cout << std::endl;


	// Check if every value has been doubled.
	for (int n(0); n < list.size(); n++)
	{
		if (list.at(n, v1) && half_copy.at(n, v2))
		{
			multiply(v2);
			assert(v1 == v2);
		}
	}

	// Check that the right values have been removed and the size has decreased.
	slist::value_t test;
	size_t sizebefore = list.size();
	if (list.at(0, v1) && list.pop_front(test))
	{
		std::cout << "Value from front: " << test << std::endl;
		assert(v1 == test);
		assert(sizebefore == list.size() + 1);
	}

	sizebefore = list.size();
	if (list.at(list.size() - 1, v1) && list.pop_back(test))
	{
		std::cout << "Value from back: " << test << std::endl;
		assert(v1 == test);
		assert(sizebefore == list.size() + 1);
	}

	// Show that values have been removed
	std::cout << "Remaining list: ";
	list.print();

	// After clearing, the list should be empty.
	list.clear();
	assert(list.empty());
}

void empty_test()
{
	slist list;
	list.clear();

	slist::value_t v1;
	list.apply(multiply);
	assert(list.at(list.size() + 1, v1) == false);
	assert(list.contains(1) == false);
	assert(list.count(1) == 0);
	assert(list.empty());
	slist list2(list);
	assert(list.equal(list2));
	list.insert_sorted(5);
	assert(list.contains(5) && list.size() == 1);
	list.clear();
	list.push_back(5);
	assert(list.contains(5) && list.size() == 1);
	list.clear();
	list.push_front(5);
	assert(list.contains(5) && list.size() == 1);
	list.clear();
	assert(list.pop_back(v1) == false);
	assert(list.pop_front(v1) == false);
	assert(list.remove_all(1) == 0);
	assert(list.size() == 0);
	list.print();

}

void negative_index_test()
{
	slist list;
	list.push_back(1);
	slist::value_t v1;
	list.at(-1, v1);
}

void stack_test()
{
	slist list;
	
	for (int i(0); i < 100; i++)
	{
		list.push_back(i);
	}

	for (int i(0); i < 50000; i++)
	{
		stack_test_helper(list);
	}
}

void stack_test_helper(slist help)
{
	slist s(help);
}

