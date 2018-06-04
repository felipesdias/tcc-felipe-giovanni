#ifndef H_DIMENSION
#define H_DIMENSION

#include "Globals.h"
#include <cstdio>

class Dimension
{
private:
	int _length;
	int _width;
	int _height;

public:
	Dimension();
	~Dimension();
	Dimension(int l, int w);
	Dimension(int l, int w, int h);
	Dimension& operator = (const Dimension &dim);
	/*
	Dimension(const Dimension &dim);
	*/

	//Setters and Getters
	int getLength() const;
	int getWidth() const;
	int getHeight() const;

	void setDims(int w, int l, int h);

	// Auxiliary functions
	int calcVolume() const;
	int calcArea() const;
	void print();
};

#endif
