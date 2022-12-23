#include "CityMap.h"
#include "City.h"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

//creating vector of cities from an array of strings(read_lines from .txt file)
vector<City>* CityMap::createMap(vector<string>* read_lines, int number_of_cities){
	vector<City>* cities = new vector<City>();
	for (size_t i = 0; i < number_of_cities; i++)
	{
		int city_name = 0;
		int postion_x = 0;
		int postion_y = 0;
		string read_line = read_lines->at(i);
		char* line = const_cast<char*>(read_line.c_str());

		char* word = strtok(line, " ");
		city_name = stoi(word);

		word = strtok(NULL, " ");
		postion_x = stoi(word);

		word = strtok(NULL, " ");
		postion_y = stoi(word);

		cities->push_back(City(postion_x, postion_y, city_name));
	}

	return cities;
}
