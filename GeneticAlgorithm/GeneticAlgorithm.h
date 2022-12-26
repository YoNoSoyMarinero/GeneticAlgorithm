#pragma once
#include <vector>
#include <random>


using namespace std;

class GeneticAlgorithm
{
public:
	static vector<int> mateSolutions(vector<int>* parent1, vector<int>* parent2,int substring_percent);

	static void mutateSolution(vector<int>* solution, int number_of_mutations);
};

