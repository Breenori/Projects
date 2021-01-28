#include "slist.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<windows.h>

HANDLE find_first_file(std::string& dir, WIN32_FIND_DATA& ffd);
std::string to_string(WCHAR* cstring);
bool find_next_file(HANDLE hFind, WIN32_FIND_DATA& ffd);
int list_directory(std::string& dir, int indent, std::ostream& out);

void main()
{
	std::string dir("D:");
	//std::string dir(".");
	std::ofstream out("out.txt");
	list_directory(dir, 0, std::cout);
}

int list_directory(std::string& dir, int indent, std::ostream& out)
{
	WIN32_FIND_DATA ffd;
	HANDLE hFind = 0;

	dir += "\\*";

	hFind = find_first_file(dir, ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		out << "ERROR invalid directory: " << dir << "\n";
		return GetLastError();
	}

	bool next_file_found(true);
	while (next_file_found)
	{
		std::string total_file_name = dir.substr(0, dir.size()-1) + to_string(ffd.cFileName);
		std::string display_name = to_string(ffd.cFileName);

		if (total_file_name[total_file_name.size() - 1] != '.')
		{
			out << std::setw(indent * 2) << " ";

			if (ffd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				out << total_file_name << " <DIR>\n";
				list_directory(total_file_name, indent + 1, out);
			}
			else
			{
				out << display_name << " (" << ffd.nFileSizeLow << " b)\n";
			}
		}

		next_file_found = find_next_file(hFind, ffd);
	}

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		out << "ERROR!";
		return GetLastError();
	}

	// List all the files with some info about them
	FindClose(hFind);
	return 0;
}

HANDLE find_first_file(std::string& dir, WIN32_FIND_DATA& ffd) {
	std::wstring stemp = std::wstring(dir.begin(), dir.end());
	LPCWSTR _dir = stemp.c_str();

	return FindFirstFile(_dir, &ffd);
}

std::string to_string(WCHAR* cstring) {
	std::string str;
	int i = 0;
	while (cstring[i] != 0) {
		str += cstring[i];
		++i;
	}
	return str;
}

bool find_next_file(HANDLE hFind, WIN32_FIND_DATA& ffd) {
	int i = FindNextFile(hFind, &ffd);
	return (i > 0);
}