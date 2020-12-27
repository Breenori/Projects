#include "formatter.h"
#include "part.h"

void formatting::SetFormatter::buildSet(PartsLists::Part* const part, std::map<string,size_t>& partsSet) const
{
	if (part != nullptr)
	{
		
		PartsLists::CompositePart* cpart = dynamic_cast<PartsLists::CompositePart*>(part);
		if (cpart != nullptr)
		{
			PartsLists::Part::partList subparts(cpart->getParts());

			// Iterate through all parts in the list
			for (int i(0); i < subparts.size(); i++)
			{
				if (subparts[i] != nullptr)
				{
					bool isCpart = dynamic_cast<PartsLists::CompositePart*>(subparts[i]) != nullptr;
					if (isCpart)
					{
						// recurse
						buildSet(subparts[i], partsSet);
					}
					else
					{
						string name = subparts[i]->getName();
						partsSet[name] ? partsSet[name]++ : partsSet[name] = 1;
					}
				}
			}
		}
	}
	else
	{
		std::cout << "Invalid part specified.\n";
	}
}

void formatting::SetFormatter::printParts(PartsLists::Part* const p) const
{	
	if (p != nullptr)
	{
		// First build a map/set
		std::map<string, size_t> partsSet;
		buildSet(p, partsSet);
		// Then iterate through it and print each item with its amount.
		std::cout << p->getName() << ":" << std::endl;
		for (auto it(partsSet.begin()); it != partsSet.end(); ++it)
		{
			std::cout << "\t" << it->second << " " << it->first << std::endl;
		}
		std::cout << std::endl;
		partsSet.clear();
	}
	else
	{
		std::cout << "Invalid part specified.\n";
	}
}

void formatting::HierarchyFormatter::printParts(PartsLists::Part* const p) const
{
	if(p != nullptr)
	{
		// To create a hierarchy, recursively iterate through the partslist and instantly output each part.
		std::cout << p->getName() << std::endl;
		printPartsWorker(p, 1);
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Invalid part specified.\n";
	}
}

void formatting::HierarchyFormatter::printPartsWorker(PartsLists::Part* const p, size_t const indent) const
{
	if (p != nullptr)
	{
		// Try to cast to a compositepart
		PartsLists::CompositePart* cpart = dynamic_cast<PartsLists::CompositePart*>(p);
		if (cpart != nullptr)
		{
			//
			PartsLists::Part::partList subparts = cpart->getParts();
			for (int i(0); i < subparts.size(); i++)
			{
				if (subparts[i] != nullptr)
				{
					for (size_t in(0); in < indent; in++)
					{
						std::cout << "\t";
					}
					std::cout << subparts[i]->getName() << std::endl;
					printPartsWorker(subparts[i], indent + 1);
				}
			}
		}
	}
	else
	{
		std::cout << "Invalid part specified.\n";
	}
}
