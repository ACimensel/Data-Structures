/******************************************************
  Heap.h -- Declarations for Basic Heap-of-Pair-of-Ints Class

  Stores pairs <element,priority> of ints.
  Supports O(log n) insertion, O(1) peeking at min priority and element 
  with min priority, and O(log n) extraction of element with min priority.
*******************************************************/
#include <iostream>
using namespace std;

class Heap{

public:
   // Constructors and Destructor

   // New empty Heap with default capacity.
   Heap();  

   // New empty Heap with capacity c.
   Heap(int c); 

   // New Heap with size s, consisting of pairs <Pi,Ei> where, 
   // for 0 <= i < s, Pi is Priorities[i] and Ei is value Elements[i].  
   // Capacity is s + c, where c is the "spare capacity" argument.
   // Requires: Priorities and Elements are of size at least s. 
   Heap( const int * Priorities, const int * Elements, int s, int c); 

   // New Heap with combined contents the two Heap arguments. 
   // Size of the new Heap is the sum of the sizes of argument Heaps.
   // Capacity of the new Heap is its size plus the "spare capacity" c.
   Heap( const Heap & Heap1, const Heap & Heap2, int c ); 

   // Destructor.
   ~Heap(); 

   // Accessors
   bool empty() const {return hSize == 0;}; // True iff Heap is empty.
   int size() const { return hSize ;} ; // Current size of Heap.
   int capacity() const { return hCapacity ;} ; // Current capacity.
   int peekMin() const { return A[0].element ;} // Peek at minimum priority element.
   int peekMinPriority() const { return A[0].priority ;} // Peek at minimum priority.

   // Modifiers
   void insert( int element, int priority ); // Insert the pair <element,priority>.
   int extractMin(); // Remove and return the highest (minimum) priority element.

   void printPQ() { // added for testing
	   for (int i = 0; i < hSize; i++) { std::cout << A[i].element << ':' << A[i].priority << ' '; }
	   std::cout << std::endl;
   }

private:
   class Pair{
      public:
        int element ;
        int priority ;
   };

	#define DFLT_ARRAY_SIZE 10

   Pair* A ; // Array containing heap contents.
   int hCapacity ; // Max number of elements (= size of A).
   int hSize ; // Current number of elements.

   // Repairs ordering invariant after adding leaf at A[i].
   void trickleUp(int i);

   // Repairs ordering invariant for sub-tree rooted at index i,
   //   when A[i] may be have larger priority than one of its children,
   //   but the subtrees of its children are heaps.
   void trickleDown(int i);

   // Establishes ordering invariant for entire array contents.
   void heapify(); //(Same as "make_heap" in lectures.)

   // Useful for implementing trickle up and down
   void swap(int i,int j);
};

// default constructor
Heap::Heap()
	: hSize{ 0 }, hCapacity{ DFLT_ARRAY_SIZE }, A{ new Pair[DFLT_ARRAY_SIZE] }
{
}
 
// constructor which creates a heap of capacity c
Heap::Heap(int c) // New empty Heap with capacity c.
	: hSize{ 0 }, hCapacity{ c }, A{ new Pair[c] }
{ 
}

// New Heap construcor with capacity c+s, with s elements, consisting of pairs <Pi,Vi> where 
//  Pi is Priorities[i], Ei is value Elements[i], for 0 <= i < s.
Heap::Heap( const int * Priorities, const int * Elements, int s, int c) 
	: hSize{ 0 }, hCapacity{ s + c }, A{ new Pair[s + c] }
{
	for (int i{ 0 }; i < s; i++) { insert(Elements[i], Priorities[i]); }
}

// New Heap constructor with combined contents and of the two given heaps.
Heap::Heap( const Heap & Heap1, const Heap & Heap2, int c )
	: hSize{ 0 }, hCapacity{ Heap1.hSize + Heap2.hSize + c }, A{ new Pair[Heap1.hSize + Heap2.hSize + c] }
{
	for (int i{ 0 }; i < Heap1.hSize; i++, hSize++) { A[i] = Pair{ Heap1.A[i].element, Heap1.A[i].priority }; }
	for (int i{ 0 }; i < Heap2.hSize; i++, hSize++) { A[Heap1.hSize + i] = Pair{ Heap2.A[i].element, Heap2.A[i].priority }; }
	heapify();
}

// Destructor
Heap::~Heap()
{
	delete[] A;
}

// Modifiers

// inserts element/value at end and bubbles it up if needed to maintain priority queue (heap) properties
// PRE: there is space left in the heap, hSize < hCapacity
// POST: new Pair bubbled up according to priority
void Heap::insert(int element, int priority)
{
	if (hSize >= hCapacity) { exit(1); } // exit if full, not implementing resizing
	A[hSize].element = element;
	A[hSize].priority = priority;
	trickleUp(hSize);
	hSize++;
}

// Repairs the heap ordering invariant after adding a new element.
// Initial call should be trickleUp(hSize-1).
// PRE: index i is not <=0
// POST: bubble up Pair up the heap according to priority
void Heap::trickleUp(int i)
{
	if (i <= 0) { return; }

	int pInd{ (i - 1) / 2 };
	if (A[i].priority < A[pInd].priority) { swap(i, pInd); }
	else { return; }

	trickleUp(pInd);
}

void Heap::swap(int i, int j)
{
   Pair temp = A[i];
   A[i] = A[j];
   A[j] = temp ;
}

// Removes and returns the element with highest priority.
// (That is, the element associated with the minimum priority value.)
// PRE: there is at least 1 Pair to extract element from
// POST: returns the element with the highest priority and removes that Pair, while maintaining priority queue properties
int Heap::extractMin()
{
	if (hSize <= 0) { exit(1); }

	int retVal{ A[0].element };
	swap(hSize - 1, 0);
	hSize--;

	if (hSize) { trickleDown(0); }

	return retVal;
}

// Repairs the heap ordering invariant after replacing the root.
// (extractMin() calls trickleDown(0)).
// (trickleDown(i) performs the repair on the subtree rooted a A[i].)
// (heapify() calls trickleDown(i) for i from (hSize/2)-1 down to 0.)
// PRE: index is valid and not out of bounds
// POST: subtree is in heap form
void Heap::trickleDown(int i)
{
	int smallest = i;
	int l = i * 2 + 1;
	int r = i * 2 + 2;

	if (l < hSize && A[l].priority < A[smallest].priority) { smallest = l; }
	if (r < hSize && A[r].priority < A[smallest].priority) { smallest = r; }

	if (smallest != i) {
		swap(i, smallest);
		trickleDown(smallest);
	}
}

// Turns A[0] .. A[size-1] into a heap.
void Heap::heapify()
{
   for( int i = (hSize/2)-1; i>=0 ; i-- ) trickleDown(i);  
}