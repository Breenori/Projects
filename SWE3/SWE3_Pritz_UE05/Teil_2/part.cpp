#include "part.h"

bool PartsLists::Part::compareNames(string const& name1, string const& name2) const
{
	if (name1.length() != name2.length())
	{
		return -1;
	}

	string tmp1 = name1;
	string tmp2 = name2;

	for (size_t n(0); n < name.length(); n++)
	{
		tmp1[n] = std::tolower(name1[n]);
		tmp2[n] = std::tolower(name2[n]);
	}

	return tmp1.compare(tmp2) == 0;
}

PartsLists::Part::Part(string name){
	this->name = name;
}

string PartsLists::Part::getName() const {
	return name;
}

bool PartsLists::Part::equals(Part o) const {
	return compareNames(name, o.name);
}

PartsLists::CompositePart::CompositePart(string name) : Part(name) { }
void PartsLists::CompositePart::addPart(Part* const p)
{
	parts.push_back(p);
}

vector<PartsLists::Part*> PartsLists::CompositePart::getParts() const {
	return parts;
}

bool PartsLists::CompositePart::equals(Part o) const {
	PartsLists::CompositePart* cpart = dynamic_cast<PartsLists::CompositePart*>(&o);
	if(cpart != nullptr)
	{
		return compareNames(getName(), o.getName()) && (this->parts.size()==cpart->parts.size());
	}
	else
	{
		return false;
	}
}