#include "Solution.h"

using namespace std;
using json = nlohmann::json;


vector<vector<int>> Solution::_lists;
correlationStructure Solution::_correlation;
mostRequestStructure Solution::_most_request;
Warehouse* Solution::_warehouse;
const int MAX_SEQ_SIZE_BRUTEFORCE_MINPATH = 7;  

Solution::Solution()
{
	auto cells = _warehouse->getCells();
	_cells = vector<vector<int>>(cells.size());
	for (size_t i = 0; i < _cells.size(); i++) {
		_cells[i] = vector<int>(cells[i].getLevels());
	}
	_products = vector<pair<int, int>>(_warehouse->getProducts().size(), make_pair(-1, -1));

	_cost = 0ll;
	_cost_brute_force = 0ll;
	_cost_heuristic = 0ll;
	_amount_heuristic = 0ll;
	_amount_brute_force = 0ll;
	_cost_analysis = 0ll;
}

Solution::~Solution()
{
}

Solution & Solution::operator=(const Solution & s)
{
	_cells = s._cells;
	_products = s._products;
	_cost = s._cost;
	return (*this);
}

bool Solution::operator<(const Solution & a) const
{
	return _cost < a.getCost();
}

bool Solution::operator>(const Solution & a) const
{
	return _cost > a.getCost();
}

void Solution::setCell(int i, int j, int p)
{
	_cells[i][j] = p;
}

void Solution::setProduct(int i, pair<int,int> p)
{
	_products[i] = p;
}


void Solution::swapItem(int i, int j, int i2, int j2)
{
	swap(_cells[i][i2], _cells[j][j2]);
}

void Solution::swapProducts(int i, int j)
{
	int size = _products.size();
	if(i < 0 || j < 0 || i >= size || j >= size){
		printf("Swap products out of range indexes!\n");
	}
	std::swap(_products[i], _products[j]);
}

pair<int,int> Solution::getProductPosition(int p) const
{
	return _products[p];
}

long long int Solution::getCost() const
{
	/*
	printf("%d  %d\n", _cost, _lists.size() - _amount_heuristic);
	printf("%d  %d\n", _cost_heuristic, _amount_heuristic);
	printf("%.2lf  %.2lf\n", 100.0*_cost / double(_cost + _cost_heuristic), 100.0*_cost_heuristic / double(_cost + _cost_heuristic));
	printf("%.2lf  %.2lf\n", 100.0*(_lists.size() - _amount_heuristic) / double(_lists.size()), 100.0*_amount_heuristic / double(_lists.size()));
	*/

	return _cost;
}

long long int Solution::getCostAnalysis() const
{
	return _cost_analysis;
}

const std::vector<std::vector<int>>& Solution::getCells() const
{
	return _cells;
}

void Solution::randomSolution()
{
	vector<pair<int, int>> open_cells;
	set<int> id_products;
	vector<int> ids_products;
	auto cells = _warehouse->getCells();

	for (auto it : _lists)
		for (auto prod : it)
			id_products.insert(prod);
	for (auto it : id_products)
		ids_products.push_back(it);

	int size = cells.size();
	for (int i = 0; i < size; i++)
		for (int j = 0; j < cells[i].getLevels(); j++)
			open_cells.push_back(make_pair(i, j));

	random_shuffle(open_cells.begin(), open_cells.end());
	random_shuffle(ids_products.begin(), ids_products.end());

	size = ids_products.size();
	for (int i = 0; i < size; i++) {
		int pos = rand() % open_cells.size();
		_products[ids_products[i]] = open_cells[pos];
		swap(open_cells[pos], open_cells[open_cells.size() - 1]);
		open_cells.pop_back();
	}
}

void Solution::greedySolution()
{
	int pos = 0;
	for (size_t i = 0; i < _cells.size(); i++) {
		for (size_t j = 0; j < _cells[i].size(); j++) {
			_cells[i][j] = _most_request[pos].first;
			_products[_most_request[pos].first].first = i;
			_products[_most_request[pos].first].second = j;
			pos++;
		}
	}
}

