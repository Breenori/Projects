#ifndef MERGESORT_H
#define MERGESORT_H
#include "FileManipulator.h"

static std::size_t const LEFT = 0;	// Left file
static std::size_t const RIGHT = 1;	// Right file
static std::size_t const NUM_FILES = 2;
static std::size_t const PRINT_THRESHOLD = 50;

class MergeSort {

public:
	// Abbreviation for FileManipulator
	typedef FileManipulator fm;
	typedef int value_type;

	std::string c_wf[NUM_FILES][NUM_FILES]; // c_wf = choose writefile
	bool c_wf_swap;

	MergeSort()
	{
		c_wf_swap = false;
	}

	// Takes the given file, sorts its values and overwrites it.
	void sort(std::string const& filename);

private:
	// Returns the current filename for reading
	std::string const& getSrc(const size_t& i);
	// Returns the current filename for writing
	std::string const& getDst(const size_t& i);
	
	// Merge a partitioned file until it is sorted
	std::string merge(size_t const k, size_t const size);
	// One merge cycle
	void merge_cycle(size_t const size, size_t const run_length, std::ifstream& in_left, std::ifstream& in_right, std::vector<std::ofstream*>& outputs);

	// Swaps between output/input files
	void swap();
};

#endif