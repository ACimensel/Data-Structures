#include <vector>		// for std::vector

/*
//
// Stand-alone counting sort that would also sort by itself
//
void CountingSort(std::vector<int>& vec) {
	if (vec.size() <= 1) { return; }

	int maxValue{ vec[0] };
	for (const int& i : vec) {
		if (i > maxValue) { maxValue = i; }
	}

	std::vector<int> freqVec(maxValue + 1);
	for (const int& i : vec) {
		freqVec[i]++;
	}

	for (int i = 1; i <= maxValue; i++) {
		freqVec[i] += freqVec[i - 1];
	}

	std::vector<int> sortedVec(vec.size());
	for (int i = vec.size() - 1; i >= 0; i--) {
		sortedVec[--freqVec[vec[i]]] = vec[i];
	}

	vec = sortedVec;
}
*/

// Sorts the given vector according to the given digit/position 
// PRE: vector is initialized previously, correct radix is passed in, and the correct sequence of digits passed in by RadixSort()
// POST: array is sorted according to the given digit and is stable
static void CountingSortByDigit(std::vector<int>& vec, const int digit, const int radix) {
	int bucketIndex;
	std::vector<int> buckets(radix, 0);

	for (int i = 0; i < vec.size(); i++) {
		bucketIndex = ((vec[i]) / digit) % radix;
		buckets[bucketIndex]++;
	}

	for (int i = 1; i < radix; i++) {
		buckets[i] += buckets[i - 1];
	}

	std::vector<int> sortedVec(vec.size());

	for (int i = vec.size() - 1; i >= 0; i--) {
		bucketIndex = ((vec[i]) / digit) % radix;
		sortedVec[--buckets[bucketIndex]] = vec[i];
	}

	vec = sortedVec;
}

// Driver function for the set of radix sort functions, calls CountingSortByDigit() to sort values digit by digit and maintain stability
// PRE: vector is initialized previously, correct radix is passed in otherwise assumes radix of 10
// POST: array is fully sorted in ascending order while maintaining stability
void RadixSort(std::vector<int>& vec, const int radix) {
	if (vec.size() <= 1) { return; }

	int maxValue{ vec[0] };
	for (const int& i : vec) {
		if (i > maxValue) { maxValue = i; }
	}

	// starting with the least significant digit, perform couting sort on each digit/position
	int digit = 1;
	while (maxValue / digit >= 1) {
		CountingSortByDigit(vec, digit, radix);
		digit *= radix; // 1's, 10's, 100's, 1000's, etc. (if radix = 10)
	}
}