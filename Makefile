# Trivial makefile for the assignment 5.
# Po-Chun Chiu & Yujie Liu

# Note that rule for goal (parse) must be the first one in this file.

all: foo1 foo2 foo3 foo4 foo5 foo6 foo7 foo8

clean:
	rm *.o

foo1: foo1.cpp tombstones.h
	g++ -o foo1.o foo1.cpp
foo2: foo2.cpp tombstones.h
	g++ -o foo2.o foo2.cpp
foo3: foo3.cpp tombstones.h
	g++ -o foo3.o foo3.cpp
foo4: foo4.cpp tombstones.h
	g++ -o foo4.o foo4.cpp
foo5: foo5.cpp tombstones.h
	g++ -o foo5.o foo5.cpp
foo6: foo6.cpp tombstones.h
	g++ -o foo6.o foo6.cpp
foo7: foo7.cpp tombstones.h
	g++ -o foo7.o foo7.cpp
foo8: foo8.cpp tombstones.h
	g++ -o foo8.o foo8.cpp

