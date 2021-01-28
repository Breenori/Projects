#include "FileManipulator.h"
#include<random>
#include<chrono>
#include<fstream>
using std::chrono::system_clock;
using std::default_random_engine;
using std::uniform_real_distribution;
using std::uniform_int_distribution;

size_t FileManipulator::partition(std::string const& src, std::vector<std::string> const& dst) 
{
	std::ifstream in(src);
	std::vector<std::ofstream*> out;

	//create outputstreams based on input parameter dst
	for (size_t n(0); n < dst.size(); n++)
	{
		out.push_back(new std::ofstream(dst[n]));
	}

	size_t n(0); // amount of total elements. For arithmetic functions (like determining the middle)
	value_type value;

	while (in >> value)
	{
		std::ofstream& outFile = *(out[n % dst.size()]);
		if (outFile)
		{
			outFile << value << " ";
		}
		n++;
	}

	// free the output streams
	for (size_t i(0); i < out.size(); i++)
	{
		delete out[i];
	}

	return n;
}

void FileManipulator::create_random_file(std::string const& filename, size_t const size, value_type const min, value_type const max)
{
	// using the uniform random generator from std lib
	unsigned int seed = system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(min, max);

	std::ofstream out(filename);

	for (size_t n(0); n < size; n++)
	{
		out << distribution(generator) << " ";
	}

	out.close();
}

void FileManipulator::copy(std::string const& src, std::string const& dst)
{
	std::ifstream in(src);
	std::ofstream out(dst);

	// Read and write value by value.
	value_type value(0);
	while (in >> value)
	{
		out << value << " ";
	}

	in.close();
	out.close();
}

void FileManipulator::clean_up(std::vector<std::string> files)
{
	for (size_t i(0); i < files.size(); i++)
	{
		remove(files[i].c_str());
	}
}

void FileManipulator::print(std::string const& filename)
{
	std::ifstream in(filename);
	print(in);
	in.close();
}

void FileManipulator::print(std::ifstream& in)
{
	value_type value(0);
	while (in >> value)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;
}

bool FileManipulator::get_next_value(std::ifstream& in, value_type& value)
{
	if (in >> value)
	{
		return true;
	}
	else
	{
		value = -1;
		return false;
	}
}