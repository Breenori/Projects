#include "maze.h"
#include<regex>
#include<fstream>
#include<windows.h>
#include<thread>
#include<chrono>
#include<cassert>
using std::string;

maze_t::maze_t()
{
	// Set the default values for the maze.
	clear();
}

maze_t::maze_t(std::string const& filename) : maze_t()
{
	// Create input filestream and read maze from it.
	std::ifstream in(filename);
	read(in);
	in.close();
}

maze_t::~maze_t()
{
	// Upon call, just clear the maze.
	// Is a deconstructor actually necessary? Since we aren't using dynamically allocated memory...
	clear();
}


bool maze_t::can_escape(position_t const& start)
{
	// Only simulate if the maze has been initialized correctly.
	if (initialized)
	{
		if (is_free(start))
		{
			return can_escape_worker(start, 0);
		}
		else
		{
			std::cout << "Position outside of boundaries or inside wall. Aborting...\n";
			return false;
		}
	}
	// Else we print a warning.
	else
	{
		std::cout << "Warning: No maze is loaded! Please read in a file first!\n";
		return false;
	}
}

void maze_t::enable_animation(bool const setting)
{
	this->animated = setting;
}

std::istream& maze_t::read(std::istream& in)
{

	if (in)
	{
		// First, read the first two lines and check if they are numeric using regex.
		std::regex num("^[0-9]+$");
		string width;
		string height;
		if (!getline(in, width))
		{
			return in;
		}
		if (!getline(in, height))
		{
			return in;
		}

		
		if (std::regex_match(width, num) && std::regex_match(height, num))
		{
			// If they are indeed numeric, we convert them to integers and set them as the dimensions.
			m_dimensions.first = std::stoi(width);
			m_dimensions.second = std::stoi(height);

			bool okay(true);

			// Read all remaining lines (or until error) and add them to the maze matrix.
			string line;
			while (getline(in, line) && okay)
			{
				if (line.size() == m_dimensions.first)
				{
					// For better visibility, we swap all stars (walls) for the ascii char 219, which is a solid block.
					for (int j(0); j < line.size(); j++)
					{
						if (line[j] == '*')
						{
							line[j] = (char)219;
						}
					}
					m_maze.push_back(line);
				}
				else
				{
					okay = false;
				}
			}

			// If the matrix doesn't meet the specified dimension requirements initialization is being aborted and the values reset to default.
			if (!okay || m_dimensions.second != m_maze.size())
			{
				std::cout << "Error: Dimension mismatch. Aborting...\n";
				clear();
				return in;
			}

			initialized = true;
		}
	}
	else
	{
		std::cout << "Error: Read failure!\n";
	}
	return in;
}

std::ostream& maze_t::print(std::ostream& out) const
{
	if (out)
	{
		// Just print every line
		for (int i(0); i < m_dimensions.second; i++)
		{
			out << m_maze[i] << std::endl;
		}
	}
	else
	{
		std::cout << "Error: Write failure!\n";
	}
	return out;
}

bool maze_t::can_escape_worker(position_t const& location, int depth)
{
	// Save values for easier access.
	coordinate_t x(location.first);
	coordinate_t y(location.second);
	coordinate_t w(m_dimensions.first);
	coordinate_t h(m_dimensions.second);
	// Precompute whether the location is on a free block and inside the boundaries.
	bool is_free(is_free(location));
	// Calculate whether the location is already on the outer boundaries.
	bool is_border((x == 0) || (y == 0) || (x == w - 1) || (y == h - 1));
	// If the location near the border AND on a free spot has been reached, it's possible to escape.
	if (is_border && is_free)
	{
		// Exit has been found. Set X and print the resulting maze and path.
		m_maze[y][x] = 'X';
		return true;
	}
	// If the location is free but not on the border, we have to do some work.
	else if (is_free)
	{
		// First, mark the current position (S for start, . for any other location after that)
		m_maze[y][x] = depth == 0 ? 'S' : '.';

		// If animation is enabled, print matrix for every new move.
		if (animated)
		{
			system("cls");
			print(std::cout);
			std::chrono::milliseconds timespan(50);
			std::this_thread::sleep_for(timespan);
		}

		// Search in all directions! First left, then right, then up, then down.
		return	can_escape_worker(position_t(x - 1, y), depth + 1) ||
			can_escape_worker(position_t(x + 1, y), depth + 1) ||
			can_escape_worker(position_t(x, y - 1), depth + 1) ||
			can_escape_worker(position_t(x, y + 1), depth + 1);
	}
	else
	{
		// If location can't reach exit or is blocked, return false.
		return false;
	}

}

bool maze_t::is_valid(position_t const& location)
{
	int x = location.first;
	int y = location.second;
	int w = m_dimensions.first;
	int h = m_dimensions.second;

	// Check whether x and y are inside the boundaries
	if (x < w && x >= 0 && y < h && y >= 0)
	{
		return true;
	}
	return false;
}

bool maze_t::is_free(position_t const& location)
{
	int x = location.first;
	int y = location.second;
	if (is_valid(location))
	{
		// Check whether the location is free.
		return m_maze[y][x] == ' ';
	}
	return false;
}

char& maze_t::at(position_t const& location)
{
	// Get modulo for values to make sure we return a reference to a location inside the maze.
	int x = location.first % m_dimensions.first;
	int y = location.second % m_dimensions.second;

	if (!is_valid(location))
	{
		assert("Index out of bounds!" && false);
	}

	return m_maze[y][x];
}

void maze_t::clear()
{
	m_maze.clear();
	m_dimensions = { 0,0 };
	initialized = false;
	animated = false;
}
