#include "Allocation_heuristic.h"

using namespace std;

Allocation_heuristic::Allocation_heuristic()
{
  _best_cost = 1ll << 60;
}

Allocation_heuristic::Allocation_heuristic(const vector<Solution> &p)
{
  if(p.size() == 0){
    printf("Empty initial population!\n");
  }
  for(auto i : p){
    _population.push(i);
  }
  _best_solution = _population.top();
  _best_cost = _best_solution.getCost();
}

void Allocation_heuristic::run(int max_iter)
{
  if(max_iter < 0){
    printf("Number of iterations send to genetic < 0\n");
  }
  int p, m, p2, k;
  p = 30;
  m = 60;
  p2 = 40;
  k = 20;
  while(max_iter--){
    int qtdRemove = crossover(p, m);
    selectPopulation(qtdRemove);
    mutatePopulation(p2, k);
  }
}

void Allocation_heuristic::initPopulation(int q)
{
  for(int i = 0; i < q; i++){
    Solution s;
    s.randomSolution();
    s.evaluate(SIZE_BRUTE_FORCE);
    if(s.getCost() < _best_cost){
      _best_cost = s.getCost();
      _best_solution = s;
    }
    _population.push(s);
  }

}

void Allocation_heuristic::setPopulation(const vector<Solution> &p)
{
  if(p.size() == 0){
    printf("SetPopulation received population size = 0!\n");
  }

  int size = p.size();
  for(int i = 0; i < size; i++){
    _population.push(p[i]);
  }
  _best_solution = _population.top();
  _best_cost = _best_solution.getCost();
}

const Solution & Allocation_heuristic::getBestSolution() const
{
  return _best_solution;
}

long long Allocation_heuristic::getBestCost() const
{
  return _best_cost;
}

struct Sorting_criteria1 { // sort based on min(avg(product[father], product[mother]))
  int father, mother;
  vector<Solution> population;
  Sorting_criteria1(int _f, int _m, const vector<Solution> &_p){
    father = _f;
    mother = _m;
    population = _p;
  }
  bool operator()(int i, int j){
    return (population[father].getProducts()[i].first+population[mother].getProducts()[i].first)/2.0 < (population[father].getProducts()[j].first+population[mother].getProducts()[j].first)/2.0;
  }
};

int Allocation_heuristic::crossover(int p, int m) // p <- percentage of new elements to be generated from the m% best elements
{
  priority_queue<Solution, std::vector<Solution>, std::greater<Solution>> pq_copy = _population;
  vector <Solution> population;
  while(pq_copy.size() > 0){
    population.push_back(pq_copy.top());
    pq_copy.pop();
  }
  int father, mother;
  int qtd = (population.size()*p)/100;
  for(int i = 0; i < qtd; i++){
    father = rand()%((population.size()*m)/100);
    do {
      mother = rand()%((population.size()*m)/100);
    } while(mother == father);

    Solution s;

    set<pair<int, int>> chosen;
    set<pair<int, int>> not_chosen;

	int size = population[father].getProducts().size();
    for(int j = 0; j < size; j++){
      if(population[father].getProducts()[j].first != -1 && population[father].getProducts()[j].second != -1){
        not_chosen.insert(population[father].getProducts()[j]);
      }
      if(population[mother].getProducts()[j].first != -1 && population[mother].getProducts()[j].second != -1){
        not_chosen.insert(population[mother].getProducts()[j]);
      }
    }

    vector <int> not_filled;
    bool fathers_turn = 1;

	size = population[father].getProducts().size();
    for(int j = 0; j <size; j++){
      if(population[father].getProducts()[j] == make_pair(-1, -1) && population[mother].getProducts()[j] == make_pair(-1, -1)){
        s.setProduct(j, make_pair(-1, -1));
      } else {
        if(fathers_turn){
          set<pair<int,int>>::iterator it = not_chosen.find(population[father].getProducts()[j]);
          if(it != not_chosen.end()){
            not_chosen.erase(it);
            s.setProduct(j, population[father].getProducts()[j]);
            fathers_turn = 0;
          } else {
            not_filled.push_back(j);
          }
        } else {
          set<pair<int,int>>::iterator it = not_chosen.find(population[mother].getProducts()[j]);
          if(it != not_chosen.end()){
            not_chosen.erase(it);
            s.setProduct(j, population[mother].getProducts()[j]);
            fathers_turn = 1;
          } else {
            not_filled.push_back(j);
          }
        }
      }
    }

    sort(not_filled.begin(), not_filled.end(), Sorting_criteria1(father, mother, population));

    vector<pair<int, int>> not_chosen2;
    for(auto it : not_chosen){
      not_chosen2.push_back(it);
    }
    sort(not_chosen2.begin(), not_chosen2.end());

	size = not_filled.size();
    for(int j = 0; j < size; j++){
      if(not_chosen.size() == 0){
        printf("No position available for alocate the product in crossover function, i.e, set size = 0\n");
      }
      s.setProduct(not_filled[j], not_chosen2[j]);
    }
    s.evaluate(SIZE_BRUTE_FORCE);
    _population.push(s);
    if(_population.top().getCost() < _best_cost){
      _best_solution = _population.top();
      _best_cost = _best_solution.getCost();
    }
  }
  return qtd;
}

