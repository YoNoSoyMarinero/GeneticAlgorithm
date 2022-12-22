#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "City.h"
#include <vector>
#include <string>

using namespace std;


class CityMap
{
public:
	static vector<City>* createMap(vector<string>* read_lines, int numbe_of_cities);
};

