#ifndef H_GRAPH
#define H_GRAPH

#include "Globals.h"
#include "Point.h"
#include "Shelf.h"
#include <vector>
#include <algorithm>
#include <unordered_map>

class Graph
{
private:
	int _n;
	std::vector<std::vector<int>> _distances;
	std::vector<std::vector<std::vector<int>>> _path;
	std::vector<Point> _vertex;
	std::vector<std::vector<int>> _edges;

	void mitm1(int max, int pos, int dist, int bit_mask, int last, const std::vector<int> &vet, std::vector<bool> &visitado, std::unordered_map<long long int, std::vector<int>> &first_permutation) const;
	void mitm2(int &min_cost, int max, int pos, int dist, int bit_mask, int last, const std::vector<int> &vet, std::vector<bool> &visitado, const std::unordered_map<long long int, std::vector<int>> &first_permutation) const;

public:
	Graph();
	Graph(const std::vector<Shelf> &shelfs);
	Graph& operator= (const Graph &g);

	~Graph();

	const std::vector<std::vector<std::vector<int>>> & getPaths() const;
	int getDistance(int i, int j) const;

	const Point & getVertex(int i) const;

	void print() const;
	void printPath(int start, int ent) const;

	const int getNumVertexes() const;
	const int getNumEdges() const;

	int pathCost(const std::vector<int> &v) const;
	int pathCostMitm(const std::vector<int> &v) const;

};

#endif
