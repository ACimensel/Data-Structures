#include <vector>		// for std::vector
#include <algorithm>	// for std::swap

// Choses a random element to be the pivot point. Sorts the pivot element and returns the sorted pivot index back to QS()
// PRE: s < e
// POST: the pivot element is sorted, and returned
static int PartitionRand(std::vector<int>& v, int s, int e) {
	int r = (rand() % (e - s + 1)) + s; // get a random index from s to e
	std::swap(v[r], v[e]); // swap the value of the random index with the end

	int piv = v[e]; // pivot  
	int i = s - 1; // Index of smaller element  

	for (int j = s; j <= e - 1; j++) {
		if (v[j] < piv) {  // If current element is smaller than the pivot  
			i++; // increment index of smaller element  
			std::swap(v[i], v[j]);
		}
	}
	std::swap(v[i + 1], v[e]);
	return (i + 1);
}

// Checks to see if vector or sub vector has 1 or two elements left to sort which are the base cases, sorts if 2 elements left. If not 
//	calls PartitionRand() to sort the pivot element and get the pivot index back. Divides up the vector and makes two recursive calls 
//	to itself to sort vector on both sides of the pivot element not including the pivot element
// PRE: s < e, otherwise return
// POST: the pivot element is sorted, the elements on either side of it are partially sorted (left: less than, right: greater than), call itself again until fully sorted
static void QS(std::vector<int>& vec, int s, int e) {
	if (s >= e) { return; }
	if (s + 1 == e) {
		if (vec[s] > vec[e]) {
			std::swap(vec[s], vec[e]);
		}
		return;
	}

	int pivInd = PartitionRand(vec, s, e);

	QS(vec, s, pivInd - 1);
	QS(vec, pivInd + 1, e);
}

// Driver function for the set of quick sort functions, calls QS() to sort "vec"
// PRE: vector is initialized previously
// POST: array is fully sorted in ascending order
void QuickSort(std::vector<int>& vec) {
	if (vec.size() <= 1) { return; }

	QS(vec, 0, vec.size() - 1);
}
