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
#include "GeneticAlgorithm.h"
#include "TicketsPool.h"
#include "DummySolutions.h"
#include "SortSolutions.h"


using namespace std;


//main function implements Genetic Alorithm that finds shortest path between cities
int main()
{
	//Defining constants

	const int PARENT_SIZE = 100; //number of parents
	const int GENERATION_SIZE = 1000; //number of solutions in population
	const int N_GENERATION = 150; //number of generation
	const int N_MUTATIONS = 5; //maximal number of possible mutation
	const int N_SUBPATHS_IN_MATING = 6; //number of subpaths in mating function
	const int NTH_PART_OF_SURVIVED_PARENTS = 5; //part of parents that survives to the next generation
	
	//Number of cities
    int number_of_cities = ReadCityFile::cityCount();

	//Reading data and creating graph(LUT of distances)
	vector<City>* cities_in_file = CityMap::createMap(ReadCityFile::readFile(), number_of_cities);
	double** cityGraphMatrix = CityGraph::getGraph(cities_in_file, number_of_cities);


	//Creating and simulating generation 0
	vector<int> dummy_solution(number_of_cities);
	DummySolutions::createDummySolutions(&dummy_solution);
	vector<Solution*>solutions(GENERATION_SIZE);
	vector<int> vectorTickets;
	TicketsPool ticket_pool(vectorTickets);
	ticket_pool.createTicketsVector(PARENT_SIZE);
	
	for (int i = 0; i < GENERATION_SIZE; i++)
	{
		shuffle(dummy_solution.begin(), dummy_solution.end(), default_random_engine(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count())));
		solutions.at(i) = new Solution(dummy_solution);
		solutions.at(i)->solutionFitness(cityGraphMatrix);
	}
	SortSolutions::sortSolutionsByDistance(&solutions);

	vector<Solution*> parents;
	

	//Genetic Algorithm simulation (Evolution)
	for (int igen = 0; igen < N_GENERATION; igen++) {

		//creating parents
		copy(solutions.begin(), solutions.begin() + PARENT_SIZE, back_inserter(parents));
		solutions.clear();
		for (int i = 0; i < floor(PARENT_SIZE / NTH_PART_OF_SURVIVED_PARENTS); i++) {
			solutions.push_back(parents.at(i));
		}

		//creating new children and mutating them
		srand(time(0));
		for (int i = floor(PARENT_SIZE / NTH_PART_OF_SURVIVED_PARENTS); i < GENERATION_SIZE; i++) {
			solutions.push_back(new Solution(GeneticAlgorithm::mateSolutions(&parents.at(ticket_pool.tickets_vector.at(rand() % ticket_pool.tickets_vector.size()))->solution, &parents.at(ticket_pool.tickets_vector.at(rand() % ticket_pool.tickets_vector.size()))->solution, N_SUBPATHS_IN_MATING)));
			solutions.at(i)->solutionFitness(cityGraphMatrix);
			GeneticAlgorithm::mutateSolution(&(solutions.at(i)->solution), N_MUTATIONS);
		}

		//sorting solutions and displaying the best one in given generation
		SortSolutions::sortSolutionsByDistance(&solutions);
		cout << "Best score for generation " << igen + 1 << " is: " << solutions.at(0)->distance << endl;
		cout << "Best path for genreation " << igen + 1 << " is: ";
		cout << "{ ";
		for (int i = 0; i < solutions.at(0)->solution.size(); i++)
		{
			cout << solutions.at(0)->solution.at(i) + 1;
			cout << " -> ";
		}
		cout << " end }";
		cout << endl;

		parents.clear();
	}
}
