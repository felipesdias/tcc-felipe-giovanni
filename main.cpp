#include "Globals.h"
#include "Warehouse.h"
#include "Solution.h"
#include "Analysis.h"
#include "Allocation_heuristic.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

void timeRandomGreedy(int n);
void genetic(int size_init, int generations);
void compareCostAnalysisCost(int n);
void compareGreedys();

int main() {
	srand(unsigned int(std::time(nullptr)));

	Warehouse warehouse;
	warehouse.readWarehouse();

	Solution::setWarehouse(&warehouse);
	Solution::setLists("Ordens2.txt", 5, 3);

	genetic(50, 20);
	//timeRandomGreedy(100);
	//compareCostAnalysisCost(20);
	//compareGreedys();

	system("pause");

	return 0;
}

void genetic(int size_init, int generations) {
	Allocation_heuristic ah;
	ah.initPopulation(size_init);
	ah.run(generations);
	cout << "Best solution cost [GENETIC]: " << ah.getBestCost() << endl;
}

void compareGreedys() {
	Solution a;
	Solution b;
	a.greedySolution();
	b.greedySolution2();

	for (size_t i = 0; i < a.getCells().size(); i++) {
		for (size_t j = 0; j < a.getCells()[i].size(); j++) {
			cout << a.getCells()[i][j] << " - " << b.getCells()[i][j] << endl;
		}
	}

	a.evaluate(SIZE_BRUTE_FORCE);
	cout << a.getCost() << endl;

	b.evaluate(SIZE_BRUTE_FORCE);
	cout << b.getCost() << endl;
}

void timeRandomGreedy(int n) {
	using namespace std::chrono;

	vector<Solution> ss1(n);
	vector<Solution> ss2(n);

	for (int i = 0; i < n; i++) {
		ss1[i].randomSolution();
		ss2[i].greedySolution();
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		ss1[i].evaluate(SIZE_BRUTE_FORCE);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		ss2[i].evaluate(SIZE_BRUTE_FORCE);
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);

	std::cout << "It took me " << time_span.count() << " seconds." << endl;
	std::cout << "It took me " << time_span2.count() << " seconds." << endl;
}

void compareCostAnalysisCost(int n) {
	vector<Solution> teste(n);

	long long int maxiC = -1;
	long long int maxiA = -1;

	long long int miniC = 1ll << 62;
	long long int miniA = 1ll << 62;

	for (size_t i = 0; i < teste.size(); i++) {
		teste[i].randomSolution();
		teste[i].evaluate(SIZE_BRUTE_FORCE);
		teste[i].evaluateAnalysis();
		maxiC = max(maxiC, teste[i].getCost());
		maxiA = max(maxiA, teste[i].getCostAnalysis());

		miniC = min(miniC, teste[i].getCost());
		miniA = min(miniA, teste[i].getCostAnalysis());
	}

	cout << "worst - Best" << endl;
	cout << maxiC << " " << miniC << endl;
	cout << maxiA << " " << miniA << endl;

	maxiC -= miniC;
	maxiA -= miniA;

	sort(teste.begin(), teste.end());

	cout << endl << "Cost - Analysis Cost" << endl;
	for (size_t i = 0; i < teste.size(); i++) {
		cout << double(teste[i].getCost() - miniC) / double(maxiC) << "\t" << double(teste[i].getCostAnalysis() - miniA) / double(maxiA) << endl;
	}
}
