#include "part.h"
#include "helper_funcs.h"
#include<fstream>
#include<vector>
using std::vector;
using std::ofstream;
using std::ifstream;

// Part

PartsLists::Part::Part(string const& name) {
	this->name = name;
}
string PartsLists::Part::getName() const {
	return name;
}
void PartsLists::Part::setName(string const& s)
{
	name = s;
}
bool PartsLists::Part::equals(Part* const o) const {
	// Normal parts are identified by their name.
	return strcmp(name, o->name)==0;
}

void PartsLists::Part::store(string const& fname) const
{
	// For normal parts one line is sufficient, since they don't have an embedded partslist.
	ofstream out(fname);
	out << 0 << "," << 0 << "," << getName() << std::endl;
}

void PartsLists::Part::load(string const& fname)
{
	// For normal parts reading one line is sufficient since they only carry so much data.
	ifstream in(fname,'w');
	if(in)
	{
		string line;
		std::getline(in, line);
		vector<string> elements(split_string(line, ','));
		if(elements.size()==3)
		{
			name = elements[2];
		}
		else
		{
			std::cout << "Error loading from file. Invalid format.\n";
		}
	}
}

// CompositePart
//Delegate to Part(name)
PartsLists::CompositePart::CompositePart(string const& name) : Part(name) { }

void PartsLists::CompositePart::addPart(Part* const p)
{
	parts.push_back(p);
}

PartsLists::Part::partList PartsLists::CompositePart::getParts() const {
	return parts;
}
PartsLists::Part::partList& PartsLists::CompositePart::getParts() {
	return parts;
}

bool PartsLists::CompositePart::cmpPartList(partList const& pl1, partList const& pl2) const
{
	// If they differ in size, they surely aren't equal.
	if (pl1.size() != pl2.size())
	{
		return false;
	}

	// If they have the same size, we need to check if they contain the same items.
	bool allOk(true);
	size_t id1(0);
	size_t id2(0);
	// We iterate through all parts or til there is a mismatch.
	while(allOk && id1<pl1.size())
	{
		// We check for each item in pl1 if it is present in pl2.
		bool curOkay(false);
		while(!curOkay && id2<pl2.size())
		{
			if (pl1[id1] == nullptr && pl2[id2] == nullptr)
				curOkay = true;
			else if(pl1[id1] != nullptr && pl2[id2] != nullptr)
			{
				PartsLists::CompositePart* cpart1 = dynamic_cast<PartsLists::CompositePart*>(pl1[id1]);
				PartsLists::CompositePart* cpart2 = dynamic_cast<PartsLists::CompositePart*>(pl2[id2]);

				if (cpart1 == nullptr && cpart2 == nullptr && pl1[id1]->equals(pl2[id2]))
					curOkay = true;
				else if (cpart1 != nullptr && cpart2 != nullptr && cmpPartList(cpart1->getParts(), cpart2->getParts()))
					curOkay = true;
			}
			id2++;
		}
		id1++;
		// if we fail to find one item, we set AllOk to false and leave the loop. One item difference = unequal.
		allOk = curOkay;
	}

	return allOk;
}

bool PartsLists::CompositePart::equals(Part* const o) const {
	// CompositeParts are equal, if they have the same name and the same subitems in the partslist.
	PartsLists::CompositePart* cpart = dynamic_cast<PartsLists::CompositePart*>(o);
	if(cpart != nullptr)
	{
		return strcmp(getName(), o->getName())==0 && cmpPartList(getParts(),cpart->getParts());
	}
	else
	{
		return false;
	}
}

void PartsLists::CompositePart::store(string const& fname) const
{
	// To store a compositePart, store the baseItem and iterate recursively through all items.
	ofstream out(fname);
	out << "0,1," << getName() << std::endl;
	storeWorker(out, 1, getParts());
	out.close();
}
void PartsLists::CompositePart::storeWorker(ofstream& out, size_t const level, vector<PartsLists::Part*> const& list) const
{
	for (int i(0); i < list.size(); i++)
	{
		if (list[i] != nullptr)
		{
			// For each item, store the sublevel (how deep it is into the list), the type (part or compositepart/ 0 or 1) and it's name.
			PartsLists::CompositePart* cpart = dynamic_cast<PartsLists::CompositePart*>(list[i]);
			out << level << "," << std::to_string(cpart != nullptr) << "," << list[i]->getName() << std::endl;
			if (cpart != nullptr)
			{
				storeWorker(out, level + 1, cpart->getParts());
			}
		}
	}
}

void PartsLists::CompositePart::load(string const& fname)
{
	// To load it back, delegate to recursive worker.
	ifstream in(fname);
	string currentline("");
	std::getline(in, currentline);
	loadWorker(in, 0, currentline, this);
	in.close();
}
void PartsLists::CompositePart::loadWorker(ifstream& in, size_t const level, string& currentline, Part* p)
{
	while(!currentline.empty())
	{
		// First, split the string from the file into its elements.
		vector<string> elements = split_string(currentline, ',');
		if (elements.size() == 3)
		{
			// If the level fits, save the content.
			if (level == std::stoi(elements[0]))
			{
				if(level == 0)
				{
					this->setName(elements[2]);
					if(std::getline(in,currentline))
					{
						loadWorker(in, level + 1, currentline, p);
					}
				}
				else
				{
					// If it isnt root part, create a new part and save it.
					PartsLists::CompositePart* cpart = dynamic_cast<PartsLists::CompositePart*>(p);
					if(cpart != nullptr)
					{
						// Check if its a part or compositepart and depending on that, save it and recurse.
						if(elements[1][0]=='0')
						{
							Part* newPart = new Part(elements[2]);
							cpart->addPart(newPart);
							if (std::getline(in, currentline))
							{
								loadWorker(in, level, currentline, p);
							}
						}
						else
						{
							CompositePart* newPart = new CompositePart(elements[2]);
							cpart->addPart(newPart);
							if (std::getline(in, currentline))
							{
								loadWorker(in, level+1, currentline, newPart);
							}
						}
					}
				}
			}
			// If the level of the function and the line is unequal, wind out of recursion.
			else
			{
				return;
			}
		}
	}
}