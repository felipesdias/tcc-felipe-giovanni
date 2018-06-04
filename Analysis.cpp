#include "Analysis.h"

using namespace std;


Analysis::Analysis()
{
}

Analysis::~Analysis()
{
}

mostRequestStructure Analysis::mostRequest(int n_products, const std::vector<std::vector<int>>& lists)
{
	vector<pair<int, int>> products;
	for (int i = 0; i < n_products; i++)
		products.push_back(make_pair(i, 0));

	for (auto list : lists)
		for (auto prod : list)
			products[prod].second++;

	sort(products.begin(), products.end(), [](const pair<int, int> &left, const pair<int, int> &right) {
		return left.second > right.second;
	});
	return products;
}

void makeCorrelation(size_t min_correlation, int max_group, int current, vector<int> &current_products,  correlationStructure &correlation, const boolMatrix &binary,
					 const vector<int> &current_lists, const intMatrix &pruduct_list) {

	if (current_products.size() == max_group) return;

	size_t cont;

	vector<int> new_current_lists;

	int size = pruduct_list.size();
	for (int i = current; i < size; i++) {
		if (pruduct_list[i].size() >= min_correlation) {
			cont = 0;
			new_current_lists.clear();

			int currentListSize = current_lists.size();
			for (int j = 0; j < currentListSize; j++) {
				if (binary[current_lists[j]][i]) {
					cont++;
					new_current_lists.push_back(current_lists[j]);
				}
			}

			if (cont >= min_correlation) {
				current_products.push_back(i);
				correlation[current_products.size()].push_back(make_pair(cont, current_products));
				makeCorrelation(min_correlation, max_group, i + 1, current_products, correlation, binary, new_current_lists, pruduct_list);

				current_products.pop_back();
			}
		}
	}
}

correlationStructure Analysis::correlation(int n_products, const vector<vector<int>>& list, int max_group, size_t min_correlation)
{
	vector<vector<int>> pruduct_list(n_products, vector<int>());
	vector<vector<bool>> binary(list.size(), vector<bool>(n_products, false));

	int size = list.size();
	int size2;
	for (int i = 0; i < size; i++) {
		size2 = list[i].size();
		for (int j = 0; j < size2; j++) {
			pruduct_list[list[i][j]].push_back(i);
			binary[i][list[i][j]] = true;
		}
	}

	correlationStructure correlation(max_group + 1, vector<pair<int, vector<int>>>());
	vector<int> current_products;

	for (int i = 0; i < n_products; i++) {
		if (pruduct_list[i].size() >= min_correlation) {
			current_products.push_back(i);
			correlation[current_products.size()].push_back(make_pair(pruduct_list[i].size(), current_products));
			makeCorrelation(min_correlation, max_group, i + 1, current_products, correlation, binary, pruduct_list[i], pruduct_list);
			current_products.pop_back();
		}
	}

	return correlation;
}

