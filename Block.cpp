#include "Block.h"

Block::Block()
{
	_n_shelfs = 0;
	_ini_shelfs = INFINITE;
	_end_shelfs = -1;
}


Block::~Block()
{
}

///Class constructor
/// @param line String vector with the information about block
Block::Block(const std::vector<std::string>& line)
{
	_id = stoi(line[0]);
	_dim.setDims(stoi(line[1]), stoi(line[2]), 1);
	_pos.setCoords(stoi(line[3]), stoi(line[4]), 0);

	_n_shelfs = 0;
	_ini_shelfs = INFINITE;
	_end_shelfs = -1;
}

/// Operator = overload (assignment)
Block & Block::operator=(const Block &  b)
{
	_id = b._id;
	_n_shelfs = b._n_shelfs;
	_ini_shelfs = b._ini_shelfs;
	_end_shelfs = b._end_shelfs;
	_pos = b._pos;
	_dim = b._dim;

	return *this;
}

int Block::getId() const
{
	return _id;
}

int Block::getIniShelfs() const
{
	return _ini_shelfs;
}

int Block::getEndShelfs() const
{
	return _end_shelfs;
}

int Block::getNShelfs() const
{
	return _n_shelfs;
}

Point Block::getPos() const
{
	return _pos;
}

Dimension Block::getDimension() const
{
	return _dim;
}

void Block::print(char sep)
{
	printf("Id: %d%c", _id, sep);
	printf("Num shelfs: %d%c", _n_shelfs, sep);
	printf("Range shelfs: [%d, %d]%c", _ini_shelfs, _end_shelfs, sep);
	printf("Position: ");
	_pos.print();
	printf("%c", sep);
	printf("Dimension: ");
	_dim.print();
	printf("\n");
}

void Block::addRangeShelfs(int id)
{
	if (id < _ini_shelfs)
		_ini_shelfs = id;
	if (id > _end_shelfs)
		_end_shelfs = id;
	_n_shelfs = _end_shelfs - _ini_shelfs + 1;
}
