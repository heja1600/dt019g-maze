#pragma once

#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

#define START_X 0
#define START_Y 0



struct Cell {
	bool visited;
	size_t x; 
	size_t y;
	Cell(const size_t x, const size_t y): x(x), y(y),visited(false) {}
};

class Maze
{
public:

	Maze(const size_t x, const size_t y);

	void generate(const size_t startX = START_X, const size_t startY = START_Y);

	void solve(std::vector<std::vector<Cell*>> matrix);

	void print() const;

private:

	void addLeft(const Cell* cell);

	void addRight(const Cell* cell);

	void addBottom(const Cell* cell);

	void addTop(const Cell* cell);

	void addNeighbours();

	bool checkNeighbours(const Cell* prevCell, const Cell * cell) const;

	bool isOutOfSpace(const size_t x, const size_t y) const;

	std::vector<std::vector<Cell*>> matrix;

	std::stack<Cell*> stack;
};