void Allocation_heuristic::selectPopulation(int q) // remove q elements
{
	size_t size = q;
  priority_queue<Solution, std::vector<Solution>, std::greater<Solution>> pq_copy;
  while(_population.size() > size){
    pq_copy.push(_population.top());
    _population.pop();
  }
  _population = pq_copy;
  if(_population.top().getCost() < _best_cost){
    _best_solution = _population.top();
    _best_cost = _best_solution.getCost();
  }
}

void Allocation_heuristic::mutatePopulation(int p, int k) // p <- percantage of solutions to mutate k%
{
  priority_queue<Solution, std::vector<Solution>, std::greater<Solution>> pq_copy = _population;
  vector<Solution> population;
  while(_population.size() > 0){
    population.push_back(_population.top());
    _population.pop();
  }

  int qtd = (population.size()*p)/100;
  for(int i = 0; i < qtd; i++){
    int m_solution = rand()%population.size();
    int qtdIn = (population[m_solution].getProducts().size()*k)/100; qtdIn /= 2;
    for(int j = 0; j < qtdIn; j++){
      int product1, product2;
      product1 = rand()%population[m_solution].getProducts().size();
      while(population[m_solution].getProducts()[product1].first == -1) {
        product1++;
        product1 %= population[m_solution].getProducts().size();
      }
      product2 = rand()%population[m_solution].getProducts().size();
      while(population[m_solution].getProducts()[product2].first == -1) {
        product2++;
        product2 %= population[m_solution].getProducts().size();
      }

      population[m_solution].swapProducts(product1, product2);
    }
    population[m_solution].evaluate(SIZE_BRUTE_FORCE);
  }

  int size = population.size();
  for(int i = 0; i < size; i++){
    _population.push(population[i]);
  }
  if(_population.top().getCost() < _best_cost){
    _best_solution = _population.top();
    _best_cost = _best_solution.getCost();
  }
}

void Allocation_heuristic::printPopulation(){
  priority_queue<Solution, std::vector<Solution>, std::greater<Solution>> pq_copy = _population;
  vector<Solution> population;
  while(_population.size() > 0){
    population.push_back(_population.top());
    _population.pop();
  }

  int size = population.size();
  int size2;
  for(int i = 0; i < size; i++){
    cerr << "Individual " << i+1 << endl;
    vector<pair<int,int>> products = population[i].getProducts();
	size2 = products.size();
    for(int j = 0; j < size2; j++){
      if(products[j].first != -1){
        cerr << "(" << products[j].first << ", " << products[j].second << ")";
      }
    } cerr << endl;
  }
  _population = pq_copy;
}
