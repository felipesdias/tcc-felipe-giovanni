#ifndef H_CELL
#define H_CELL

#include "Globals.h"
#include <string>
#include <vector>

class Cell
{
private:
	int _id;
	int _id_shelf;
	int _levels;
	int _vertex;

public:
	Cell();
	~Cell();

	Cell(const std::vector<std::string>& line);
	Cell& operator= (const Cell &c);

	void setVertex(const int &v);

	int getId() const;
	int getIdShelf() const;
	int getLevels() const;
	int getVertex() const;

	void print(char separator);
};

#endif
