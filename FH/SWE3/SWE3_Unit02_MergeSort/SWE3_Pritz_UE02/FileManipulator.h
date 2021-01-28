#ifndef FILEMANIPULATOR_H
#define FILEMANIPULATOR_H
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

class FileManipulator {

public:
	typedef int value_type;

	// Writes the next value from <in> into <value>. Returns whether it was successful or not.
	static bool get_next_value(std::ifstream& in, value_type& value);

	// Splits a file in two.
	static size_t partition(std::string const& src, std::vector<std::string> const& dst);
	// Creates a file with random numbers
	static void create_random_file(std::string const& filename, size_t const size, value_type const min, value_type const max);
	
	// Prints a file one number after another.
	static void print(std::string const& filename);
	// Prints a file one number after another using an inputstream.
	static void print(std::ifstream& in);
	
	// Copies the content of one file to another.
	// Caution: Overwrites files
	static void copy(std::string const& src, std::string const& dst);

	// Deletes all specified files
	static void clean_up(std::vector<std::string> files);
};

#endif