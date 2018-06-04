#ifndef H_PATH_HEURISTIC
#define H_PATH_HEURISTIC

#include "Globals.h"
#include "Graph.h"

class Path_Heuristic {
public:
  Path_Heuristic();
  ~Path_Heuristic();

  static int getBestCost(const std::vector<int> &v, const Graph* g);
  static const std::vector <int> getBestPath(const std::vector<int> &v, const Graph* g);
};

#endif
