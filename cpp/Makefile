all: bin bin/z1 bin/z4

bin:
	mkdir bin

bin/z1: z1.o stack.o
	g++ z1.o stack.o -o bin/z1

bin/z4: z4.o
	g++ z4.o -o bin/z4

z4.o: z4.cpp
	g++ z4.cpp -c -o z4.o

z1.o: z1.cpp
	g++ z1.cpp -c -o z1.o

array.o: array.cpp array.h
	g++ array.cpp -c -o array.o

forwardlist.o: forwardlist.cpp forwardlist.h
	g++ forwardlist.cpp -c -o forwardlist.o

list.o: list.cpp list.h
	g++ list.cpp -c -o list.o

queue.o: queue.cpp queue.h
	g++ queue.cpp -c -o queue.o

rbtree.o: rbtree.cpp rbtree.h
	g++ rbtree.cpp -c -o rbtree.o

stack.o: stack.cpp stack.h
	g++ stack.cpp -c -o stack.o

clean:
	rm -f *.o