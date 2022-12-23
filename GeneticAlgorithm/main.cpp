#include <iostream>
#include <vector>
#include <random>
#include <cmath>
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

template <typename ForwardIterator>
ForwardIterator remove_duplicates(ForwardIterator first, ForwardIterator last)
{
	auto new_last = first;

	for (auto current = first; current != last; ++current)
	{
		if (find(first, new_last, *current) == new_last)
		{
			if (new_last != current)
				*new_last = *current;
			++new_last;
		}
	}

	return new_last;
}

vector<int> mateSolutions(vector<int> parent1, vector<int> parent2)
{
	vector<int> solutionChild;
	int last = 0;

	for (int i = 0; i < floor(parent1.size() / 6); i++)
	{
		for (int j = i * 6; j < (i + 1) * 6; j++)
		{
			solutionChild.push_back(parent1.at(j));
		}

		for (int j = i * 6; j < (i + 1) * 6; j++)
		{
			solutionChild.push_back(parent2.at(j));
			last = j;
		}
	}

	for (int i = last; i < parent1.size() - 1; i++)
	{
		solutionChild.push_back(parent1.at(i));
	}

	for (int i = last; i < parent1.size() - 1; i++)
	{
		solutionChild.push_back(parent2.at(i));
	}

	solutionChild.erase(remove_duplicates(solutionChild.begin(), solutionChild.end()), solutionChild.end());
	return solutionChild;
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
	const int PARENT_SIZE = 1000;
	const int GENERATION_SIZE = 10000;

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
	vector<Solution*>solutions(GENERATION_SIZE);
	
	

	for (int i = 0; i < GENERATION_SIZE; i++)
	{
		shuffle(dummy_solution.begin(), dummy_solution.end(), default_random_engine(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count())));
		solutions.at(i) = new Solution(dummy_solution);
		solutions.at(i)->solutionFitness(cityGraphMatrix);
	}
	sortSolutionsByDistance(&solutions);

	double current_shortest_path = solutions.at(0)->distance;
	vector<Solution*> parents;
	
	for (int igen = 0; igen < 30; igen++) {

		
		copy(solutions.begin(), solutions.begin() + PARENT_SIZE, back_inserter(parents));


		solutions.clear();


		for (int i = 0; i < floor(PARENT_SIZE / 8); i++) {
			solutions.push_back(parents.at(i));
		}

		srand(time(0));
		for (int i = floor(PARENT_SIZE / 8); i < GENERATION_SIZE; i++) {
			solutions.push_back(new Solution(mateSolutions(parents.at((rand() % PARENT_SIZE))->solution, parents.at((rand() % PARENT_SIZE))->solution)));
			solutions.at(i)->solutionFitness(cityGraphMatrix);
		}

		sortSolutionsByDistance(&solutions);
		
		cout << "Best score for generation " << igen + 1 << " is: " << solutions.at(0)->distance << endl;
		cout << "Best path for genreation " << igen << "is: ";
		cout << "{ ";
		for (int i = 0; i < solutions.at(0)->solution.size(); i++)
		{
			cout << solutions.at(0)->solution.at(i) + 1;
			cout << " , ";
		}
		cout << " }";
		cout << endl;

		if (current_shortest_path == solutions.at(0)->distance) {
			break;
		}
		else {
			cout << "SOLUTION IS CONVERING!";
			current_shortest_path = solutions.at(0)->distance;
		}
		parents.clear();
	}
}
