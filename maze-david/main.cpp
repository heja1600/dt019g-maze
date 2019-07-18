

#include "maze.h"

int main()
{
	Maze maze(25, 50);
	maze.generate();
	maze.solve();
	return EXIT_SUCCESS;
}