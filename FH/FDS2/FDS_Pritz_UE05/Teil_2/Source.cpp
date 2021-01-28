#include "slist.h"

void main()
{
	// Create a list of 20 elements.
	slist list;
	for (int i(0); i < 10; i++)
	{
		list.push_back(i);
	}


	list.print();
	std::cout << std::endl;

	//list.print_reverse();
	list.reverse();
	list.print();
	std::cout << std::endl;

	// Print the reversed list in a reverse way to get the initial list.
	list.print_reverse();
}