int findProduct(int &i, int &j, const std::vector<std::pair<int, int>> & _products, const vector<pair<int, vector<int>>> &most_correlation) {
	int size = most_correlation.size();
	int size2;
	for (; i < size; i++) {
		size2 = most_correlation[i].second.size();
		for (; j < size2; j++) {
			if (_products[most_correlation[i].second[j]].first == -1) {
				return most_correlation[i].second[j];
			}
		}
		j = 0;
	}

	return -1;
}

void Solution::greedySolution2()
{
	vector<pair<int, vector<int>>> most_correlation;

	for (size_t ii = 2; ii < _correlation.size(); ii++)
		for (auto correlation : _correlation[ii])
			most_correlation.push_back(correlation);
	sort(most_correlation.rbegin(), most_correlation.rend());

	int pos1 = 0;
	int pos2 = 0;
	int product;
	int i, j;
	int size = _cells.size();
	int size2;
	for (i = 0; i < size; i++) {
		size2 = _cells[i].size();
		for (j = 0; j < size2; j++) {
			product = findProduct(pos1, pos2, _products, most_correlation);

			if (product == -1) {
				goto end;
			}

			_cells[i][j] = product;
			_products[product].first = i;
			_products[product].first = j;
		}
	}

	end:
	int pos = 0;
	size = _cells.size();
	for (; i < size; i++) {
		size2 = _cells[i].size();
		for (; j < size2; j++) {
			while (_products[_most_request[pos].first].first != -1) {
				pos++;
				if (pos == _most_request.size()) {
					return;

				}
			}

			_cells[i][j] = _most_request[pos].first;
			_products[_most_request[pos].first].first = i;
			_products[_most_request[pos].first].second = j;
		}
		j = 0;
	}
}

void Solution::setWarehouse(Warehouse * wh)
{
	_warehouse = wh;
}

void Solution::setLists(string file_path, int max_group, int min_correlation)
{
	int id_list, id_product;
	char c;
	string word;

	//Read Products
	ifstream file_products(file_path);
	getline(file_products, word);
	while (true) {
		c = file_products.peek();
		if (c == EOF || c == '\n') break;

		getline(file_products, word, '\t');
		id_product = stoi(word);

		getline(file_products, word, '\t');

		getline(file_products, word, '\t');
		id_list = stoi(word);

		getline(file_products, word, '\n');

		if (id_list >= int(_lists.size()))
			_lists.push_back(vector<int>());

		_lists[id_list].push_back(id_product);
	}

	file_products.close();

	_correlation = Analysis::correlation(_warehouse->getProducts().size(), _lists, max_group, min_correlation);
	_most_request = Analysis::mostRequest(_warehouse->getProducts().size(), _lists);
}

const vector<vector<int>>& Solution::getLists()
{
	return _lists;
}


void getVerticesList(const vector<int> &l, vector<int> &v, const Warehouse &wh, const Solution &solution)
{
	int numVertexes = wh.getGraph().getNumVertexes();
	vector<bool> s(numVertexes,false);

	for (size_t i = 0; i < l.size(); i++) {
		int productCell = solution.getProductPosition(l[i]).first;
		int vertex = wh.getCells()[productCell].getVertex();
		if (!s[vertex])
			v.push_back(vertex);

		s[vertex] = true;
	}

	sort(v.begin(), v.end());
}

vector<int> getBestPath(const vector<int> &v2, const Warehouse &wh)
{
	if (v2.size() <= 7) {
		vector <int> v = v2;
		int min_cost = INFINITE;
		vector<int> route = v;
		do {
			int value = wh.getGraph().pathCost(v);
			if (value < min_cost) {
				min_cost = value;
				route = v;
			}
		} while (next_permutation(v.begin(), v.end()));
		return route;
	}
	else {
		return Path_Heuristic::getBestPath(v2, &wh.getGraph());
	}
}

unordered_map<long long int, int> cache_routes;

