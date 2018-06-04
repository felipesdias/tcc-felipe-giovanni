#ifndef H_ALLOCATION_HEURISTIC
#define H_ALLOCATION_HEURISTIC

#include "Globals.h"
#include "Solution.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <functional>     // std::greater

class Allocation_heuristic {
private:
  std::priority_queue<Solution, std::vector<Solution>, std::greater<Solution>> _population;
  Solution _best_solution;
  long long _best_cost;

  int crossover(int p, int m); // p <- percentage of new elements to be generated from the m% best elements
  void selectPopulation(int q); // remove q elements
  void mutatePopulation(int p, int k); // p <- percentage of solutions to be mutated k%
  void printPopulation();
public:

  Allocation_heuristic();
  Allocation_heuristic(const std::vector<Solution> &p);

  void run(int max_iter);
  void initPopulation(int q); // q <- size of population
  void setPopulation(const std::vector<Solution> &p); // p <- new population

  const Solution & getBestSolution() const;
  long long getBestCost() const;

};

#endif
