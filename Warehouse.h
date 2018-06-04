#ifndef H_WAREHOUSE
#define H_WAREHOUSE

#include "Globals.h"
#include "Block.h"
#include "Shelf.h"
#include "Cell.h"
#include "Product.h"
#include "Functions.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>

class Warehouse
{
private:
	std::vector<Block> _blocks;
	std::vector<Shelf> _shelfs;
	std::vector<Cell> _cells;
	std::vector<Product> _products;
	Graph _graph;

public:
	Warehouse();
	~Warehouse();

	void addBlock(const Block &b);
	void addShelf(const Shelf &s);
	void addCell(const Cell &c);
	void addProduct(const Product &p);

	const std::vector<Block> & getBlocks() const;
	const std::vector<Shelf> & getShelfs() const;
	const std::vector<Cell> & getCells() const;
	const std::vector<Product> & getProducts() const;
	const Graph & getGraph() const;

	void readWarehouse();

	void print(char separator);
};

#endif
