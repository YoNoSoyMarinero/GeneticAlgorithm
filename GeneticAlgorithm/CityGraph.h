#pragma once
#include "City.h"
#include <vector>

using namespace std;

class CityGraph
{
public:
	static double** getGraph(vector<City>* cities_in_file, int number_of_cities);
};

