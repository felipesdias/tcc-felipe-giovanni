#ifndef H_BLOCK
#define H_BLOCK

#include "Globals.h"
#include "Point.h"
#include "Dimension.h"
#include <vector>
#include <string>

class Block
{
private:
	int _id;
	int _n_shelfs;
	int _ini_shelfs;
	int _end_shelfs;
	Point _pos;
	Dimension _dim;

public:
	Block();
	~Block();

	Block(const std::vector<std::string>& line);
	Block& operator= (const Block &b);

	int getId() const;
	int getIniShelfs() const;
	int getEndShelfs() const;
	int getNShelfs() const;

	Point getPos() const;
	Dimension getDimension() const;

	void print(char separator);

	static bool cmpCod(const Block &a, const Block &b);
	void addRangeShelfs(int id);
};

#endif