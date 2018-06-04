#ifndef H_POINT
#define H_POINT

#include "Globals.h"
#include <cstdio>
#include <cmath>

class Point
{
private:
	int _x, _y, _z;

public:
	Point();
	~Point();
	Point(int x, int y);
	Point(int x, int y, int z);
	Point& operator = (const Point &p);

	//Setters
	void setCoords(int x, int y, int z);

	int getX() const;
	int getY() const;
	int getZ() const;

	// Operators
	/*
	Point& operator - (const Point &p);
	Point& operator + (const Point &p);
	*/

	// Auxiliary functions
	void print();
	void addPoint(const Point &p);
	void divisionInt(int n);

	static int distance(const Point &a, const Point &b);
	static int distanceAnalysis(const Point &a, const Point &b);
};

#endif
