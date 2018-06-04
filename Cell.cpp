#include "Cell.h"

using namespace std;

Cell::Cell()
{
}


Cell::~Cell()
{
}

Cell::Cell(const vector<string>& line)
{
	_id = stoi(line[0]);
	_id_shelf = stoi(line[1]);
	_levels = stoi(line[2]);
	_vertex = -1;
}

Cell & Cell::operator=(const Cell & c)
{
	_id = c._id;
	_id_shelf = c._id_shelf;
	_levels = c._levels;
	_vertex = c._vertex;

	return *this;
}

void Cell::setVertex(const int& v)
{
	_vertex = v;
}

int Cell::getId() const
{
	return _id;
}

int Cell::getIdShelf() const
{
	return _id_shelf;
}

int Cell::getLevels() const
{
	return _levels;
}

int Cell::getVertex() const
{
	return _vertex;
}

void Cell::print(char sep)
{
	printf("Id: %d%c", _id, sep);
	printf("Id Shelf: %d%c", _id_shelf, sep);
	printf("Levels: %i%c", _levels, sep);
	printf("Vertex: %d%c", _vertex, sep);
	printf("\n");
}
