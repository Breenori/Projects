#ifndef PART_H
#define PART_H

#include<iostream>
#include<string>
#include<vector>
#include "storable.h"
#include<fstream>

using std::string;
using std::cout;
using std::vector;
using std::ofstream;
using std::ifstream;

namespace PartsLists {
	class Part : Storable {
	private:
		string name;
	protected:
		// Set the name to the desired string.
		void setName(string const& s);
	public:
		// Vector of Part-Pointers.
		typedef vector<Part*> partList;
		// Overloaded constructor: name
		Part(string const& name);
		// Returns the name of the part.
		string getName() const;
		// Returns whether or not a part is equal to another.
		virtual bool equals(Part* const o) const;

		// Stores the file to the disk under the designated name.
		void store(string const& fname) const override;
		// Loads the part from a file with the given name.
		void load(string const& fname) override;
	};

	class CompositePart : public Part {
	private:
		partList parts;
		// Stores the file to the disk under the designated name.
		void storeWorker(ofstream& out, size_t const level, vector<PartsLists::Part*> const& list) const;
		// Loads the part from a file with the given name.
		void loadWorker(ifstream& in, size_t const level, string& currentline, Part* p);
	protected:
		// Returns whether or not two partLists are equal
		bool cmpPartList(partList const& pl1, partList const& pl2) const;
	public:
		// Overloaded Constructor: name
		CompositePart(string const& name);
		// Adds a part to the partlist
		void addPart(Part* const p);
		// Returns all subparts.
		partList getParts() const;
		// Returns all subparts (editable)
		partList& getParts();
		// Returns whether or not two Parts/Compositeparts are equal.
		bool equals(Part* const o) const override;
		
		// Stores the current CompositePart to the disk under the designated filename.
		void store(string const& fname) const override;
		// Restores the compositepart from disk using the given file.
		void load(string const& fname) override;
	};
}



#endif
