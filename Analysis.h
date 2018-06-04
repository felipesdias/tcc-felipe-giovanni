#ifndef H_ANALYSIS
#define H_ANALYSIS

#define boolMatrix std::vector<std::vector<bool>>
#define intMatrix std::vector<std::vector<int>>
#define correlationStructure std::vector<std::vector<std::pair<int, std::vector<int>>>>
#define mostRequestStructure std::vector<std::pair<int, int>>

#include "Globals.h"
#include <vector>
#include <algorithm>

class Analysis
{
public:
	Analysis();
	~Analysis();

	// Indice do 1º vector => quantidade de itens sendo correlacionados
	// First => quantas vezes a correlação aparece
	// Second => quais itens estão correlacionados
	static correlationStructure correlation(int n_products, const std::vector<std::vector<int>> &list, int max_group, size_t min_correlation);
	static mostRequestStructure mostRequest(int n_products, const std::vector<std::vector<int>> &lists);
};

#endif