#include "Shelf.h"

using namespace std;

Shelf::Shelf()
{
	_n_cells = 0;
	_ini_cells = INFINITE;
	_end_cells = -1;
}


Shelf::~Shelf()
{
}

/// Class constructor
/// @param line String list with the information about the shelf
Shelf::Shelf(const vector<string>& line)
{
	_id = stoi(line[0]);
	_id_block = stoi(line[1]);
	_pos.setCoords(stoi(line[2]), stoi(line[3]), 0);
	_lines = stoi(line[4]);
	_columns = stoi(line[5]);
	_direction = line[6][0];

	_n_cells = 0;
	_ini_cells = INFINITE;
	_end_cells = -1;
}


/// Operator = overload (assignment overload)
/// @param newValue Updated value
Shelf & Shelf::operator=(const Shelf & newValue)
{
	_id = newValue._id;
	_n_cells = newValue._n_cells;
	_ini_cells = newValue._ini_cells;
	_end_cells = newValue._end_cells;
	_id_block = newValue._id_block;
	_lines = newValue._lines;
	_columns = newValue._columns;
	_direction = newValue._direction;
	_pos = newValue._pos;
	_vertex = newValue._vertex;

	return *this;
}

void Shelf::setIdBlock(int id)
{
	_id_block = id;
}

int Shelf::getId() const
{
	return _id;
}

int Shelf::getNCells() const
{
	return _n_cells;
}

int Shelf::getIniCells() const
{
	return _ini_cells;
}

int Shelf::getEndCells() const
{
	return _end_cells;
}

int Shelf::getIdBlock() const
{
	return _id_block;
}

int Shelf::getLines() const
{
	return _lines;
}

int Shelf::getColumns() const
{
	return _columns;
}

int Shelf::getLength() const
{
	return 90;
}

char Shelf::getDirection() const
{
	return _direction;
}

Point Shelf::getPos() const
{
	return _pos;
}

vector<int> Shelf::getVertex() const
{
	return _vertex;
}

/// Print information about the shelf
void Shelf::print(char sep)
{
	printf("Id: %d%c", _id, sep);
	printf("Id Block: %d%c", _id_block, sep);
	printf("Num cells: %i%c", _n_cells, sep);
	printf("Range cells: [%d, %d]%c", _ini_cells, _end_cells, sep);
	printf("Size: %d x %d%c", _lines, _columns, sep);
	printf("Direction: %c%c", _direction, sep);
	printf("Vertex: %d | %d%c", _vertex[0], _vertex[1], sep);
	printf("Position: ");
	_pos.print();
	printf("\n");
}

void Shelf::addRangeCells(int id)
{
	if (id < _ini_cells)
		_ini_cells = id;
	if (id > _end_cells)
		_end_cells = id;
	_n_cells = _end_cells - _ini_cells + 1;
}

void Shelf::addVertex(int v)
{
	_vertex.push_back(v);
}

void Shelf::setVertexCells(std::vector<Cell> &cell)
{
	for (int i = _ini_cells; i <= _end_cells; i++) {
		if (i - _ini_cells < _columns)
			cell[i].setVertex(_vertex[0]);
		else
			cell[i].setVertex(_vertex[1]);
	}
}

int Shelf::getVertex(int cell) const // return the vertex covering a cell
{
	if(!(cell >= _ini_cells && cell <= _end_cells)){
		puts("getVertex in wrong shelf!");
		return -1;
	}
	if((cell-_ini_cells)/_columns > 0)
		return _vertex[1];
	else
		return _vertex[0];
}
