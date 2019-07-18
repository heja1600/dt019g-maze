#pragma once

#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>

#include "colorModifier.h"


#define START_X 1
#define START_Y 1

#define PATH " "
#define WALL "#"
#define START_POINT "S"
#define END_POINT "E"
#define SOLVE_PATH "o"

struct Cell {
	bool path, endPoint, visited, solvePath, startPoint;
	std::size_t x, y;
	Cell(const size_t x, const size_t y)
		: x(x), y(y), 
		path(false), endPoint(false), startPoint(false),
		visited(false), solvePath(false) {}
};

using Cmp = const std::function<bool(const Cell*, const Cell*)>;

class Maze
{
public:

	Maze(const size_t x, const size_t y);

	~Maze();

	void generate(const size_t startX = START_X, const size_t startY = START_Y);

	void solve();

	void print() const;

private:

	bool addCell(const Cell* cell, Cmp& cmp, const size_t xChange, const size_t yChange);

	bool addNeighbour(Cell * cell, Cmp & cmp);

	bool checkNeighbours(const Cell* prevCell, const Cell * cell) const;

	bool isOutOfSpace(const size_t x, const size_t y) const;

	void setEndPoint();

	std::vector<std::vector<Cell*>> matrix;

	std::stack<Cell*> stack;

	std::vector<std::function<bool(Cell*, Cmp)>> addMethods;
};

