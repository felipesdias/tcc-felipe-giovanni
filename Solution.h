#ifndef H_SOLUTION
#define H_SOLUTION

#include "Globals.h"
#include "Warehouse.h"
#include "Path_Heuristic.h"
#include "Analysis.h"
#include "Point.h"
#include "json.hpp"

#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>
#include <unordered_map>

class Solution
{
private:
	static std::vector<std::vector<int>> _lists;
	static correlationStructure _correlation;
	static mostRequestStructure _most_request;
	static Warehouse* _warehouse;

	std::vector<std::vector<int>> _cells;
	std::vector<std::pair<int, int>> _products; ///< first = cell, second = level
	long long int _cost;						///< Cost of the solution
	long long int _cost_brute_force;			///< Cost of solution evaluated by brute force
	long long int _cost_heuristic;				///< Cost of solution obtained through heuristic
	long long int _amount_heuristic;
	long long int _amount_brute_force;

	long long int _cost_analysis;

public:
	Solution();
	~Solution();

	Solution& operator= (const Solution &s);
	bool operator < (const Solution &a) const;
	bool operator > (const Solution &a) const;

	void setCell(int i, int j, int p);
	void setProduct(int i, std::pair<int,int> p);
	void swapItem(int i, int j, int i2, int j2);
	void swapProducts(int i, int j);
	void evaluate(int bruteForceSize);
	void evaluateAnalysis();
	std::pair<int,int> getProductPosition(int p) const;

	long long int getCost() const;
	long long int getCostAnalysis() const;
	const std::vector<std::vector<int>> & getCells() const;
	const std::vector<std::pair<int, int>> & getProducts() const;
	std::string getJson() const;

	void randomSolution();
	void greedySolution();
	void greedySolution2();

	static void setWarehouse(Warehouse *wh);
	static void setLists(std::string file, int max_group, int min_correlation);
	static const std::vector<std::vector<int>> & getLists();
};

#endif
