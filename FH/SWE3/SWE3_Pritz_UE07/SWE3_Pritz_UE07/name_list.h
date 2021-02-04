#ifndef NAME_LIST_H
#define NAME_LIST_H

#include<map>
#include<iostream>
#include<string>
#include<algorithm>

using std::map;
using std::string;
using std::ostream;

namespace xpr
{
	// forward declaration
	template<typename T>
	class SyntaxTree;

	template<typename T>
	class NameList
	{
	public:
		NameList()
		{

		}
		virtual ~NameList()
		{

		}
		// searches and if found returns the specified identifier in the namelist
		virtual T lookup_variable(string identifier) = 0;
		// adds a new variable to the name_list
		virtual void register_variable(string identifier, T value) = 0;
		// prints all of the variables in the namelist as trees
		virtual void print_name_list(ostream& os) = 0;
	};

	template<typename T>
	class NameListMap : public NameList<T>
	{
	public:
		NameListMap()
		{

		}

		~NameListMap()
		{
			// Delete all variables (syntaxtrees)
			for (auto it = name_list.begin(); it != name_list.end(); ++it)
			{
				delete it->second;
			}
		}

		T lookup_variable(string identifier) override
		{
			return name_list[identifier];
		}

		void register_variable(string identifier, T value) override
		{
			name_list[identifier] = value;
		}

		void print_name_list(ostream& os) override
		{
			std::for_each(name_list.begin(), name_list.end(), [&os](std::pair<std::string, T> dp) { dp.second->print_tree(os,dp.first); });
		}

	private:
		map<string, T> name_list;

	};
}

#endif