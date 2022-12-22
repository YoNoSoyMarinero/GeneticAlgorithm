#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "ReadCityFile.h"
#include "City.h"
#include "CityMap.h"
#include "CityGraph.h"
#include "Solution.h"


using namespace std;

void createDummySolutions(vector<int>* dummy_solutions) {
	for (int i = 0; i < dummy_solutions->size(); i++)
	{
		dummy_solutions->at(i) = i;
	}
}

void sortSolutionsByDistance(vector<Solution*>* solutions) {
	int i, j;

	for (i = 0; i < solutions->size() - 1; i++) {
		for (j = 0; j < solutions->size() - i - 1; j++) {
			if (solutions->at(j)->distance > solutions->at(j + 1)->distance)
				swap(solutions->at(j), solutions->at(j + 1));
		}
	}
}

int main()
{
	//defining const
	const SAMPLE_SIZE = 100;

	//Getting number of cities in file
    int number_of_cities = ReadCityFile::cityCount();

	//Read file gets vector of strings wich represenst each row in file, row reptresnts city No. x postion and y postion
	//City map createMap returns vector of Citties with thier No. x and y coordinates
	vector<City>* cities_in_file = CityMap::createMap(ReadCityFile::readFile(), number_of_cities);

	//cityGraph is just matrix where intersection between rows and columns represent distance between two cities with No - 1 name
	double** cityGraphMatrix = CityGraph::getGraph(cities_in_file, number_of_cities);

	//creating dummy solutions vectors with values 0,1,2... to number of cities, this represents first permutaion of many
	vector<int> dummy_solution(number_of_cities);
	createDummySolutions(&dummy_solution);

	//creating generation of solutions, first generation
	vector<Solution*>solutions(1000);
	
	

	for (int i = 0; i < 1000; i++)
	{
		shuffle(dummy_solution.begin(), dummy_solution.end(), default_random_engine(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count())));
		solutions.at(i) = new Solution(dummy_solution);
		solutions.at(i)->solutionFitness(cityGraphMatrix);
	}
	sortSolutionsByDistance(&solutions);

	
}
