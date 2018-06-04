#include "Graph.h"

using namespace std;

Graph::Graph()
{
}

Graph::Graph(const vector<Shelf>& shelfs)
{
	int i = 0;
	int j, k;


	//Generate vertex
	_vertex.push_back(Point(shelfs[i].getPos().getX(), 0));
	_vertex.push_back(Point(shelfs[i].getPos().getX() + shelfs[i].getLength() / 2, 0));
	_vertex.push_back(Point(shelfs[i].getPos().getX() + shelfs[i].getLength(), 0));

	_vertex.push_back(shelfs[i].getPos());
	_vertex.push_back(Point(shelfs[i].getPos().getX() + shelfs[i].getLength() / 2, shelfs[i].getPos().getY()));
	_vertex.push_back(Point(shelfs[i].getPos().getX() + shelfs[i].getLength(), shelfs[i].getPos().getY()));

	int size = shelfs.size();
	for (i = 1; i < size; i++) {
		if (shelfs[i].getPos().getX() != shelfs[i - 1].getPos().getX()) {
			_vertex.push_back(Point(shelfs[i].getPos().getX(), 0));
			_vertex.push_back(Point(shelfs[i].getPos().getX() + shelfs[i].getLength() / 2, 0));
			_vertex.push_back(Point(shelfs[i].getPos().getX() + shelfs[i].getLength(), 0));
		}

		if (shelfs[i].getLines() == 2) {
			_vertex.push_back(shelfs[i].getPos());
			_vertex.push_back(Point(shelfs[i].getPos().getX() + shelfs[i].getLength() / 2, shelfs[i].getPos().getY()));
			_vertex.push_back(Point(shelfs[i].getPos().getX() + shelfs[i].getLength(), shelfs[i].getPos().getY()));
		}
	}

	_n = _vertex.size();
	_distances = vector<vector<int>>(_n, vector<int>(_n, INFINITE));
	_edges = vector<vector<int>>(_n, vector<int>());
	_path = vector<vector<vector<int>>>(_n, vector<vector<int>>(_n, vector<int>()));

	vector<vector<int>> next(_n, vector<int>(_n, -1));

	// Calculate distances
	// Self
	for (i = 0; i < _n; i++)
		_distances[i][i] = 0;

	// Horizontal distances on the same shelf
	size = shelfs.size();
	for (i = 0; i < size; i++) {
		int down = -1, up = -1;

		down = shelfs[i].getVertex()[0];
		if (shelfs[i].getVertex().size() == 2)
			up = shelfs[i].getVertex()[1];

		if (shelfs[i].getDirection() == 'C') {
			_distances[down + 1][down] = Point::distance(_vertex[down], _vertex[down + 1]);
			_distances[down][down - 1] = Point::distance(_vertex[down], _vertex[down - 1]);
			if (up != -1) {
				_distances[up - 1][up] = Point::distance(_vertex[up], _vertex[up - 1]);
				_distances[up][up + 1] = Point::distance(_vertex[up], _vertex[up + 1]);
			}
		}
		else {
			_distances[down][down + 1] = Point::distance(_vertex[down], _vertex[down + 1]);
			_distances[down - 1][down] = Point::distance(_vertex[down], _vertex[down - 1]);
			if (up != -1) {
				_distances[up][up - 1] = Point::distance(_vertex[up], _vertex[up - 1]);
				_distances[up + 1][up] = Point::distance(_vertex[up], _vertex[up + 1]);
			}
		}
	}


	int cont = 0;
	bool stop = false;
	// Vertical distances
	for (i = 0; i < _n - 3; i++) {
		if (i % 3 == 1)
			continue;

		if (stop && i % 3 == 2)
			cont++;

		// Vertical
		if (_vertex[i].getX() == _vertex[i + 3].getX())
			_distances[i][i + 3] = _distances[i + 3][i] = Point::distance(_vertex[i], _vertex[i + 3]);
		else if (i % 3 == 2) {
			stop = true;
		}
	}

	// Horizontal distances between the shelves
	int v1, v2;
	for (i = 0; i <= cont; i++) {
		v1 = i * 3 + 2;						///TODO: Explain why 
		v2 = cont * 3 + 1 + v1;
		_distances[v1][v2] = _distances[v2][v1] = Point::distance(_vertex[v1], _vertex[v2]);
	}

	// Generate edges
	for (i = 0; i < _n; i++)
		for (j = 0; j < _n; j++)
			if (_distances[i][j] != INFINITE && _distances[i][j] != 0) {
				_edges[i].push_back(j);
				next[i][j] = j;
			}

	for (k = 0; k < _n; k++) {
		for (i = 0; i < _n; i++) {
			for (j = 0; j < _n; j++) {
				if (_distances[i][k] != INFINITE && _distances[k][j] != INFINITE && _distances[i][j] > _distances[i][k] + _distances[k][j]) {
					_distances[i][j] = _distances[i][k] + _distances[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}

	for (i = 0; i < _n; i++) {
		for (j = 0; j < _n; j++) {
			if (i == j)
				continue;
			int curr = i;
			_path[i][j].push_back(i);
			while (j != curr) {
				curr = next[curr][j];
				_path[i][j].push_back(curr);
			}
		}
	}
}

Graph & Graph::operator=(const Graph & g)
{
	_n = g._n;
	_distances = g._distances;
	_vertex = g._vertex;
	_edges = g._edges;
	_path = g._path;

	return *this;
}


Graph::~Graph()
{
}

const std::vector<std::vector<std::vector<int>>>& Graph::getPaths() const
{
	return _path;
}

void Graph::print() const
{
	const char c = '\t';

	int size = _edges.size();
	for (int i = 0; i < size; i++) {
		printf("%d: ", i);
		for (auto it : _edges[i])
			printf("%d ", it);
		puts("");
	}

	printf("Vertex: %d\n", _n);
	for (int i = 0; i < _n; i++)
		printf("%c%d", c, i);
	puts("");
	for (int i = 0; i < _n; i++) {
		printf("%d", i);
		for (int j = 0; j < _n; j++)
			printf("%c%d", c, (_distances[i][j] == INFINITE) ? -1 : _distances[i][j]);
		puts("");
	}
}

void Graph::printPath(int start, int end) const
{
	printf("Path: %d->%d: ", start, end);
	for (auto it : _path[start][end])
		printf("%d ", it);
	puts("");
}

int Graph::pathCost(const vector<int> &v) const {
	if(v.size() == 0){
		printf("Route size = 0!!\n");
		return -1;
	}
	int cost = _distances[0][v[0]];
	int size = v.size() - 1;
	for(int i = 0; i < size; i++){
		cost += _distances[v[i]][v[i + 1]]; //As the value of second index should be i+1 and we will do this operation after, it's better to use pre-increment
	}
	cost += _distances[v.back()][0];
	return cost;
}

int Graph::getDistance(int i, int j) const
{
	return _distances[i][j];
}

const Point & Graph::getVertex(int i) const
{
	if (i < 0 || i > int(_vertex.size())) {
		printf("Invalid vertex index: %d, max: %lu\n", i, _vertex.size());
	}
	return _vertex[i];
}

const int Graph::getNumEdges() const {
	return _edges.size();
}

void Graph::mitm1(int max, int pos, int dist, int bit_mask, int last, const vector<int> &vet, vector<bool> &visitado, unordered_map<long long int, vector<int>> &first_permutation) const {
	if (pos == max) {
		auto it = first_permutation.find(bit_mask);
		if (it == first_permutation.end()) {
			first_permutation[bit_mask] = vector<int>(vet.size(), INFINITE);
			first_permutation[bit_mask][last] = dist;
		}
		else
			it->second[last] = min(it->second[last], dist);

		return;
	}

	int size = vet.size();
	for (int i = 0; i < size; i++) {
		if (!visitado[i]) {
			visitado[i] = true;
			mitm1(max, pos + 1, dist + _distances[vet[last]][vet[i]], bit_mask | (1 << i), i, vet, visitado, first_permutation);
			visitado[i] = false;
		}
	}
}

void Graph::mitm2(int & min_cost, int max, int pos, int dist, int bit_mask, int last, const std::vector<int>& vet, std::vector<bool>& visitado, const std::unordered_map<long long int, std::vector<int>>& first_permutation) const
{
	if (pos == max) {
		auto it = first_permutation.find(bit_mask);
		for (size_t i = 0; i<vet.size(); i++)
			if (!visitado[i])
				min_cost = min(min_cost, dist + _distances[vet[i]][vet[last]] + it->second[i]);

		return;
	}

	int size = vet.size();
	for (int i = 0; i < size; i++) {
		if (!visitado[i]) {
			visitado[i] = true;
			mitm2(min_cost, max, pos + 1, dist + _distances[vet[i]][vet[last]], bit_mask ^ (1 << i), i, vet, visitado, first_permutation);
			visitado[i] = false;
		}
	}
}


int Graph::pathCostMitm(const vector<int> &v) const
{
	unordered_map<long long int, vector<int>> first_permutation;

	int size_first = v.size() / 2;
	int size_second = v.size() / 2;
	if (v.size() % 2 == 1)
		size_first++;

	int max_set = 0;
	int size = v.size();
	for (int i = 0; i < size; i++)
		max_set |= 1 << i;

	vector<bool> visitado(v.size(), false);

	int min_cost = INFINITE;

	for (int i = 0; i < size; i++) {
		visitado[i] = true;
		mitm1(size_first, 1, _distances[0][v[i]], 0 | (1 << i), i, v, visitado, first_permutation);
		visitado[i] = false;
	}

	for (int i = 0; i < size; i++) {
		visitado[i] = true;
		mitm2(min_cost, size_second, 1, _distances[v[i]][0], max_set ^ (1 << i), i, v, visitado, first_permutation);
		visitado[i] = false;
	}

	return min_cost;
}

const int Graph::getNumVertexes() const {
	return _vertex.size();
}
