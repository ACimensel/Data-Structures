#include <vector>		// for std::vector

// Sorts the two sorted subvectors using merge sort. Subvector 1 from "s" to "mid", subvector 2 from "mid"+1 to "e"
// PRE: assume passed in indeces are correct
// POST: the two subvectors are sorted
static void Merge(std::vector<int>& vec, std::vector<int>& tmpVec, int leftStart, int rightStart, int rightEnd) {
	int leftEnd = rightStart - 1;
	int tmpPos = leftStart;
	int numElements = rightEnd - leftStart + 1;

	while (leftStart <= leftEnd && rightStart <= rightEnd) {
		if (vec[leftStart] <= vec[rightStart])
			tmpVec[tmpPos++] = vec[leftStart++];
		else
			tmpVec[tmpPos++] = vec[rightStart++];
	}

	while (leftStart <= leftEnd)
		tmpVec[tmpPos++] = vec[leftStart++];

	while (rightStart <= rightEnd)
		tmpVec[tmpPos++] = vec[rightStart++];

	for (int i = 0; i < numElements; ++i, --rightEnd)
		vec[rightEnd] = tmpVec[rightEnd];
}

// Creates an int "mid" which is the middle point of the vector to divide in half. Makes recursive calls to itself and keeps dividing
//	the vector in half until all the subvectors are single elements. At that point it goes up the stack and sorts the subvectors using Merge()
// PRE: s < e, otherwise returns
// POST: recursively split the vector until base case is reached, then call Merge() to sort as going up the call stack
static void MS(std::vector<int>& vec, std::vector<int>& tmpVec, int s, int e) {
	if (s < e) {
		int mid = (s + e) / 2;

		// Sort first and second halves 
		MS(vec, tmpVec, s, mid);
		MS(vec, tmpVec, mid + 1, e);

		Merge(vec, tmpVec, s, mid + 1, e);
	}
}

// Driver function for the set of merge sort functions. Creates "tmpVec" to pass onto MS() which Merge() will use for its operations. Calls MS() to sort "vec"
// PRE: vector is initialized previously
// POST: array is fully sorted in ascending order
void MergeSort(std::vector<int>& vec) {
	if (vec.size() <= 1) { return; }

	std::vector<int> tmpVec(vec.size());

	MS(vec, tmpVec, 0, vec.size() - 1);
}