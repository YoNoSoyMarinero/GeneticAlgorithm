#pragma once
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

class TicketsPool
{
public:
	vector<int> tickets_vector;

	TicketsPool(vector<int> tickets_vector);

	void createTicketsVector(int parent_size);
};

