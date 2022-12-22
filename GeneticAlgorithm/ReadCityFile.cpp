#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "ReadCityFile.h"


using namespace std;
vector<string>* ReadCityFile::readFile() {
	vector<string>* read_lines = new vector<string>();
	fstream myFile;
	myFile.open("data_tsp.txt", ios::in);

	if (myFile.is_open()) {
		string line;

		while (getline(myFile, line))
		{
			read_lines->push_back(line);
		}

		return read_lines;

		myFile.close();
	}
}


int ReadCityFile::cityCount(){
	int counter = 0;
	fstream myFile;
	myFile.open("data_tsp.txt", ios::in);

	if (myFile.is_open()) {
		string line;

		while (getline(myFile, line))
		{
			counter++;
		}

		return counter;

		myFile.close();
	}
}