#pragma once
#include <vector>

using namespace std;


class Solution
{
public:
	vector<int> solution;
	double distance;
	Solution(vector<int> solution);
	
	double solutionFitness(double** cityGraph);
};

