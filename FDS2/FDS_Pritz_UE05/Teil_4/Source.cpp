#include<iostream>
#include<fstream>
#include<iomanip>
#include<windows.h>

// Returns a FileHandler for the first file in the specified directory <dir>
HANDLE find_first_file(std::string& dir, WIN32_FIND_DATA& ffd);
// Converts a WCHAR carray to a std::string
std::string to_string(WCHAR* cstring);
// Sets the FileHandler to the next file. Returns true if another file has been found, false if it was the last fíle.
bool find_next_file(HANDLE hFind, WIN32_FIND_DATA& ffd);
// Prints all files in the folders and recursively in subfolders and returns the error code.
int list_directory(std::string& dir, int indent, std::ostream& out);

void main()
{
	std::string dir("C:\\tmp");
	std::ofstream out("out.txt");
	list_directory(dir, 0, out);
	out.close();
}

int list_directory(std::string& dir, int indent, std::ostream& out)
{
	if (!out)
	{
		std::cout << "Error -1: The specified outputstream is invalid. \n";
		return -1;
	}
	// Define windows.h module datatypes for file handling
	// ffd is the utility used to aquire FileHandles and hFind is the actualy FileHandle
	WIN32_FIND_DATA ffd;
	HANDLE hFind = 0;

	// Add wildcard to specify that we want ALL files and directories in the given path.
	dir += "\\*";

	// Find first file and get its filehandle. If not possible, throw error.
	// For example on a nonexisting path.
	hFind = find_first_file(dir, ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		out << "ERROR invalid directory: " << dir << "\n";
		return GetLastError();
	}

	// Then, repeat following process for the file and its successors.
	bool next_file_found(true);
	while (next_file_found)
	{
		// Extract filename and full path from ffd.
		std::string total_file_name = dir.substr(0, dir.size() - 1) + to_string(ffd.cFileName);
		std::string display_name = to_string(ffd.cFileName);

		// Files aren't allowed to end in ".". Only print for proper files.
		if (total_file_name[total_file_name.size() - 1] != '.')
		{
			// For folder structure: Print blanks to create indentation (more subfolders = more indents)
			out << std::setw(indent * 2) << " ";

			// If it is a directory, print its name and recursively repeat the process.
			if (ffd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				out << total_file_name << " <DIR>\n";
				list_directory(total_file_name, indent + 1, out);
			}
			else
			{
				// if its just a file, print its name and the size in bytes.
				out << display_name << " (" << ffd.nFileSizeLow << " b)\n";
			}
		}

		// Check if next file exists and initialize the handle.
		next_file_found = find_next_file(hFind, ffd);
	}

	// If theres an error (that isn't "no more files") print error and return the code.
	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		out << "ERROR!";
		return GetLastError();
	}

	// Close the filehandle
	FindClose(hFind);
	// Return zero if successful
	return 0;
}

HANDLE find_first_file(std::string& dir, WIN32_FIND_DATA& ffd) {
	// Convert wstring to LPCWString used for finding filehandles.
	std::wstring stemp = std::wstring(dir.begin(), dir.end());
	LPCWSTR _dir = stemp.c_str();

	return FindFirstFile(_dir, &ffd);
}

std::string to_string(WCHAR* cstring) {
	std::string str;
	int i = 0;
	// copy cstring to string char by char
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