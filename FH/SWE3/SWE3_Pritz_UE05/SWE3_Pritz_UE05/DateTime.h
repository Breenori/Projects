#ifndef DATETIME_H
#define DATETIME_H
#include<iostream>
#include<string>
#include<regex>
#include<time.h>
using std::ostream;

using std::string;
using std::to_string;

class DateTime {
private:
	struct tm ti;

	std::vector<int>months = { 31,//January
		59,//February
		90, //March 31
		120,//April 30
		151,//May 31
		181,//June 30
		212,//July 31
		243,//August 31
		273, //September 30
		304,//October 31
		334,//November 30
		365//December 31
	};
	bool isDiff;

	void strtodate(string const& datestr)
	{
		std::regex date_regex("^([0-9][0-9]?)[ .]([0-9][0-9]?)[ .]([0-9][0-9]|[0-9][0-9][0-9][0-9]) ([0-9][0-9]?)[:]([0-9][0-9]?)[:]([0-9][0-9]?)");
		std::smatch matches;

		if (std::regex_search(datestr, matches, date_regex) && matches.size()==7)
		{
			ti.tm_mday = std::stoi(matches[1].str());
			ti.tm_mon = std::stoi(matches[2].str())-1;
			string yearStr = matches[3].str();
			if (yearStr.length() == 2)
			{
				yearStr = "20" + yearStr;
			}
			ti.tm_year = std::stoi(yearStr)-1900;
			ti.tm_hour = std::stoi(matches[4].str());
			ti.tm_min = std::stoi(matches[5].str());
			ti.tm_sec = std::stoi(matches[6].str());
		}
		else
		{
			std::cout << "Error parsing date.\n";
			*this = DateTime();
		}
	}
	string formatdd(short const num) const
	{
		if (num < 10)
		{
			return "0" + to_string(num);
		}
		return to_string(num);
	}


public:
	friend ostream& operator<<(ostream& lhs, DateTime const& rhs);
	
	DateTime()
	{
		std::time_t t = std::time(0);
		gmtime_s(&ti, &t);
		isDiff = false;
	}
	DateTime(short const day, short const month, short const year, short const hour, short const min, short const sec)
	{
		struct tm tmp;
		tmp.tm_mday = day;
		tmp.tm_mon = month - 1;
		tmp.tm_year = year - 1900;
		tmp.tm_hour = hour;
		tmp.tm_min = min;
		tmp.tm_sec = sec;
		if (mktime(&tmp) == -1)
		{
			std::cout << "Invalid date given.\n";
			*this = DateTime();
		}
		ti = tmp;
		isDiff = false;
	}

	DateTime(string const& s)
	{
		strtodate(s);
	}

	string toStr() const
	{
		return isDiff ? std::to_string(ti.tm_mday) + " days, " + std::to_string(ti.tm_hour) + " hours, " + std::to_string(ti.tm_min) + " minutes, " + std::to_string(ti.tm_sec) + " seconds" : (formatdd(ti.tm_mday) + "." + formatdd(ti.tm_mon+1) + "." + to_string(ti.tm_year+1900) + " " + formatdd(ti.tm_hour) + ":" + formatdd(ti.tm_min) + ":" + formatdd(ti.tm_sec));
	}

	static DateTime diff(DateTime& time1, DateTime& time2)
	{
		DateTime tmp = DateTime();

		int seconds = std::abs(mktime(&(time1.ti)) - mktime(&(time2.ti)));
		tmp.ti.tm_sec = seconds % 60;
		tmp.ti.tm_min = (seconds / 60) % 60;
		tmp.ti.tm_hour = (seconds / 60 / 60) % 24;
		tmp.ti.tm_mday = (seconds / 60 / 60 / 24);
		tmp.isDiff = true;

		return tmp;
	}

	
};

ostream& operator<<(ostream& lhs, DateTime const& rhs)
{
	lhs << rhs.toStr();
	return lhs;
}
#endif