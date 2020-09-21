#include <vector>		// for std::vector
#include <algorithm>	// for std::swap

// maintains a sorted and unsorted section. finds the min element in the unsorted section and puts it at the end of the sorted section, and repeats
// PRE: vector is initialized previously
// POST: array is sorted
void SelectionSort(std::vector<int>& vec) {
	if (vec.size() <= 1) { return; }

	int minInd{ 0 };

	for (unsigned int start{ 0 }; start < vec.size(); start++) {
		minInd = start;
		for (unsigned int i{ start }; i < vec.size(); i++) {
			if (vec[i] < vec[minInd])
				minInd = i;
		}
		std::swap(vec[minInd], vec[start]);
	}
}