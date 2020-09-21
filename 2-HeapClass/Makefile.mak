
all: test1 test2 test3 test4

test1: test1.o 
	g++ -o test1 test1.o 

test2: test2.o 
	g++ -o test2 test2.o 

test3: test3.o
	g++ -o test3 test3.o 

test4: test4.o
	g++ -o test4 test4.o 
	
test1.o: test1.cpp heap.h
	g++ -c test1.cpp 

test2.o: test2.cpp heap.h
	g++ -c test2.cpp 

test3.o: test3.cpp heap.h
	g++ -c test3.cpp 

test4.o: test4.cpp heap.h
	g++ -c test4.cpp 

clean:
	rm -f test1 test2 test3 test4 *.o  

t1:
	./test1
	
t2:
	./test2
	
t3:
	./test3
	
t4:
	./test4
	
vg1:
	valgrind --leak-check=full --show-leak-kinds=all ./test1
	
vg2:
	valgrind --leak-check=full --show-leak-kinds=all ./test2
	
vg3:
	valgrind --leak-check=full --show-leak-kinds=all ./test3
	
vg4:
	valgrind --leak-check=full --show-leak-kinds=all ./test4
