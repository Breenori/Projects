#if !defined FASTA_H
#define FASTA_H
#include<vector>
#include<string>
using namespace std;

enum state_t {st_outside, st_header, st_sequence, st_comment};

struct fasta_entry_t {
	string header;
	string sequence;
	vector<string> comments;
};

struct fasta_t {
	vector<fasta_entry_t> entries;
};

// Clears all entries inside the fasta_t
void clear(fasta_t& fasta);
// Reads  fasta entries from the specified file and stores them inside the specified fasta struct
void read_from_file(fasta_t& fasta, string const& name, size_t const max = 0);
// Reads the given fasta entries from the specified input stream and stores them in the fasta struct.
// A value of "0" for max removes the max-limit.
// Returns reference to the used istream
istream& read_from_stream(fasta_t& fasta, istream& in, size_t const max = 0);
// Initializes the fasta file by clearing its entries.
void initialize(fasta_t& fasta);
// Initializes the fasta file by reading the entries using a stream.
void initialize(fasta_t& fasta, istream& in, size_t const max = 0);
// Initializes the fasta file by reading the entries using a filename.
void initialize(fasta_t& fasta, string const& name, size_t const max = 0);
// Writes the given fasta entries to a file with the specified name.
// Line length is limited by "len".
void write_to_file(fasta_t const& fasta, string const& name, size_t const len = 80);
// Writes the given fasta entries to the specified stream.
// Line length is limited by "len".
// Returns reference to the used ostream
ostream& write_to_stream(fasta_t const& fasta, ostream& out, size_t const len = 80);
// Removes all the values from a given fasta entry.
void clear(fasta_entry_t& entry);
// Reads a given fasta file, creates a fasta struct and splits the fasta entries to n files.
void split(string const& name, size_t const n = 2, size_t const len = 80);
// Returns whether a char is dNTP
bool is_valid(char const c);
// Takes a string and prints it on several lines, based on linelength.
// Returns reference to the used ostream
ostream& write_linelen(string const& str, ostream& out, size_t const len = 80, string const& prefix = "");
// Writes out the content of a fasta entry to the specified stream.
// Returns reference to the used ostream
ostream& write_entry(fasta_entry_t const& entry, ostream& out, size_t const len = 80);
#endif
