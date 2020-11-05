#include "maze.h"

void main()
{
	//maze_t m("input/maze-1.txt");
	//maze_t m("input/maze-2.txt");
	maze_t m("input/maze-3.txt");
	//maze_t m("input/invalid.txt");
	//maze_t m("nonexisting");

	// Following position works for all mazes: 8,12
	if (m.can_escape(maze_t::position_t{ 8,12 }))
	{
		std::cout << std::endl << "Endresult: " << std::endl;
		m.print(std::cout);
		std::cout << "It's possible to escape!\n";
	}
	else
	{
		std::cout << std::endl << "Endresult: " << std::endl;
		m.print(std::cout);
		std::cout << "Escaping is impossible.\n";
	}
}