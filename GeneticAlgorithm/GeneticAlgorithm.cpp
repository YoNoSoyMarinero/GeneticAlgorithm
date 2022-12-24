#include "GeneticAlgorithm.h"


vector<int> GeneticAlgorithm::mateSolutions(vector<int> parent1, vector<int> parent2, int substring_percent)
{
	vector<int> solutionChild;
	int last = 0;

	for (int i = 0; i < floor(parent1.size() / substring_percent); i++)
	{
		for (int j = i * substring_percent; j < (i + 1) * substring_percent; j++)
		{
			if (!count(solutionChild.begin(), solutionChild.end(), parent1.at(j)))
			{
				solutionChild.push_back(parent1.at(j));
			}
		}

		for (int j = i * substring_percent; j < (i + 1) * substring_percent; j++)
		{
			if (!count(solutionChild.begin(), solutionChild.end(), parent2.at(j)))
			{
				solutionChild.push_back(parent2.at(j));
			}
		}
	}

	for (int i = last; i < parent1.size() - 1; i++)
	{
		if (!count(solutionChild.begin(), solutionChild.end(), parent1.at(i)))
		{
			solutionChild.push_back(parent1.at(i));
		}
	}

	for (int i = last; i < parent1.size() - 1; i++)
	{
		if (!count(solutionChild.begin(), solutionChild.end(), parent1.at(i)))
		{
			solutionChild.push_back(parent2.at(i));
		}
	}

	return solutionChild;
}


//mutates solutions
void GeneticAlgorithm::mutateSolution(vector<int>* solution, int number_of_mutations)
{
	for (int i = 0; i < rand() % 3; i++)
	{
		iter_swap(solution->begin() + (rand() % (solution->size() - 2)) + 1, solution->begin() + (rand() % (solution->size() - 2)));
	}
}
