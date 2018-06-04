#ifndef H_PRODUCT
#define H_PRODUCT

#include "Globals.h"
#include "Dimension.h"
#include <string>
#include <vector>

class Product
{
private:
	int _id;
	int _weight;
	std::string _measurement_unit;
	std::string _family;
	Dimension _dim;

public:
	Product();
	~Product();

	Product(const std::vector<std::string>& line);
	Product& operator= (const Product &p);

	int getId() const;
	int getWeight() const;
	std::string getMeasurement() const;
	std::string getFamily() const;
	Dimension getDimension() const;

	void print(char separator);

	static bool cmpCod(const Product &a, const Product &b);
};

#endif
