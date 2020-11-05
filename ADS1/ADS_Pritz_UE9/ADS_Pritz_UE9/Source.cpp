#include "fasta.h"
#include<iostream>
#include<fstream>
using namespace std;

// Reads and returns a positive number with error detection
size_t read_pos_number();
// Returns whether a file exists
bool file_exists(string filename);

void main()
{
	cout << "Which file do you want to read from?\n";
	string in_name;
	getline(cin, in_name); 
	// Repeat input as long as file doesnt exist
	while (!file_exists(in_name))
	{
		cout << "File not found! Please enter valid file: ";
		getline(cin, in_name);
	}

	cout << endl << "What do you want to do?\n";
	cout << "(1) Output the file.\n";
	cout << "(2) Split the file.\n";
	size_t mode(read_pos_number());
	while (mode != 1 && mode != 2)
	{
		cout << "Please select one of the above: ";
		mode = read_pos_number();
	}

	fasta_t fasta;
	if (mode == 1)
	{
		cout << endl << "How many entries do you want to read? (0 = all)\n";
		size_t max(read_pos_number());

		// Everything necessary for initializing was aquired. Commence read.
		initialize(fasta, in_name, max);

		cout << endl << "Where do you want to output the data?\n";
		cout << "(1) Output to file.\n";
		cout << "(2) Output to console.\n";
		size_t dest(read_pos_number());
		while (dest != 1 && dest != 2)
		{
			cout << "Please select one of the above: ";
			dest = read_pos_number();
		}

		if (dest == 1)
		{
			cout << endl << "Please enter the output filename:\n";
			string out_name;
			getline(cin, out_name);

			// Display error if file would be overwritten.
			if (file_exists(out_name))
			{
				cout << "This will overwrite an existing file.\nContinue? (y/n)\n";
				string ans("");
				while (ans != "y" && ans != "n")
				{
					getline(cin, ans);
				}
				if (ans == "n")
				{
					return;
				}
			}

			cout << endl << "Please enter the linelength: (20-255) (enter 0 for default value)\n";
			size_t len(read_pos_number());
			while (len < 20 && len != 0 || len > 255)
			{
				cout << "Please enter a valid number: ";
				len = read_pos_number();
			}
			
			if (len > 0)
			{
				write_to_file(fasta, out_name, len);
			}
			else
			{
				write_to_file(fasta, out_name);
			}
		}
		else
		{
			// Writing everything to console.
			cout << endl;
			write_to_stream(fasta, cout);
		}
	}
	else
	{
		cout << endl << "Please enter the amount of files to split into:\n";
		size_t split_n(read_pos_number());
		while (split_n <= 1 || split_n > 10)
		{
			cout << "Value must at least be between 2 and 10: ";
			split_n = read_pos_number();
		}

		cout << endl << "Please enter the linelength: (20-255) (enter 0 for default value)\n";
		size_t len(read_pos_number());
		while (len < 20 && len != 0 || len > 255)
		{
			cout << "Please enter a valid number: ";
			len = read_pos_number();
		}

		// if len is 0, use default value
		if (len == 0)
		{
			split(in_name, split_n);
		}
		else
		{
			split(in_name, split_n, len);
		}
	}
}

size_t read_pos_number()
{
	size_t val;
	cin >> val;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Please enter a valid number: ";
		cin >> val;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return val;
}

bool file_exists(string filename)
{
	ifstream test(filename);
	bool state(test.good());
	test.close();
	return state;
}
