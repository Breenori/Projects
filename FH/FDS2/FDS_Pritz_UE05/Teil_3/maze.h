#ifndef MAZE_H
#define MAZE_H
#include<iostream>
#include<vector>

class maze_t {
public:
	// Renames int to coordinate_t for clarity
	typedef int coordinate_t;
	// Holds coordinates in x|y form.
	// x first element, y second element.
	typedef std::pair<coordinate_t, coordinate_t> position_t;
	// Default constructor
	maze_t();
	// Constructor to initialize maze using <filename>.
	maze_t(std::string const& filename);
	// Deconstructor.
	~maze_t();
	// Returns whether somebody is able to escape the maze from the given position <start>.
	// Also returns false if the starting location <start> is blocked.
	bool can_escape(position_t const& start);
	// Enables a step by step "animation" to see how the algorithm progresses.
	// If set to off, result and finished path will be printed at the end.
	void enable_animation(bool const setting);
	// Reads a maze from a given inputstream <in>
	std::istream& read(std::istream& in);
	// Prints the currently initialized maze to outputstream <out>
	std::ostream& print(std::ostream& out) const;
private:
	// rename position_t to dimension_t for clarity
	typedef position_t dimension_t;
	// Defines the boundaries of the maze.
	dimension_t m_dimensions;
	// The state of the maze.
	std::vector<std::string> m_maze;
	// Saves whether the maze has been initialized or not.
	bool initialized;
	// Saves whether the output of can_escape() should be animated.
	bool animated;
	// Helper function for can_escape()
	bool can_escape_worker(position_t const& location, int depth);
	// Returns whether a <location> is inside the boundaries of the maze.
	bool is_valid(position_t const& location);
	// Returns whether a <location> is on a free spot.
	bool is_free(position_t const& location);
	// Returns a reference to a location. If it is out of bounds, modulo is used.
	// Initialize first to avoid crashes.
	char& at(position_t const& location);
	void clear();
};

#endif