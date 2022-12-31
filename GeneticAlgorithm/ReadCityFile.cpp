#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "ReadCityFile.h"


using namespace std;

//reading file and returing array of strings that represents each city's name and postion
vector<string>* ReadCityFile::readFile() {
	vector<string>* read_lines = new vector<string>();
	fstream myFile;
	myFile.open("cities.txt", ios::in);

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

//counting cities in file
int ReadCityFile::cityCount(){
	int counter = 0;
	fstream myFile;
	myFile.open("cities.txt", ios::in);

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