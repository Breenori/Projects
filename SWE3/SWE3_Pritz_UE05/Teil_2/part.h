#ifndef PART_H
#define PART_H

#include<iostream>
#include<string>
#include<vector>

using std::string;
using std::cout;
using std::vector;

namespace PartsLists {
	class Part {
	private:
		string name;
	protected:
		bool compareNames(string const& name1, string const& name2) const;
	public:
		Part(string name);
		string getName() const;
		virtual bool equals(Part o) const;
	};

	class CompositePart : public Part {
	private:
		vector<Part*> parts;
	public:
		CompositePart(string name);
		void addPart(Part * const P);
		vector<Part*> getParts() const;
		bool equals(Part o) const override;
	};
}



#endif
