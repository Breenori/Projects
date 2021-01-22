#ifndef NAME_LIST_H
#define NAME_LIST_H

#include<map>
#include<iostream>
#include<string>

using std::map;
using std::string;
using std::ostream;

namespace xpr
{
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
		virtual T lookup_variable(string identifier) = 0;
		virtual void register_variable(string identifier, T value) = 0;
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
			// TODO
		}

	private:
		map<string, T> name_list;

	};
}

#endif