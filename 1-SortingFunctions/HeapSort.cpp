#include <vector>		// for std::vector
#include <algorithm>	// for std::swap

// takes a vector and the index of a subtree and heapifies the subtree
// PRE: vector is initialized previously, index is valid, size is correct (decrementing) as heap is being sorted with HeapSort()
// POST: subtree is in heap form
static void Heapify(std::vector<int>& vec, int rootInd, int size) { // MAX HEAP
	int largest = rootInd;
	int l = rootInd * 2 + 1;
	int r = rootInd * 2 + 2;

	if (l < size && vec[l] > vec[largest]) { largest = l; }
	if (r < size && vec[r] > vec[largest]) { largest = r; }
	
	if (largest != rootInd) {
		std::swap(vec[largest], vec[rootInd]);
		Heapify(vec, largest, size);
	}
}

// takes a vector and turns it into a heap with the bottom up approach using heapify on all non leaf subtrees
// PRE: vector is initialized previously
// POST: array is partially sorted (is in heap form)
static void MakeHeap(std::vector<int>& vec) {
	for (int lastNonLeadNodeInx = (vec.size() / 2) - 1; lastNonLeadNodeInx > -1; lastNonLeadNodeInx--) {
		Heapify(vec, lastNonLeadNodeInx, vec.size());
	}
}

// driver function for heapsort, turns unsorted vector into a max heap. sorts the heap in ascending order
// PRE: vector is initialized previously
// POST: array is fully sorted in ascending order
void HeapSort(std::vector<int>& vec) {
	if (vec.size() <= 1) { return; }

	MakeHeap(vec);
	
	for (int lastUnsorted = vec.size() - 1; lastUnsorted > 0; lastUnsorted--) {
		std::swap(vec[0], vec[lastUnsorted]);
		Heapify(vec, 0, lastUnsorted);
	}
}