#pragma once
#include <string>
#include <vector>

using namespace std;

class ReadCityFile
{
public:
	//reading file
	static vector<string>* readFile();

	//count cities
	static int cityCount();
};
