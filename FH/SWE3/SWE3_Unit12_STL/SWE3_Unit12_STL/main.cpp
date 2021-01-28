#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<sstream>
#include<functional>
#include<algorithm>

void count_word(std::string const& word, std::map<std::string, std::size_t>& container)
{
	++container[word];
}

void count_char(std::string const& word, std::map<char, std::size_t>& container)
{
	std::for_each(container.begin(), container.end(), [container](std::pair<char, std::size_t> const& p)
		{
			std::cout << p.first << ": " << p.second << std::endl;
		});
}

size_t count_letter(std::string const& word, char const letter)
{
	return std::count(word.begin(), word.end(), letter);
}

void print_character(std::pair<char, std::size_t> const& p)
{
	std::cout << p.first << ": " << p.second << std::endl;
}

void statistics(std::istream& in)
{
	std::string word;
	std::map <std::string, std::size_t> wc; // word count
	std::map<char, std::size_t> cc;

	while (in >> word)
	{
		count_word(word, wc);
	}

	std::cout << "Istream statistics:\n";
	std::for_each(wc.begin(), wc.end(), [](std::pair<std::string, std::size_t> const& p)
		{
			std::cout << p.first << ": " << p.second << std::endl;
		});
	std::cout << "---------------------------\n";

	std::cout << "Character count statistics: \n";
	std::for_each(cc.begin(), cc.end(), print_character);
	std::cout << "---------------------------\n";

	std::size_t sum = 0;
	std::for_each(wc.begin(), wc.end(), [&sum](std::pair<std::string, std::size_t> const& p)
		{
			sum += count_letter(p.first, 'e');
		});
	std::cout << "Anzahl von 'e': " << sum << std::endl;
	std::cout << "---------------------------\n";

	std::vector<size_t> v;
	std::for_each(cc.begin(), cc.end(), [&v](std::pair<char, std::size_t> const& p)
		{
			v.push_back(p.second);
		});


	BiggerThan<std::size_t> bP(2);
	LowerThan<std::size_t> lP(2);
	std::size_t amount = std::count_if(v.begin(), v.end(), bP);
	std::cout << "Elements bigger than > 2: " << amount << "\n";
	std::size_t amount = std::count_if(v.begin(), v.end(), lP);
	std::cout << "Elements lower than < 2: " << amount << "\n";

	std::size_t const less = std::count_if(v.begin(), v.end(), 
		std::bind(std::less<std::size_t>(), std::placeholders::_1, 4)
	);

	std::cout << "Elements lower than 4: " << less << "\n";
}

void main()
{
	std::istringstream in_str{ "seas oida wos geht wos" };
	statistics(in_str);
}
