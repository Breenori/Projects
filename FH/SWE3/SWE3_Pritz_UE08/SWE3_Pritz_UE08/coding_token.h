#ifndef CODING_TOKEN_H
#define CODING_TOKEN_H
#include<iostream>
#include<fstream>
#include<map>
#include<algorithm>
#include "huffman_list.h"
using std::string;
using std::map;
using std::ifstream;


class CodingToken {
private:
	map<char, double> frequency_table;
	HuffmanList huffl;

	void create_frequency_table(string const& filename)
	{
		ifstream in(filename);
		char c(' ');

		size_t total(0);
		while (in >> c)
		{
			frequency_table[c] ? frequency_table[c] += 1 : frequency_table[c] = 1;
			total++;
		}
		std::for_each(frequency_table.begin(), frequency_table.end(), [total](std::pair<const char, double>& entry) {entry.second = entry.second / total; });

		in.close();
	}
	

public:
	CodingToken() {}
	CodingToken(string const& filename)
	{
		create_frequency_table(filename);
		huffl = HuffmanList(frequency_table);
	}
	//~CodingToken();

	void print_frequency_table()
	{
		std::for_each(frequency_table.begin(), frequency_table.end(), [](std::pair<const char, double>& entry) { std::cout << entry.first << " || " << entry.second << std::endl; });
	}

};

#endif