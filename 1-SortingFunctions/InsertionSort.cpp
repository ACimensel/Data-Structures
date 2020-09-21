#include <vector>		// for std::vector
#include <algorithm>	// for std::swap

// maintains a sorted and unsorted section. sorts the first element in the unsorted section in the right place in the sorted section, and repeats
// PRE: vector is initialized previously
// POST: array is sorted
void InsertionSort(std::vector<int>& vec) {
	if (vec.size() <= 1) { return; }

	for (int sorted = 1; sorted < vec.size(); sorted++) {
		for (int comp = sorted; comp > 0; comp--) {
			if (vec[comp] < vec[comp - 1]) { std::swap(vec[comp], vec[comp - 1]); }
		}
	}
}