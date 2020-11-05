#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using std::vector;
using std::string;
using std::swap;
using std::endl;
using std::cout;
using std::ifstream;
using std::getline;

void read_from_file(vector<string const*>& vec, string const filename = "test.txt");
void sort_indirect(vector<string const*> & vec);
int str_cmp_indirect(string const* str1, string const* str2);
void print_all(vector<string const*> vec);

void main()
{
	vector<string const*> strings;
	read_from_file(strings);
	sort_indirect(strings);
	print_all(strings);
}

void read_from_file(vector<string const*>& vec, string const filename)
{
	ifstream in(filename);

	if (in)
	{
		string line("");
		while (getline(in, line))
		{
			string* s = new string;
			*s = line;
			vec.push_back(s);
		}
	}

	in.close();
}
void sort_indirect(vector<string const*> & vec)
{
	if (vec.empty())
	{
		return;
	}

	for (int i(0); i < vec.size() - 1; i++)
	{
		int smallest = i;
		for (int j(i+1); j < vec.size(); j++)
		{
			if (str_cmp_indirect(vec[j], vec[smallest]) < 0)
			{
				smallest = j;
			}
		}

		if (smallest != i)
		{
			swap(vec[smallest], vec[i]);
		}
	}
} 
int str_cmp_indirect(string const* str1, string const* str2)
{
	if (str1 == nullptr && str2 == nullptr)
	{
		return 0;
	}
	else if (str1 == nullptr)
	{
		return -1;
	}
	else if (str2 == nullptr)
	{
		return 1;
	}

	size_t str1len = (*str1).length();
	size_t str2len = (*str2).length();
	size_t counter(0);
	int state(0);
	while (counter < str1len && counter < str2len && state == 0)
	{
		if (toupper((*str1)[counter]) < toupper((*str2)[counter]))
		{
			state = -1;
		}
		else if (toupper((*str1)[counter]) > toupper((*str2)[counter]))
		{
			state = 1;
		}
		counter++;
	}

	if (state == 0 && str1len < str2len)
	{
		state = -1;
	}
	else if (state == 0 && str1len > str2len)
	{
		state = 1;
	}

	return state;
}
void print_all(vector<string const*> vec)
{
	for (int i(0); i < vec.size(); i++)
	{
		cout << *(vec[i]) << endl;
	}

	if (vec.empty())
	{
		cout << "The input file was empty.";
	}
}