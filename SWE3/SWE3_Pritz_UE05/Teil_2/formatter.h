#ifndef FORMATTER_H
#define FORMATTER_H
#include "part.h"
#include<vector>
#include<map>
using std::map;
using std::vector;

namespace formatting {
	class Formatter {
	public:
		virtual void printParts(PartsLists::Part* const p) const = 0;
	};

	class SetFormatter : public Formatter {
	private:
		// Creates a map to output for printparts
		void buildSet(PartsLists::Part* const part, std::map<string, size_t>& partsSet) const;
	public:
		// Prints the amount of each part. Only counts leafs.
		void printParts(PartsLists::Part* const p) const override;
	};

	class HierarchyFormatter : public Formatter {
	private:
		// Recursive worker for printparts.
		void printPartsWorker(PartsLists::Part* const p, size_t const indent) const;
	public:
		// Prints each part as a hierarchy.
		void printParts(PartsLists::Part* const p) const override;
	};
}

#endif