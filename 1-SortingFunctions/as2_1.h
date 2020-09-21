#pragma once

// Some global constants to adjust the settings of the outputted table
const int G_WIDTH1 = 14;
const int G_WIDTH2 = 18;
const int G_WIDTH3 = 4;
const int G_PRECISION = 5;

// Array Size!
const int ARRAY_SIZE = 20000; // CHANGE THIS

void BubbleSort(std::vector<int>& vec);
void SelectionSort(std::vector<int>& vec);
void InsertionSort(std::vector<int>& vec);
void QuickSort(std::vector<int>& vec);
void MergeSort(std::vector<int>& vec);
void HeapSort(std::vector<int>& vec);
void RadixSort(std::vector<int>& vec, const int radix = 10);