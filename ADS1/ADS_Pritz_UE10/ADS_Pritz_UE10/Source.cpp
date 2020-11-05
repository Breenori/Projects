#include<iostream>
#include<string>
#include<fstream>
#include "stack_machine.h"
using namespace std;

// Read expression from file
string get_expression(string name);
// Removes all whitespaces from a given string
void remove_whitespaces(string& str);

void main()
{
	cout << "Please enter the filename containing the expression: ";
	string filename;
	getline(cin, filename);
	string expression(get_expression(filename));
	cout << "\n";

	if (!empty(expression))
	{
		remove_whitespaces(expression);
		cout << "The entered expression is: \n" + expression << endl << endl;

		cout << "Result: " << evaluate(expression);
	}
	else
	{
		cout << "The given expression is empty.";
	}
}

string get_expression(string name)
{
	string exp("");
	string line("");
	ifstream in(name);
	if (in)
	{
		while (getline(in, line))
		{
			exp += line;
		}
	}
	else
	{
		cout << "ERROR! File couldn't be read.\n";
	}
	return exp;
}

void remove_whitespaces(string& str)
{
	while (str.find(' ', 0) != string::npos)
	{
		str.replace(str.find(' ', 0), 1, "");
	}
}