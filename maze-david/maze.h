#pragma once

#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <functional>

#define START_X 0
#define START_Y 0

enum {
	LEFT,
	RIGHT,
	TOP,
	BOT
};

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

	bool addLeft(const Cell* cell);

	bool addRight(const Cell* cell);

	bool addBottom(const Cell* cell);

	bool addTop(const Cell* cell);

	bool addNeighbour(Cell * cell);

	bool checkNeighbours(const Cell* prevCell, const Cell * cell) const;

	bool isOutOfSpace(const size_t x, const size_t y) const;

	std::vector<std::vector<Cell*>> matrix;

	std::vector<Cell*> stack;

	std::vector<std::function<bool(Cell*)>> adder;
};

