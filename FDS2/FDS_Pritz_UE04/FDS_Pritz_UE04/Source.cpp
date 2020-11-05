#include<vector>
#include<iostream>
using std::vector;
using std::cout;

// global variable for troubleshooting and testing scenarios.
// To show the amount of permutations for testcases.
size_t AMOUNT(0);

// Prints all possible permutations of the given vector.
void permute(vector<int> vec);
// Prints the given vector.
void print_vector(vector<int> const& vec);
// Helper function for permute().
void permute_wrapper(vector<int> vec, size_t const start);

void main()
{
	vector<int> test = { 1,3,3};
	cout << "Start: ";
	print_vector(test);
	cout << std::endl;
	permute(test);
}

void print_vector(vector<int> const& vec)
{
	cout << AMOUNT ++ << "{";
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
void permute(vector<int> vec)
{
	// Delegates to the wrapper function, starting with index 0.
	permute_wrapper(vec, 0);
}
void permute_wrapper(vector<int> vec, size_t const start)
{
	// If the floor is reached (index greater than size) we unwind and print the vector.
	if (start >= vec.size())
	{
		print_vector(vec);
	}
	else
	{
		// Swap the index with every possible option (every index after start)
		// Then call the wrapper with the altered vector
		// And finally: swap the values back.
		for (int i(start); i < vec.size(); i++)
		{
			std::swap(vec[start], vec[i]);
			permute_wrapper(vec, start + 1);
			std::swap(vec[start], vec[i]);
		}
	}
}