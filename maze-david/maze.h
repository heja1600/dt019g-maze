#pragma once

#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>



#define START_X 1
#define START_Y 1

struct Cell {
	bool visited;
	std::size_t x; 
	std::size_t y;
	Cell(const size_t x, const size_t y): x(x), y(y), visited(false) {}
};


class Maze
{
public:

	Maze(const size_t x, const size_t y);

	void generate(const size_t startX = START_X, const size_t startY = START_Y);

	void solve();

	void print() const;

private:

	bool addCell(const Cell* cell, const size_t xChange, const size_t yChange);

	bool addNeighbour(Cell * cell);

	bool checkNeighbours(const Cell* prevCell, const Cell * cell) const;

	bool isOutOfSpace(const size_t x, const size_t y) const;

	std::vector<std::vector<Cell*>> matrix;

	std::stack<Cell*> stack;

	std::vector<std::function<bool(Cell*)>> addMethods;
};

