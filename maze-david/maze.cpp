#include "maze.h"


Maze::Maze(const std::size_t x, const std::size_t y)
	: matrix(std::vector<std::vector<Cell*>>(x, std::vector<Cell*>(y)))
{
	for (std::size_t x = 0; x < this->matrix.size(); x++)
	{
		for (std::size_t y = 0; y < this->matrix[x].size(); y++)
		{
			this->matrix[x][y] = new Cell(x, y);
		}
	}

	// bind direction functions
	this->addMethods.push_back(std::bind(&Maze::addCell, this, std::placeholders::_1, 1, 0)); 
	this->addMethods.push_back(std::bind(&Maze::addCell, this, std::placeholders::_1, -1, 0));
	this->addMethods.push_back(std::bind(&Maze::addCell, this, std::placeholders::_1, 0, 1));
	this->addMethods.push_back(std::bind(&Maze::addCell, this, std::placeholders::_1, 0, -1));

}


bool Maze::addNeighbour(Cell * cell)
{
	std::random_shuffle(addMethods.begin(), addMethods.end());

	for (auto &add : addMethods) {
		if (add(cell)) return true;
	}

	return false;
}


void Maze::generate(const size_t startX, const size_t startY)
{
	Cell* startCell = this->matrix[startX][startY];

	startCell->visited = true;

	this->stack.push(startCell);


	while (!this->stack.empty())
	{

		if (!this->addNeighbour(this->stack.top()))
		{
			this->stack.pop();
		}
	}
	this->print();

}


bool Maze::addCell(const Cell* cell, const size_t xChange, const size_t yChange)
{
	if (!this->isOutOfSpace(cell->x + xChange, cell->y + yChange))
	{
		Cell* existingCell = this->matrix[cell->x + xChange][cell->y + yChange];
		if (checkNeighbours(cell, existingCell))
		{
			existingCell->visited = true;
			this->stack.push(existingCell);
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

	auto canBeAdded = [prevCell](const Cell* cell) { return prevCell == cell ? true : !cell->visited; };

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


bool Maze::isOutOfSpace(const std::size_t x, const std::size_t y) const {
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