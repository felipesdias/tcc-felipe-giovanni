#ifndef H_SHELF
#define H_SHELF

#include "Globals.h"
#include "Point.h"
#include "Cell.h"
#include <string>
#include <vector>

class Shelf
{
private:
	int _id;
	int _id_block;
	int _n_cells;
	int _ini_cells;
	int _end_cells;
	int _lines;
	int _columns;
	char _direction;
	Point _pos;
	std::vector<int> _vertex;

public:
	Shelf();
	~Shelf();

	Shelf(const std::vector<std::string>& line);
	Shelf& operator= (const Shelf &b);

	void setIdBlock(int id);

	int getId() const;
	int getNCells() const;
	int getIniCells() const;
	int getEndCells() const;
	int getIdBlock() const;
	int getLines() const;
	int getColumns() const;
	int getLength() const;
	char getDirection() const;
	Point getPos() const;
	std::vector<int> getVertex() const;
	int getVertex(int cell) const; // return the vertex covering a cell

	void print(char separator);

	void addRangeCells(int id);
	void addVertex(int v);

	void setVertexCells(std::vector<Cell> &cell);
};

#endif
