all: word_frequencies hashtable_test ht_debug

word_frequencies: word_frequencies.cpp HashTable.o
	g++ word_frequencies.cpp -o word_frequencies HashTable.o

hashtable_test: hashtable_test.cpp HashTable.o
	g++ hashtable_test.cpp -o hashtable_test HashTable.o

ht_debug: ht_debug.cpp HashTable.o
	g++ ht_debug.cpp -o ht_debug HashTable.o

HashTable.o: HashTable.cpp HashTable.h
	g++ -c HashTable.cpp

clean:
	rm -f *.o word_frequencies hashtable_test ht_debug