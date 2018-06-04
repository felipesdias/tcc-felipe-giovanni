#include "Point.h"

/// Class constructor
Point::Point() : _x(-1), _y(-1), _z(-1)
{
}


/// Class destructor
Point::~Point()
{
}

/// Class constructor
/// @param x Coordinate on x-axis
/// @param y Coordinate on y-axis
Point::Point(int x, int y) : _x(x), _y(y), _z(0)
{
}

/// Class constructor
/// @param x Coordinate on x-axis
/// @param y Coordinate on y-axis
/// @param z Coordinate on z-axis (default value 1)
Point::Point(int x, int y, int z) : _x(x), _y(y), _z(1)
{
}

/// Operator = overload (in this function, used as a simple assignment)
/// @param newValue value that will be assigned to the current point
/// @return
Point & Point::operator=(const Point & newValue)
{
	_x = newValue._x;
	_y = newValue._y;
	_z = newValue._z;

	return *this;
}

/// Sets the coordinates of the point
/// @param x Coordinate on x-axis
/// @param y Coordinate on y-axis
/// @param z Coordinate on z-axis
void Point::setCoords(int x, int y, int z)
{
	_x = x;
	_y = y;
	_z = z;
}

int Point::getX() const
{
	return _x;
}

int Point::getY() const
{
	return _y;
}

int Point::getZ() const
{
	return _z;
}

/// Prints a point position
void Point::print()
{
	printf("(%d, %d, %d)", _x, _y, _z);
}

/// Vector/Point plus operation
/// @param point right side point
void Point::addPoint(const Point & point)
{
	_x += point._x;
	_y += point._y;
	_z += point._z;
}

void Point::divisionInt(int n)
{
	if (n != 0) {
		_x /= n;
		_y /= n;
		_z /= n;
	}else {
		_x = INFINITE;
		_y /= INFINITE;
		_z /= INFINITE;
	}
}

int Point::distance(const Point & a, const Point & b)
{
	return abs(a._x - b._x) + abs(a._y - b._y);
}

int Point::distanceAnalysis(const Point & a, const Point & b)
{
	return (a._x - b._x)*(a._x - b._x) + (a._y - b._y)*(a._y - b._y);
}
