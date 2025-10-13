all: bin bin/z1 bin/z2 bin/z3 bin/z4 bin/z5 bin/z6a bin/z6 bin/z7

bin:
	mkdir bin

bin/z7: z7.o lfu.o
	g++ z7.o lfu.o -o bin/z7

z7.o: z7.cpp
	g++ z7.cpp -c -o z7.o

bin/z6: z6.o hashtabledouble.o
	g++ z6.o hashtabledouble.o -o bin/z6

z6.o: z6.cpp
	g++ z6.cpp -c -o z6.o

bin/z6a: z6a.o hashtabledouble.o hashtablecuckoo.o
	g++ z6a.o hashtabledouble.o hashtablecuckoo.o -o bin/z6a

z6a.o: z6a.cpp
	g++ z6a.cpp -c -o z6a.o

bin/z2: z2.o set.o
	g++ z2.o set.o -o bin/z2

z2.o: z2.cpp
	g++ z2.cpp -c -o z2.o

bin/z3: z3.o set.o
	g++ z3.o set.o -o bin/z3

z3.o: z3.cpp
	g++ z3.cpp -c -o z3.o

bin/z1: z1.o stack.o
	g++ z1.o stack.o -o bin/z1

bin/z4: z4.o
	g++ z4.o -o bin/z4

bin/z5: z5.o
	g++ z5.o -o bin/z5

z5.o: z5.cpp
	g++ z5.cpp -c -o z5.o

z4.o: z4.cpp
	g++ z4.cpp -c -o z4.o

z1.o: z1.cpp
	g++ z1.cpp -c -o z1.o

stack.o: stack.cpp stack.h
	g++ stack.cpp -c -o stack.o

set.o: set.cpp set.h
	g++ set.cpp -c -o set.o

lfu.o: lfu.cpp lfu.h
	g++ lfu.cpp -c -o lfu.o

hashtabledouble.o: hashtabledouble.cpp hashtabledouble.h
	g++ hashtabledouble.cpp -c -o hashtabledouble.o

hashtablecuckoo.o: hashtablecuckoo.cpp hashtablecuckoo.h
	g++ hashtablecuckoo.cpp -c -o hashtablecuckoo.o

clean:
	rm -f *.o