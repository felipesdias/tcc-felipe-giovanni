#include "Warehouse.h"

#define DELIMITER_CSV "\t"
#define DIR_PRODUCTS "Produtos2.txt"
#define DIR_BLOCKS "Blocos2.txt"
#define DIR_SHELFS "Prateleiras2.txt"
#define DIR_CELLS "Celulas2.txt"

using namespace std;

Warehouse::Warehouse()
{
}

Warehouse::~Warehouse()
{
}

void Warehouse::addBlock(const Block & b)
{
	_blocks.push_back(b);
}

void Warehouse::addShelf(const Shelf & s)
{
	_shelfs.push_back(s);
}

void Warehouse::addCell(const Cell & c)
{
	_cells.push_back(c);
}

void Warehouse::addProduct(const Product & p)
{
	_products.push_back(p);
}

void Warehouse::readWarehouse()
{
	int i;
	string line;

	//Read Products
	ifstream file_products(DIR_PRODUCTS);
	i = 0;
	getline(file_products, line);
	for (getline(file_products, line); line != "" && line[0] != EOF; getline(file_products, line)) {
		addProduct(Product(sSplit(line, DELIMITER_CSV)));
		i++;
	}
	file_products.close();

	//Read Blocks
	ifstream file_blocks(DIR_BLOCKS);
	i = 0;
	getline(file_blocks, line);
	for (getline(file_blocks, line); line != "" && line[0] != EOF; getline(file_blocks, line)) {
		addBlock(Block(sSplit(line, DELIMITER_CSV)));
		i++;
	}
	file_blocks.close();

	//Read Shelfs
	ifstream file_shelfs(DIR_SHELFS);
	i = 0;
	getline(file_shelfs, line);
	for (getline(file_shelfs, line); line != "" && line[0] != EOF; getline(file_shelfs, line)) {
		addShelf(Shelf(sSplit(line, DELIMITER_CSV)));
		_blocks[_shelfs[i].getIdBlock()].addRangeShelfs(i);
		i++;
	}
	file_shelfs.close();

	for (size_t j = 0, v = 1; j < _shelfs.size(); j++) {
		_shelfs[j].addVertex(v);
		v += 3;
		if (_shelfs[j].getLines() == 2)
			_shelfs[j].addVertex(v);

		if (j + 1 < _shelfs.size() && _shelfs[j].getPos().getX() != _shelfs[j + 1].getPos().getX())
			v += 3;
	}

	//Read Cells
	ifstream file_cells(DIR_CELLS);
	i = 0;
	getline(file_cells, line);
	for (getline(file_cells, line); line != "" && line[0] != EOF; getline(file_cells, line)) {
		addCell(Cell(sSplit(line, DELIMITER_CSV)));
		_shelfs[_cells[i].getIdShelf()].addRangeCells(i);
		i++;
	}
	file_cells.close();

	//Define which edge access the cell
	for (size_t j = 0; j < _shelfs.size(); j++)
		_shelfs[j].setVertexCells(_cells);

	_graph = Graph(_shelfs);
}

void Warehouse::print(char sep)
{
	printf("Num products: %lu%c", _products.size(), sep);
	printf("Num blocks: %lu%c", _blocks.size(), sep);
	printf("Num shelfs: %lu%c", _shelfs.size(), sep);
	printf("Num cells: %lu\n", _cells.size());
}

const vector<Block> & Warehouse::getBlocks() const
{
	return _blocks;
}

const vector<Shelf> & Warehouse::getShelfs() const
{
	return _shelfs;
}

const vector<Cell> & Warehouse::getCells() const
{
	return _cells;
}

const vector<Product> & Warehouse::getProducts() const
{
	return _products;
}

const Graph & Warehouse::getGraph() const
{
	return _graph;
}
