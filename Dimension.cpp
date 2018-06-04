#include "Dimension.h"

Dimension::Dimension() : _length(-1), _width(-1), _height(-1)
{
}


Dimension::~Dimension()
{
}

Dimension::Dimension(int l, int w) : _length(l), _width(w), _height(1)
{
}

Dimension::Dimension(int l, int w, int h) : _length(l), _width(w), _height(h)
{
}

Dimension & Dimension::operator=(const Dimension & dim)
{
	_length = dim._length;
	_width = dim._width;
	_height = dim._height;

	return *this;
}

int Dimension::getLength() const
{
	return _length;
}

int Dimension::getWidth() const
{
	return _width;
}

int Dimension::getHeight() const
{
	return _height;
}

void Dimension::setDims(int w, int l, int h)
{
	_width = w;
	_length = l;
	_height = h;
}

int Dimension::calcVolume() const
{
	return _length * _width * _height;
}

int Dimension::calcArea() const
{
	return _length * _width;
}

void Dimension::print()
{
	printf("(%d, %d, %d)", _length, _width, _height);
}
