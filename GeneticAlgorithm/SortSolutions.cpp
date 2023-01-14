#include "SortSolutions.h"

//sorting solutions by distance in ascending order
void SortSolutions::sortSolutionsByDistance(vector<Solution*>* solutions) {
	int i, j;

	for (i = 0; i < solutions->size() - 1; i++) {
		for (j = 0; j < solutions->size() - i - 1; j++) {
			if (solutions->at(j)->distance > solutions->at(j + 1)->distance)
				swap(solutions->at(j), solutions->at(j + 1));
		}
	}
}