#include "maze.h"


Maze::Maze(const size_t x, const size_t y)
	: matrix(std::vector<std::vector<Cell*>>(x, std::vector<Cell*>(y)))
{
	for (size_t x = 0; x < this->matrix.size(); x++)
	{
		for (size_t y = 0; y < this->matrix[x].size(); y++)
		{
			this->matrix[x][y] = new Cell(x, y);
		}
	}

	
}


bool Maze::addNeighbour(Cell * cell)
{

	auto adder = [=](size_t dir, Cell* cell) {
		switch (dir)
		{
		case TOP: {
			if (this->addTop(cell)) return true;
			break;
		}
		case RIGHT: {
			if (this->addRight(cell)) return true;
			break;
		}
		case BOT: {
			if (this->addBottom(cell)) return true;
			break;
		}
		case LEFT: {
			if (this->addLeft(cell)) return true;
			break;
		}
		}
		return false;
	};

	std::vector<size_t> dir = { RIGHT, TOP, BOT, LEFT };
	std::random_shuffle(dir.begin(), dir.end());
	for (auto &e : dir) {
		if (adder(e, cell)) return true;
	}

	return false;
}


void Maze::generate(const size_t startX, const size_t startY)
{
	Cell* startCell = this->matrix[startX][startY];

	startCell->visited = true;

	this->stack.push_back(startCell);


	while (true)
	{

		if (!this->addNeighbour(this->stack.back()))
		{
			this->stack.pop_back();
		}
		if (this->stack.empty())
		{
			break;
		}


	}
	this->print();

}

bool Maze::addLeft(const Cell * cell)
{
	if (!this->isOutOfSpace(cell->x - 1, cell->y))
	{
		Cell* leftCell = this->matrix[cell->x - 1][cell->y];
		if (checkNeighbours(cell, leftCell))
		{
			leftCell->visited = true;
			this->stack.push_back(leftCell);
			return true;
		}
	}
	return false;
}


bool Maze::addRight(const Cell * cell)
{
	if (!this->isOutOfSpace(cell->x + 1, cell->y))
	{
		Cell * rightCell = this->matrix[cell->x + 1][cell->y];
		if (checkNeighbours(cell, rightCell))
		{
			rightCell->visited = true;
			this->stack.push_back(rightCell);
			return true;
		}
	}
	return false;
}

bool Maze::addBottom(const Cell * cell)
{
	if (!this->isOutOfSpace(cell->x, cell->y - 1))
	{
		Cell * bottomCell = this->matrix[cell->x][cell->y - 1];
		if (checkNeighbours(cell, bottomCell))
		{
			bottomCell->visited = true;
			this->stack.push_back(bottomCell);
			return true;
		}
	}
	return false;
}


bool Maze::addTop(const Cell * cell)
{
	if (!this->isOutOfSpace(cell->x, cell->y + 1))
	{
		Cell* topCell = this->matrix[cell->x][cell->y + 1];
		if (checkNeighbours(cell, topCell))
		{
			topCell->visited = true;
			this->stack.push_back(topCell);
			return true;
		}
	}
	return false;
}


void Maze::print() const
{
	std::for_each(matrix.begin(), matrix.end(), [](const std::vector<Cell*> row) {
		std::for_each(row.begin(), row.end(), [](const Cell* cell){
			std::cout << (cell->visited ? " " : "#");
		});
		std::cout << std::endl;
		
	});
}

bool Maze::checkNeighbours(const Cell* prevCell, const Cell* checkCell) const
{

	if (checkCell->visited) return false;

	auto canBeAdded = [prevCell](const Cell* cell) {
		if (prevCell == cell)
		{
			return true;
		}
		return !cell->visited;
	};

	// check right
	if (!isOutOfSpace(checkCell->x + 1, checkCell->y))
	{
		if (!canBeAdded(matrix[checkCell->x + 1][checkCell->y]))
		{
			return false;
		}
	}

	// check left
	if (!isOutOfSpace(checkCell->x - 1, checkCell->y))
	{
		if (!canBeAdded(matrix[checkCell->x - 1][checkCell->y]))
		{
			return false;
		}
	}

	// check top
	if (!isOutOfSpace(checkCell->x, checkCell->y + 1))
	{
		if (!canBeAdded(matrix[checkCell->x][checkCell->y + 1]))
		{
			return false;
		}
	}

	// check bottom
	if (!isOutOfSpace(checkCell->x, checkCell->y - 1))
	{
		if (!canBeAdded(matrix[checkCell->x][checkCell->y - 1]))
		{
			return false;
		}
	}

	return true;
}


bool Maze::isOutOfSpace(const size_t x, const size_t y) const {
	if (x < 0 || x > this->matrix.size() - 1)
	{
		return true;
	}
	if (y < 0 || y > this->matrix[x].size() - 1)
	{
		return true;
	}
	return false;
}