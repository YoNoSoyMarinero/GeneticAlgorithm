#include "DummySolutions.h"

//creating dummy solutions from 0 to N
void DummySolutions::createDummySolutions(vector<int>* dummy_solutions) {
	for (int i = 0; i < dummy_solutions->size(); i++)
	{
		dummy_solutions->at(i) = i;
	}
}