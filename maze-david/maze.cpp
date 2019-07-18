#include "maze.h"

using Cmp = const std::function<bool(const Cell*, const Cell*)>;

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

	matrix[START_X][START_Y]->startPoint = true;

	// bind direction functions
	this->addMethods.push_back(std::bind(&Maze::addCell, this, std::placeholders::_1, std::placeholders::_2, 1, 0));
	this->addMethods.push_back(std::bind(&Maze::addCell, this, std::placeholders::_1, std::placeholders::_2, -1, 0));
	this->addMethods.push_back(std::bind(&Maze::addCell, this, std::placeholders::_1, std::placeholders::_2, 0, 1));
	this->addMethods.push_back(std::bind(&Maze::addCell, this, std::placeholders::_1, std::placeholders::_2, 0, -1));

}

Maze::~Maze()
{
	std::for_each(matrix.begin(), matrix.end(), [](std::vector<Cell*>& row) {
		std::for_each(row.begin(), row.end(), [](Cell* cell) {
			delete cell;
			});
		});
}


bool Maze::addNeighbour(Cell * cell, Cmp &cmp)
{
	std::random_shuffle(addMethods.begin(), addMethods.end());

	for (auto &add : addMethods) {
		if (add(cell, cmp)) return true;
	}

	return false;
}


void Maze::generate(const size_t startX, const size_t startY)
{
	Cell* startCell = this->matrix[startX][startY];

	startCell->path = true;

	this->stack.push(startCell);

	Cmp cmp = std::bind(&Maze::checkNeighbours, this, std::placeholders::_1, std::placeholders::_2);

	while (!this->stack.empty())
	{
		this->stack.top()->path = true;
		if (!this->addNeighbour(this->stack.top(), cmp))
		{
			this->stack.pop();
		}
	}
	this->print();

}

void Maze::solve()
{
	this->stack.push(matrix[START_X][START_Y]);
	this->setEndPoint();

	Cmp cmp = [](const Cell* prevCell, const Cell* checkCell) {
		return checkCell->path && checkCell != prevCell && !checkCell->visited;
	};

	while (!stack.top()->endPoint)
	{
		this->stack.top()->visited = true;

		if (!addNeighbour(stack.top(), cmp)) this->stack.pop();
	}
	while (!stack.empty())
	{
		stack.top()->solvePath = true;
		stack.pop();
	}
	print();

}


bool Maze::addCell(const Cell* cell, Cmp & cmp, const size_t xChange, const size_t yChange)
{
	if (!this->isOutOfSpace(cell->x + xChange, cell->y + yChange))
	{
		Cell* existingCell = this->matrix[cell->x + xChange][cell->y + yChange];
		if (cmp(cell, existingCell))
		{
			this->stack.push(existingCell);
			return true;
		}
	}
	return false;
}




void Maze::print() const
{
	Color::Modifier bgRed(Color::BG_RED), bgGreen(Color::BG_GREEN), bgBlue(Color::BG_BLUE), bgD(Color::BG_DEFAULT);
	std::for_each(matrix.begin(), matrix.end(), [=](const std::vector<Cell*> row) {
		std::for_each(row.begin(), row.end(), [=](const Cell* cell){
			if (cell->startPoint) std::cout << bgBlue << "  ";
			else if (cell->endPoint) std::cout << bgBlue << "  ";
			else if (cell->solvePath) std::cout << bgGreen << "  ";
			else if (cell->path) std::cout << bgD << "  ";
			else std::cout << bgRed << "  ";
		});
		std::cout << std::endl;
	});
	std::cout << bgD << std::endl << std::endl;
}

bool Maze::checkNeighbours(const Cell* prevCell, const Cell* checkCell) const
{

	if (checkCell->path) return false;

	auto canBeAdded = [prevCell](const Cell* cell) { return prevCell == cell ? true : !cell->path; };

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

void Maze::setEndPoint()
{
	for (size_t x = matrix.size() - 3; x < matrix.size(); x++)
	{
		for (size_t y = matrix.front().size() - 3; y < matrix.front().size(); y++)
		{
			if (matrix[x][y]->path)
			{
				matrix[x][y]->endPoint = true;
				return;
			}
		}
	}
}
