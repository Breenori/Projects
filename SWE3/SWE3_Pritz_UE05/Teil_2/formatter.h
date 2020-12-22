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
		virtual void printParts(PartsLists::Part const& p) const = 0;
	};

	class SetFormatter : public Formatter {
	private: 
		map<string, size_t> partsSet;
		void buildSet(PartsLists::Part* part);
	public:
		void printParts(PartsLists::Part const& p) const override;
	};
}

#endif