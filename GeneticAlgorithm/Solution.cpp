#include "Solution.h"
#include <random>
#include <chrono>
#include <iostream>


//creating object of class solution with atrributes: solution(vector<int>), distance(int)
Solution::Solution(vector<int> solution) {
	this->solution = solution;
	this->solution.push_back(this->solution.at(0));
	this->distance = 0;
}

//calculating current solution fitness
double Solution::solutionFitness(double** cityGraph){

	for (int i = 0; i < this->solution.size() - 1; i++)
	{
		this->distance += cityGraph[this->solution.at(i)][this->solution.at(i + 1)];
	}

	return this->distance;
}

//overriding < operator 
bool operator<(const Solution& solution1, const Solution& solution2) {
	return solution1.distance < solution1.distance;
}
