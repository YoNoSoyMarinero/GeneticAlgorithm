#include "CityGraph.h"
#include "City.h"
#include <vector>
#include <cmath>

using namespace std;


double** CityGraph::getGraph(vector<City>* cities_in_file, int number_of_cities) {
	double** graph = 0;
	graph = new double*[number_of_cities];

	for (size_t i = 0; i < number_of_cities; i++)
	{
		graph[i] = new double[number_of_cities];
		for (size_t j = 0; j < number_of_cities; j++)
		{
			graph[i][j] = sqrt(pow((cities_in_file->at(i).postion_x - cities_in_file->at(j).postion_x), 2) + pow((cities_in_file->at(i).postion_y - cities_in_file->at(j).postion_y), 2));
		}
	}

	return graph;
}