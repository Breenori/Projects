#include "MergeSort.h"
#include "FileManipulator.h"
#include<iostream>

int main()
{
	std::string const test1("empty.txt");
	std::string const test2("reference.txt");
	std::string const test3("uneven.txt");
	std::string const test4("negative.txt");
	std::string const test5("random_big.txt");
	std::string const test6("strings.txt");
	FileManipulator::create_random_file(test5, 1000000, -1000000, 1000000);

	// Initialize mergesort
	MergeSort ms = MergeSort();
	ms.c_wf[0][0] = "f0.txt";
	ms.c_wf[0][1] = "f1.txt";
	ms.c_wf[1][0] = "g0.txt";
	ms.c_wf[1][1] = "g1.txt";

	

	ms.sort(test1);
	//ms.sort(test2);
	//ms.sort(test3);
	//ms.sort(test4);
	//ms.sort(test5);
	//ms.sort(test6);

	return 0;
}