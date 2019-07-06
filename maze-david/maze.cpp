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


void Maze::addNeighbours()
{
	this->addLeft(this->stack.top());

	this->addBottom(this->stack.top());

	this->addRight(this->stack.top());

	this->addTop(this->stack.top());
}


void Maze::generate(const size_t startX, const size_t startY)
{
	Cell* startCell = this->matrix[startX][startY];

	startCell->visited = true;

	this->stack.push(startCell);

	while (true)
	{
		Cell* currentCell = this->stack.top();
		this->addNeighbours();
		if (currentCell == this->stack.top())
		{
			this->stack.pop();
		}
		if (currentCell == startCell)
		{
			break;
		}
	}
	this->print();
}

void Maze::addLeft(const Cell* cell)
{
	if (this->isOutOfSpace(cell->x - 1, cell->y))
	{
		Cell* leftCell = this->matrix[cell->x - 1][cell->y];
		if (!leftCell->visited)
		{
			leftCell->visited = true;
			this->stack.push(leftCell);
		}
	}
}


void Maze::addRight(const Cell* cell)
{
	if (this->isOutOfSpace(cell->x + 1, cell->y))
	{
		Cell* rightCell = this->matrix[cell->x + 1][cell->y];
		if (!rightCell->visited)
		{
			rightCell->visited = true;
			this->stack.push(rightCell);
		}
	}
}

void Maze::addBottom(const Cell* cell)
{
	if (this->isOutOfSpace(cell->x, cell->y -1))
	{
		Cell* bottomCell = this->matrix[cell->x][cell->y - 1];
		if (!bottomCell->visited)
		{
			bottomCell->visited = true;
			this->stack.push(bottomCell);
		}
	}
}


void Maze::addTop(const Cell* cell)
{
	if (this->isOutOfSpace(cell->x, cell->y + 1))
	{
		Cell* topCell = this->matrix[cell->x][cell->y + 1];
		if (!topCell->visited)
		{
			topCell->visited = true;
			this->stack.push(topCell);
		}
	}
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