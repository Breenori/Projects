#include "maze.h"

bool maze_t::can_escape(position_t const& start)
{
	return can_escape_worker(start, 0);
}

bool maze_t::can_escape_worker(position_t const& location, int depth)
{
	coordinate_t x(location.first);
	coordinate_t y(location.second);
	coordinate_t w(m_dimensions.first);
	coordinate_t h(m_dimensions.second);
	// is loc within maze?
	bool is_free(is_valid(location));
	// on wall?
	bool is_border((x == 0) || (y == 0) || (x == w - 1) || (y == h - 1));
	// is it free?
	if (is_border && is_free)
	{
		//wooohooo... exit!
		m_maze[x][y] = 'X';
		return true;
	}
	else if (is_free)
	{
		
		m_maze[x][y] = depth == 0 ? 'S' : '.';	
		//recursive call
		return	can_escape_worker(position_t(x - 1, y), depth + 1) ||
				can_escape_worker(position_t(x + 1, y), depth + 1) ||
				can_escape_worker(position_t(x, y - 1), depth + 1) ||
				can_escape_worker(position_t(x, y + 1), depth + 1);
	}
	else
	{
		return false;
	}
	// on free cell?
		//exit?
		// if not: check up, right, left, down
	
}

bool maze_t::is_valid(position_t const& location)
{
	int x = location.first;
	int y = location.second;
	int w = m_dimensions.first;
	int h = m_dimensions.second;

	if (x < w && x >= 0 && y < h && y >= 0)
	{
		return x < w && y < h;
	}

}