/// Gets the path cost given a warehouse configuration and a sequence of pickings (integers)
/// @param v2 Sequence
/// @param wh Warehouse configuration
/// @return The cost of the path
int bestPathCost(vector<int> &v, const Warehouse &wh, int bruteForceSize)
{
	long long int bit_mask = 0;
	for (int it : v)
		bit_mask |= 1ll << (it / 3);

	auto it = cache_routes.find(bit_mask);
	if (it != cache_routes.end())
		return it->second;

	int min_cost = INFINITE;

	int size = v.size();
	if(size <= 5 && size <= bruteForceSize){
		do {
		  int value = wh.getGraph().pathCost(v);
		  if(value < min_cost){
				min_cost = value;
		  }
		} while(next_permutation(v.begin(), v.end()));		//Test all sequences (???)
	}
	else if (size <= bruteForceSize) {
		min_cost = wh.getGraph().pathCostMitm(v);
	}
	else {
		min_cost = Path_Heuristic::getBestCost(v, &wh.getGraph());
	}

	cache_routes[bit_mask] = min_cost;
	return min_cost;
}

/// Function to evaluate a cost of a solution
///
void Solution::evaluate(int bruteForceSize)
{
	int result;
	vector <int> v;
	_cost = _cost_brute_force = _cost_heuristic = _amount_heuristic = _amount_brute_force = 0ll;

	for (size_t i = 0; i < _lists.size(); i++) {
		v.clear();
		getVerticesList(_lists[i], v, *_warehouse, *this);

		result = bestPathCost(v, *_warehouse, bruteForceSize);

		if (int(v.size()) <= bruteForceSize) {
			_cost_brute_force += (long long int)result;
			_amount_brute_force++;
		}
		else {
			_cost_heuristic += (long long int)result;
			_amount_heuristic++;
		}
	}
	_cost = _cost_brute_force + _cost_heuristic;
}

void Solution::evaluateAnalysis()
{
	Point point;
	int productCell, vertex;
	_cost_analysis = 0ll;
	for (size_t i = 0; i < _correlation.size(); i++) {
		for (size_t j = 0; j < _correlation[i].size(); j++) {
			point.setCoords(0, 0, 0);
			for (size_t k = 0; k < _correlation[i][j].second.size(); k++) {
				productCell = getProductPosition(_correlation[i][j].second[k]).first;
				vertex = _warehouse->getCells()[productCell].getVertex();
				point.addPoint(_warehouse->getGraph().getVertex(vertex));
			}
			point.divisionInt(_correlation[i][j].second.size());
			if (i == 1) {
				point.setCoords(0, 0, 0);
			}
			for (size_t k = 0; k < _correlation[i][j].second.size(); k++) {
				productCell = getProductPosition(_correlation[i][j].second[k]).first;
				vertex = _warehouse->getCells()[productCell].getVertex();
				_cost_analysis += (long long int)Point::distance(point, _warehouse->getGraph().getVertex(vertex)) * _correlation[i][j].first * i;
			}
		}
	}
}

/// Get the poisition of the products
const vector<pair<int, int>> & Solution::getProducts() const{
	return _products;
}

/// Converts a pair to a json format
/// @param j Json environment. It will receive the result of the function
/// @param p pair to be converted
void to_json(json &j, const pair<int,int> &p)
{
	j = json{ { "Cell", p.first },{ "Level", p.second } };
}

/// Converts a solution to the json format
/// @param j Json environment
/// @param s Solution to be converted
void to_json(json &j, const Solution &s)
{
	for(size_t i = 0; i < s.getProducts().size(); i++){
		string aux = "Product " + to_string(i);
		pair<int, int> p = s.getProductPosition(i);
		if(p.first != -1 && p.second != -1){
			j += json{aux, s.getProductPosition(i)};
		}
	}
}

/// Return the json of solution translated to a string
/// @return The json environment dump
std::string Solution::getJson() const
{
	json j = (*this);
	return j.dump();
}
