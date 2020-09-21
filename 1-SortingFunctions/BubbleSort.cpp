#include <vector>		// for std::vector
#include <algorithm>	// for std::swap

// repeatedly swaps the adjacent elements if they are in wrong order. stops early if it went for a whole iteration without a swap
// PRE: vector is initialized previously
// POST: array is sorted
void BubbleSort(std::vector<int>& vec) {
	if (vec.size() <= 1) { return; }

	bool swapped = false;
	do {
		swapped = false;
		for (int i = 1; i < vec.size(); i++) {
			if (vec[i] < vec[i - 1]) { 
				std::swap(vec[i], vec[i - 1]); 
				swapped = true;
			}
		}
	} while (swapped);
}