#include <iostream>		// for std::cout
#include <vector>		// for std::vector
#include <time.h>       // for time(NULL)
#include <chrono>		// for chrono timer
#include <iomanip>		// for table manipulators
#include <string>		// for std::to_string()
#include "AVL.h"
#include "as2_1.h"

void SetUpVec(std::vector<int>& vec, int option);
void FillInTable(int option);
void PrintVec(std::vector<int>& intv);
void RandomizeVector(std::vector<int>& vec, int maxVal = RAND_MAX, int minVal = 0);

// Timer class will save start time when instantiated (by calling Reset(). 
// When GetTime() is called it will save the end time, calculate
// the duration (end minus start time) and return the difference. 
class Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start, m_end;
	std::chrono::duration<float> m_duration;

public:
	// start timer in contructor when a timer object is created
	Timer() { Reset(); }

	void Reset() {
		m_duration = std::chrono::nanoseconds::zero();
		m_start = std::chrono::high_resolution_clock::now();
	}

	float GetTime() {
		m_end = std::chrono::high_resolution_clock::now();
		m_duration = m_end - m_start;

		return m_duration.count();
	}
};

// Change ARRAY_SIZE in the as2.h header file if needed
int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << "Array [n=" + std::to_string(ARRAY_SIZE) + "]";
	std::cout << std::left << std::setw(G_WIDTH3) << std::setfill(' ') << "|";
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << "Bubble Sort";
	std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << "Selection Sort";
	std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << "Insertion Sort";
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << "Merge Sort";
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << "Quick Sort";
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << "Heap Sort";
	std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << "Balanced BST";
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << "Radix Sort";
	std::cout << '\n';

	FillInTable(1); // random: 0 to RAND_MAX values
	FillInTable(2); // random: 0 to 5 values
	FillInTable(3); // sorted values, 0 to ARRAY_SIZE-1
	FillInTable(4); // reverse sorted values, ARRAY_SIZE to 1

	std::cout << "\nDONE! **all times are in seconds**\n";

	return 0;
}

// Sets up the vector that is passed in by reference in one of four ways, for the 4 test cases
//	random: 0 - RAND_MAX, random: 0 - 5, sorted, and sorted in reverse
// PRE: valid option from 1-4 is given, vector of needed size is created beforehand
// POST: referenced vector is set up according to the option that was passed in
void SetUpVec(std::vector<int>& vec, int option) {
	if		(option == 1) { RandomizeVector(vec, RAND_MAX); }
	else if (option == 2) { RandomizeVector(vec, 5); }
	else if (option == 3) { for (int i = 0; i < vec.size(); i++) { vec[i] = i; } }
	else if (option == 4) { for (int i = 0; i < vec.size(); i++) { vec[i] = ARRAY_SIZE - i; } }
}

// Prints the table of times, and calls functions to sort, and counts time to sort
// PRE: valid option is passed in (only 1-4)
// POST: sets up and prints the table of times, assuming the sort functions work correctly
void FillInTable(int option) {

	if		(option == 1) { std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << "Rand: 0-RAND_MAX"; }
	else if (option == 2) { std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << "Rand: 0-5"; }
	else if (option == 3) { std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << "Sorted:"; }
	else if (option == 4) { std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << "Sorted: Reverse"; }

	std::cout << std::left << std::setw(G_WIDTH3) << std::setfill(' ') << '|';
	
	std::vector<int> vec(ARRAY_SIZE);
	Timer t;

	SetUpVec(vec, option);
	//PrintVec(vec);
	t.Reset();
	BubbleSort(vec);
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << t.GetTime();
	//PrintVec(vec);

	SetUpVec(vec, option);
	//PrintVec(vec);
	t.Reset();
	SelectionSort(vec);
	std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << t.GetTime();
	//PrintVec(vec);

	SetUpVec(vec, option);
	//PrintVec(vec);
	t.Reset();
	InsertionSort(vec);
	std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << t.GetTime();
	//PrintVec(vec);

	SetUpVec(vec, option);
	//PrintVec(vec);
	t.Reset();
	MergeSort(vec);
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << t.GetTime();
	//PrintVec(vec);

	SetUpVec(vec, option);
	//PrintVec(vec);
	t.Reset();
	QuickSort(vec);
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << t.GetTime();
	//PrintVec(vec);

	SetUpVec(vec, option);
	//PrintVec(vec);
	t.Reset();
	HeapSort(vec);
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << t.GetTime();
	//PrintVec(vec);

	AVL avl;
	t.Reset();
	if		(option == 1) { for (int i = 0; i < ARRAY_SIZE; i++) { avl.insert(rand() % (RAND_MAX + 1)); } }
	else if (option == 2) { for (int i = 0; i < ARRAY_SIZE; i++) { avl.insert(rand() % 6); } }
	else if (option == 3) { for (int i = 0; i < ARRAY_SIZE; i++) { avl.insert(i); } }
	else if (option == 4) { for (int i = 0; i < ARRAY_SIZE; i++) { avl.insert(ARRAY_SIZE - i); } }
	std::cout << std::left << std::setw(G_WIDTH2) << std::setfill(' ') << t.GetTime();
	//avl.inOrder();

	SetUpVec(vec, option);
	//PrintVec(vec);
	t.Reset();
	RadixSort(vec);
	std::cout << std::left << std::setw(G_WIDTH1) << std::setfill(' ') << t.GetTime();
	//PrintVec(vec);

	std::cout << std::endl;
}

// randomizes the values in the vector with values minVal to maxVal (inclusive)
// PRE: vector is already initialized, maxVal >= minVal
// POST: elements are randomized with values from minVal to maxVal (inclusive)
void RandomizeVector(std::vector<int>& vec, int maxVal, int minVal) {
	for (auto& i : vec) {
		i = (rand() % (maxVal + 1 - minVal)) + minVal;
	}
}

// Used for testing to print the vector values, to confirm sort functions worked
// PRE: vector is already initialized
// POST: prints vector values from intv[0] to intv[intv.size()-1]
void PrintVec(std::vector<int>& intv) {
	for (const int& i : intv) { std::cout << i << '\n'; }
	std::cout << std::endl;
}