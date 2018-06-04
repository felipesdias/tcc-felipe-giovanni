#include "Path_Heuristic.h"

using namespace std;

Path_Heuristic::Path_Heuristic()
{
}

Path_Heuristic::~Path_Heuristic()
{
}

int Path_Heuristic::getBestCost(const std::vector<int>& _vertices, const Graph * _graph)
{
	vector <int> vertices = _vertices;
	vector <int> new_path;
	int source = 0;
	int nearest_neighbor;
	int min_distance;
	while (vertices.size() > 0) {
		nearest_neighbor = 0;
		min_distance = _graph->getDistance(source, vertices[nearest_neighbor]);
		for (size_t i = 1; i < vertices.size(); i++) {
			int dist_s_i = _graph->getDistance(source, vertices[i]);
			if (dist_s_i < min_distance) {
				min_distance = dist_s_i;
				nearest_neighbor = i;
			}
		}
		new_path.push_back(vertices[nearest_neighbor]);
		source = vertices[nearest_neighbor];
		swap(vertices[nearest_neighbor], vertices[vertices.size() - 1]);
		vertices.pop_back();
	}

	return _graph->pathCost(new_path);
}

const std::vector<int> Path_Heuristic::getBestPath(const std::vector<int>& _vertices, const Graph * _graph)
{
	vector <int> vertices = _vertices;
	vector <int> new_path;
	int source = 0;
	int nearest_neighbor;
	int min_distance;
	while (vertices.size() > 0) {
		nearest_neighbor = 0;
		min_distance = _graph->getDistance(source, vertices[nearest_neighbor]);
		for (size_t i = 1; i < vertices.size(); i++) {
			int dist_s_i = _graph->getDistance(source, vertices[i]);
			if (dist_s_i < min_distance) {
				min_distance = dist_s_i;
				nearest_neighbor = i;
			}
		}
		new_path.push_back(vertices[nearest_neighbor]);
		source = vertices[nearest_neighbor];
		swap(vertices[nearest_neighbor], vertices[vertices.size() - 1]);
		vertices.pop_back();
	}

	return new_path;
}
