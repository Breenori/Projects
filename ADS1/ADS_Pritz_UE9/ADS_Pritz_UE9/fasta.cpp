#include "fasta.h"
#include<fstream>
#include<iostream>


void clear(fasta_t& fasta)
{
	// Clear every entry inside the fasta_t
	for (int i(0); i < fasta.entries.size(); i++)
	{
		clear(fasta.entries[i]);
	}
}

void read_from_file(fasta_t& fasta, string const& name, size_t const max)
{
	// Create stream and delegate to read_from_stream
	ifstream in(name);
	if (in)
	{
		read_from_stream(fasta, in, max);
	}
	else
	{
		cout << "File '" + name + "' couldn't be opened for reading!\n";
	}
	in.close();
	
}

istream& read_from_stream(fasta_t& fasta, istream& in, size_t const max)
{
	state_t state(st_outside);
	fasta_entry_t entry;

	string line;
	size_t entry_counter(0);
	while (getline(in, line) && (entry_counter < max || max == 0))
	{
		// checking the first letter to determine the type of statement
		char c = line.size() > 0 ? line[0] : 0;
		bool is_header = c == '>';
		bool is_comment = c == ';';
		bool is_sequence = is_valid(c);

		switch (state)
		{
		case st_outside:
			// To start an entry, we need its header first which signals the start.
			if (is_header)
			{
				clear(entry);
				entry.header = line.replace(0, 1, "");
				state = st_header;
			}
			break;
		case st_header:
			// After reading a header we can immediately read another header.
			// Push the current entry and start a new one.
			if (is_header)
			{
				fasta.entries.push_back(entry);
				clear(entry);
				entry.header = line.replace(0, 1, "");
				entry_counter++;
			}
			else if (is_comment)
			{
				entry.comments.push_back(line.replace(0, 1, ""));
				state = st_comment;
			}
			else if (is_sequence)
			{
				entry.sequence = line;
				state = st_sequence;
			}
			// If the line is empty or doesn't meet any of the above criteria, we pusht he current entry and jump to st_outside
			else{
				fasta.entries.push_back(entry);
				clear(entry);
				state = st_outside;
				entry_counter++;
			}

			break;
		case st_comment:
			if (is_header)
			{
				fasta.entries.push_back(entry);
				clear(entry);
				entry.header = line.replace(0, 1, "");
				state = st_header;
				entry_counter++;
			}
			else if (is_comment)
			{
				entry.comments.push_back(line.replace(0, 1, ""));
			}
			else if (is_sequence)
			{
				entry.sequence = line;
				state = st_sequence;
			}
			else {
				fasta.entries.push_back(entry);
				clear(entry);
				state = st_outside;
				entry_counter++;
			}
			break;
		case st_sequence:
			if (is_header)
			{
				fasta.entries.push_back(entry);
				clear(entry);
				entry.header = line.replace(0, 1, "");
				state = st_header;
				entry_counter++;
			}
			else if (is_comment)
			{
				entry.comments.push_back(line.replace(0, 1, ""));
				state = st_comment;
			}
			else if (is_sequence)
			{
				entry.sequence += line;
			}
			else {
				fasta.entries.push_back(entry);
				clear(entry);
				state = st_outside;
				entry_counter++;
			}
		}
	}

	return in;
}

void initialize(fasta_t& fasta)
{
	// Without further data there is nothing else to do but clear it.
	clear(fasta);
}

void initialize(fasta_t& fasta, istream& in, size_t const max)
{
	// Delegating to basic initialize and read fasta entries from stream
	initialize(fasta);
	read_from_stream(fasta, in, max);
}

void initialize(fasta_t& fasta, string const& name, size_t const max)
{
	// Creating stream and delegating to initialize with stream
	ifstream in(name);
	initialize(fasta, in, max);
	in.close();
}

void write_to_file(fasta_t const& fasta, string const& name, size_t const len)
{
	// Creating fileoutputstream and delegating to write_to_stream
	ofstream out(name);
	if (out)
	{
		write_to_stream(fasta, out, len);
	}
	else
	{
		cout << "File '" + name + "' couldn't be opened for writing!";
	}
	out.close();
}

ostream& write_to_stream(fasta_t const& fasta, ostream& out, size_t const len)
{
	// Write every single entry of a fasta_t to the designated stream
	for (int i(0); i < fasta.entries.size(); i++)
	{
		write_entry(fasta.entries[i], out, len);
		out << endl;
	}

	return out;
}

void clear(fasta_entry_t& entry)
{
	entry.header = "";
	entry.comments.clear();
	entry.sequence = "";
}

void split(string const& name, size_t const n, size_t const len)
{	
	// First prepare the fasta entries
	fasta_t fasta;
	initialize(fasta, name);
	
	int filecounter(0);
	ofstream out;
	for (int i(0); i < fasta.entries.size(); i++)
	{
		// The initial name mustn't get lost!
		// Altered file name to signal that it has been split and which part it is.
		string split_name = name;
		split_name = split_name.insert(split_name.rfind('.'), "_split-" + to_string(filecounter + 1));
		
		// The first time each file is opened, we use default mode to overwrite so we don't append to existing files.	
		if (i < n)
		{
			out.open(split_name);
		}
		else
		{
			out.open(split_name, ios_base::app);
		}

		if (out)
		{
			write_entry(fasta.entries[i], out, len);
		}
		else if(!out && i < n)
		{
			cout << "File '"+split_name+"' couldn't be opened for writing!\n";
		}

		out.close();

		// Increase and keep filecounter between 0 and n-1
		filecounter = (filecounter + 1) % n;
	}
	
}

bool is_valid(char const c)
{
	return c == 'A' || c == 'T' || c == 'G' || c == 'C';
}

ostream& write_linelen(string const& str, ostream& out, size_t const len, string const& prefix)
{
	if (!str.empty())
	{
		// recalculating the length based on prefix
		// For example, if a comment is 80 characters long, we can still only write 79 chars per line because we need to re-add the semicolon.
		size_t calc_len = len - prefix.length();
		size_t num_lines = str.length() / (calc_len);

		// Then for each line, write all substrings of length "calc_len" preceeded by the prefix
		for (int line_index(0); line_index < num_lines; line_index++)
		{
			if (line_index != num_lines)
			{
				out << prefix << str.substr(line_index * calc_len, calc_len) << endl;
			}
		}
		if (str.length() % calc_len != 0)
		{
			out << prefix << str.substr(num_lines * calc_len, str.length() - num_lines * calc_len) << endl;
		}
	}

	return out;
}

ostream& write_entry(fasta_entry_t const& entry, ostream& out, size_t const len)
{
	// Writing headers multiline would cause a mess (more entries than before, if a header would be longer than len!)
	out << ">" << entry.header << endl;

	// Each comment could be longer than len!
	for (int j(0); j < entry.comments.size(); j++)
	{
		write_linelen(entry.comments[j], out, len, ";");
	}

	// Write sequence as multiple lines of length len.
	write_linelen(entry.sequence, out, len);

	return out;
}

