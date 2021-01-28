#include "MergeSort.h"
#include<vector>
#include<fstream>

void MergeSort::sort(std::string const& filename)
{
	size_t k(1);
	std::vector<std::string> src;
	src.push_back(getSrc(LEFT));
	src.push_back(getSrc(RIGHT));

	// 1) partition
	size_t const n(fm::partition(filename, src));
	
	if (n > 0)
	{
		// 2) merge
		std::string sorted_filename(merge(k, n));

		// 3) copy result in source file
		if (n < PRINT_THRESHOLD)
		{
			std::cout << sorted_filename << ":\n";
			fm::print(sorted_filename);
		}
		else
		{
			std::cout << "Printing has been skipped due to large amount of data.\n";
		}
		fm::copy(sorted_filename, filename);
	}
	else
	{
		std::cout << "Nothing to do here, no elements found. Cleaning up...\n";
	}
	
	// Remove all temporary files
	fm::clean_up({ getSrc(LEFT) ,getDst(LEFT) ,getSrc(RIGHT) ,getDst(RIGHT) });
}

std::string MergeSort::merge(size_t const run_length, size_t const size)
{
	// If run_length greater or equal the amount of total datasets, stop recursion and return filename.
	// Using size here, because we always handle run_length * 2 variables and therefor have twice as many as per file.
	if (run_length >= size)
	{
		swap();
		return getDst(LEFT);
	}
	else
	{
		// Create all necessary input and output streams
		std::ifstream in_left(getSrc(LEFT));
		std::ifstream in_right(getSrc(RIGHT));

		std::vector<std::ofstream*> outputs;
		outputs.push_back(new std::ofstream(getDst(LEFT)));
		outputs.push_back(new std::ofstream(getDst(RIGHT)));

		merge_cycle(size, run_length, in_left, in_right, outputs);
		if (size <= PRINT_THRESHOLD)
		{
			std::cout << getSrc(LEFT) << ": \n";
			fm::print(getSrc(LEFT));
			std::cout << getSrc(RIGHT) << ": \n";
			fm::print(getSrc(RIGHT));
			std::cout << "\n";
		}

		// After one merging process, close all the filestreams.
		in_left.close();
		in_right.close();
		for (size_t n(0); n < outputs.size(); n++)
		{
			delete outputs[n];
		}

		// After one merging process, swap the input/output files and follow recursion with double run_length
		swap();
		return merge(run_length * 2, size);
	}
}

void MergeSort::merge_cycle(size_t const size, size_t const run_length, std::ifstream& in_left, std::ifstream& in_right, std::vector<std::ofstream*>& outputs)
{
	// Define a variable to easily switch between outputstreams
	size_t stream_index(1);

	// These two variables are used to store the current dataset (e.g, the first uncompared number in the file) for each file
	value_type i1(-1);
	value_type i2(-1);

	// When reading from the file, it could happen that one file has no more values.Hence we can check whether or not the number is valid later.
	bool ok1(fm::get_next_value(in_left, i1));
	bool ok2(fm::get_next_value(in_right, i2));

	// In every run only "k" numbers can be read from each file. Therefor we count how often we read from each file.
	size_t amount1(0);
	size_t amount2(0);

	// Merging process (we write one element per cycle, hence we need <size> cycles)
	for (size_t n(0); n < size; n++)
	{
		// Change the output file after k run_length and reset read amounts
		if (n % (run_length * NUM_FILES) == 0)
		{
			stream_index = (stream_index + 1) % NUM_FILES;

			amount1 = 0;
			amount2 = 0;
		}

		// In case we have already written too many entries from one file, always write the other number.
		if (amount1 == run_length && ok2)
		{
			*outputs[stream_index] << i2 << " ";
			ok2 = fm::get_next_value(in_right, i2);
		}
		else if (amount2 == run_length && ok1)
		{
			*outputs[stream_index] << i1 << " ";
			ok1 = fm::get_next_value(in_left, i1);
		}
		else
		{
			// If input from both files could potentially be taken (based on amount), check if they're valid...
			if (ok1 && ok2)
			{
				// ...and compare them
				if (i1 <= i2)
				{
					*outputs[stream_index] << i1 << " ";

					// Upon writing one number to the file, we need to increase the amount counter and read the next number
					amount1++;
					ok1 = fm::get_next_value(in_left, i1);
				}
				else
				{
					*outputs[stream_index] << i2 << " ";
					amount2++;
					ok2 = fm::get_next_value(in_right, i2);
				}
			}
			// If one of the numbers couldn't be read, take the other one.
			else if (!ok1)
			{
				*outputs[stream_index] << i2 << " ";
				ok2 = fm::get_next_value(in_right, i2);
			}
			else if (!ok2)
			{
				*outputs[stream_index] << i1 << " ";
				ok1 = fm::get_next_value(in_right, i2);
			}
		}
	}
}

std::string const& MergeSort::getSrc(const size_t& i)
{
	return c_wf[c_wf_swap ? RIGHT : LEFT][i];
}
std::string const& MergeSort::getDst(const size_t& i)
{
	return c_wf[c_wf_swap ? LEFT : RIGHT][i];
}

void MergeSort::swap()
{
	c_wf_swap = !c_wf_swap;
}

