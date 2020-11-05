#include<iostream>
#include<vector>
#include<time.h>
#include "pfc-mini.hpp"
using std::cout;
using std::vector;

// Normally global variables should not be used
// However, since we can't pass the size/repeats because of the limitations of pfc.hpp timed_run, this is necessary.
size_t SIZE_OF_VECTOR(3000);

// Shuffles the values of an array
// Since i had several ideas for wrappers, i included a version as parameter to compare them for efficiency.
void random_shuffle(vector<int>& vec, size_t const version = 0);
// Shuffle Wrapper 1. <index> is being passed as reference so we avoid copying from/to stack.
void random_shuffle_wrapper_v1(vector<int>& vec, size_t & index);
// Shuffle Wrapper 2. <index> is being passed by value so it gets copied and therefor should be slower. 
void random_shuffle_wrapper_v2(vector<int>& vec, size_t index);
// Shuffle wrapper 3. <index> passed by value and max depth is halved by swapping 4 values instead of 2 per cycle.
void random_shuffle_wrapper_v3(vector<int>& vec, size_t index);
// Prints a vector
void print_vector(vector<int> const& vec);
// Creates a vector of size <n> by initialized it with [i]=i
void create_vec(vector<int>& v, size_t const n);

// Test if the algorithm works as intended.
void test_functionality();
// Calls all the testfunctions and prints their runtime.
void test_efficiency(size_t const repeats);
// Calls random_shuffle version 1.
// Used for measuring time.
void test1();
// Calls random_shuffle version 2.
// Used for measuring time.
void test2();
// Calls random_shuffle version 3.
// Used for measuring time.
void test3();



void main()
{
	srand(time(0));
	test_functionality();
	//test_efficiency(500);
}

void random_shuffle(vector<int>& vec, size_t const version)
{
	if (version == 0)
	{
		size_t start_index(0);
		random_shuffle_wrapper_v1(vec, start_index);
	}
	else if (version == 1)
	{
		random_shuffle_wrapper_v2(vec, 0);
	}
	else if (version == 2)
	{
		random_shuffle_wrapper_v3(vec, 0);
	}
}

void random_shuffle_wrapper_v1(vector<int>& vec, size_t & index)
{
	// Every index is being replaced with another.
	if (index < vec.size())
	{
		std::swap(vec[index], vec[rand() % vec.size()]);
		// Index is given via reference, so we can just add it up here.
		index++;
		random_shuffle_wrapper_v1(vec, index);
	}
}
void random_shuffle_wrapper_v2(vector<int>& vec, size_t index)
{
	// Similiar to v2, but without index as reference.
	if (index < vec.size())
	{
		std::swap(vec[index], vec[rand() % vec.size()]);
		random_shuffle_wrapper_v2(vec, index + 1);
	}
}
void random_shuffle_wrapper_v3(vector<int>& vec, size_t index)
{
	// Only iterate through half the vector, but swap two values every iteration.
	if (index < (vec.size()+1)/2)
	{
		std::swap(vec[index], vec[rand() % vec.size()]);
		std::swap(vec[vec.size()-1-index], vec[rand() % vec.size()]);
		random_shuffle_wrapper_v3(vec, index+1);
	}
}

void print_vector(vector<int> const& vec)
{
	cout << "{";
	for (size_t i(0); i < vec.size(); i++)
	{
		if (i > 0)
		{
			cout << ", ";
		}
		cout << vec[i];
	}
	cout << "}\n";
}
void create_vec(vector<int>& v, size_t const n)
{
	for (int i(0); i < n; i++)
	{
		v.push_back(i);
	}
}

void test_efficiency(size_t const repeats)
{
	// Calculate the total of needed time for each version of the shuffle.
	double sum1(0);
	double sum2(0);
	double sum3(0);
	for (int i(0); i < repeats; i++)
	{
		sum1 += pfc::in_s(pfc::timed_run(test1));
		sum2 += pfc::in_s(pfc::timed_run(test2));
		sum3 += pfc::in_s(pfc::timed_run(test3));
	}

	// Get the average for each.
	cout << (sum1 / repeats) << std::endl;
	cout << (sum2 / repeats) << std::endl;
	cout << (sum3 / repeats) << std::endl;
}
void test1()
{
	vector<int> test;
	create_vec(test, SIZE_OF_VECTOR);
	random_shuffle(test, 0);
}
void test2()
{
	vector<int> test;
	create_vec(test, SIZE_OF_VECTOR);
	random_shuffle(test, 1);
}
void test3()
{
	vector<int> test;
	create_vec(test, SIZE_OF_VECTOR);
	random_shuffle(test, 2);
}

void test_functionality()
{
	vector<int> showcase;

	create_vec(showcase, 10);
	random_shuffle(showcase, 0);
	print_vector(showcase);
	showcase.clear();

	create_vec(showcase, 10);
	random_shuffle(showcase, 1);
	print_vector(showcase);
	showcase.clear();

	create_vec(showcase, 10);
	random_shuffle(showcase, 2);
	print_vector(showcase);
}
