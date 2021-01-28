#ifndef MAZE_H
#define MAZE_H
#include<iostream>
#include<vector>

class maze_t {
public:
	typedef int coordinate_t;
	typedef std::pair<coordinate_t, coordinate_t> position_t;
	maze_t();
	~maze_t();
	bool can_escape(position_t const& start);
	std::istream& read(std::istream& in);
	std::ostream& print(std::ostream & out) const;
private:
	typedef position_t dimension_t;
	dimension_t m_dimensions;
	std::vector<std::string> m_maze;
	bool can_escape_worker(position_t const& location, int depth);
	bool is_valid(position_t const& location);
	char& at(position_t const& location);
};

#endif