// Implement HashTable methods.
#include <iostream>     // std::cout, std::endl
#include <iomanip>      // std::setw
#include <cmath>
#include <string>
#include "HashTable.h"
using namespace std;

bool HashTable::insert(const string& key, int value) {
	// Try to insert key,value pair at pval, increment by probe function.
	int hval = hash(key);
	int pval = hval;

	for (int iter=0; iter<tsize; iter++) {
		if (sentinels[pval] != curr_used) {
			// Found an empty spot, insert the (key,value) pair here.
			sentinels[pval] = curr_used;
			keys[pval] = key;
			values[pval] = value;
			nstored++;
			return true;
		}
		pval = probeFunction(hval,iter);
	}
	return false;
}

// looks for key/value in hash table. if it exists and is still in use (sentinel == 1), set sentinel to -1 (this "removes" it)
// PRE: key/value pair must exist in hash table
// POST: removes key/value pair if it exists in hash table and is in use
bool HashTable::remove(const string& key, int value) {
	int hashKey = hash(key);

	for (int i = 0; i < tsize; i++) {
		int trythiskey = probeFunction(hashKey, i);

		if (sentinels[trythiskey] == 0) { return false; }
		else if (sentinels[trythiskey] == 1) { 
			if (keys[trythiskey] == key && values[trythiskey] == value) {
				sentinels[trythiskey] = -1;
				return true;
			}
		}
	}
	return false;
}


// looks for key in hash table. if it exists and is still in use, copy its value into the passed in "int& value" variable
// PRE: key must exist in hash table
// POST: modifies the value of the variable passed in as an argument
bool HashTable::lookup(const string& key, int& value) {
	int hashKey = hash(key);

	for (int i = 0; i < tsize; i++) {
		int trythiskey = probeFunction(hashKey, i);

		if (sentinels[trythiskey] == 0) { return false; }
		else if (sentinels[trythiskey] == 1) {
			if (keys[trythiskey] == key) {
				value = values[trythiskey];
				return true;
			}
		}
	}
	return false;
}


// looks for key in hash table. if it exists and is still in use, modify its value to the passed in "value" variable
// PRE: key must exist in hash table
// POST: modifies the value of the key pair in the hash table to the value that was passed in as an argument
bool HashTable::modify(const string& key, int value) {
	int hashKey = hash(key);

	for (int i = 0; i < tsize; i++) {
		int trythiskey = probeFunction(hashKey, i);

		if (sentinels[trythiskey] == 0) { return false; }
		else if (sentinels[trythiskey] == 1) {
			if (keys[trythiskey] == key) {
				values[trythiskey] = value;
				return true;
			}
		}
	}
	return false;
}


void HashTable::getKeys(string*& all_keys, int& nkeys) {
	// Allocate an array to hold all the keys in the table.
	all_keys = new string[nstored];
	nkeys = nstored;


	// Walk the table's array.
	int key_i=0;
	for (int i=0; i<tsize; i++) {
		if (sentinels[i]==curr_used) {
			// Debug check: there shouldn't be more sentinels at curr_used than nstored thinks.
			if (key_i > nkeys) {
				cerr << "Error: more keys in table than nstored reports." << endl;
			}

			all_keys[key_i] = keys[i];
			key_i++;
		}
	}
}

int HashTable::numStored() {
	return nstored;
}


int HashTable::hash(const string& key) {
	return smarterHash(key);
}


int HashTable::probeFunction(int val, int iter) {
	// Linear probing.
	return (val + iter) % tsize;
}


int HashTable::sillyHash(const string& key) {
	return tsize/2;
}

// djb2 implementation for strings, less collisions than horner's method in tests i ran, and fast
// PRE: key is non empty
// POST: return hash value modded with tsize
int HashTable::smarterHash(const string& key) {
	unsigned long hash = 5381;
	for (int i{ 0 }, c{ key[0] }; i < key.size(); c = key[++i]) { hash = ((hash << 5) + hash) + c; } // hash * 33 + c

	return hash % tsize;
}


HashTable::HashTable() {
	init(default_size);
}


HashTable::HashTable(int nkeys) {
	init(4*nkeys);
}


void HashTable::init(int tsizei) {
	tsize = tsizei;
	nstored = 0;

	keys = new string[tsize];
	values = new int[tsize];
	sentinels = new int[tsize];

	// Initialize all sentinels to 0.
	for (int i=0; i<tsize; i++)
		sentinels[i]=0;
}



HashTable::~HashTable() {
	delete[] keys;
	delete[] values;
	delete[] sentinels;
}


void HashTable::printTable() {
	// Print the current state of the hashtable.
	// Note, prints actual data structure contents, entry might not be "in" the table if sentinel not curr_used.
	// left, setw() are part of <iomanip>

	// Find longest string.
	const int indw = 5;
	int long_string = 3; // Length of "Key", nice magic number.
	const int intw = 10;
	const int sentw = 8;
	for (int i=0; i<tsize; i++) {
		if (keys[i].length() > long_string)
			long_string = keys[i].length();
	}

	// Print title
	cout << setw(indw) << left << "Index" << " | " << setw(long_string) << left << "Key" << " | " << setw(intw) << "Value" << " | " << "Sentinel" << endl;

	// Print a separator.
	for (int i=0; i < indw+long_string+intw+sentw+9; i++) {
		cout << "-";
	}
	cout << endl;

	// Print each table row.
	for (int i=0; i<tsize; i++) {
		cout << setw(indw) << left << i << " | " << setw(long_string) << left << keys[i] << " | " << setw(intw) << values[i] << " | " << sentinels[i] << endl;
	}

	// Print a separator.
	for (int i=0; i < indw+long_string+intw+sentw+9; i++) {
		cout << "-";
	}
	cout << endl;

}
