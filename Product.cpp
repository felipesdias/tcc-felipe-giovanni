#include "Product.h"

using namespace std;

/// Class constructor
Product::Product()
{
}


///Class destructor
Product::~Product()
{
}

/// Class constructor
/// @param line List of strings containing the information about the product
Product::Product(const vector<string>& line)
{
	_id = stoi(line[0]);
	_measurement_unit = line[2];
	_family = line[3];
	_dim.setDims(stoi(line[4]), stoi(line[5]), stoi(line[6]));
	if (line[7] == "")
		_weight = -1;
	else
		_weight = stoi(line[7]);
}

/// Operator = overload (assignment overload)
/// @param newValue Updated value 
Product & Product::operator=(const Product & newValue)
{
	_id = newValue._id;
	_weight = newValue._weight;
	_measurement_unit = newValue._measurement_unit;
	_family = newValue._family;
	_dim = newValue._dim;

	return *this;
}

int Product::getId() const
{
	return _id;
}

int Product::getWeight() const
{
	return _weight;
}

string Product::getMeasurement() const
{
	return _measurement_unit;
}

string Product::getFamily() const
{
	return _family;
}

Dimension Product::getDimension() const
{
	return _dim;
}

void Product::print(char sep)
{
	printf("ID: %d%c", _id, sep);
	printf("Weight: %d%c", _weight, sep);
	printf("Dimension: ");
	_dim.print();
	printf("%c", sep);
	printf("Family: %s%c", _family.c_str(), sep);
	printf("Measurement: %s%c\n", _measurement_unit.c_str(), sep);
}
