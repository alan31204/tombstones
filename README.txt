CSC 254 Assignment 5 README
  Tombstones Assignment
  Po-Chun Chiu(pchiu4) & Yujie Liu(yliu134)
	Student ID: 29433254 & 29421244
	Email: pchiu4@u.rochester.edu, yliu134@u.rochester.edu

Assignment Directory: A5
	Everything is in the A5 directories including foo1.cpp to foo8.cpp, with modified tombstones.h, Makefile, README.txt
	Tested in the school CSUG cycle machines. 


Compile steps and sample outputs:
make
./foo1.o->foo1: OK
./foo2.o->Dangling Reference Exception!
./foo3.o->foo3: OK
./foo4.o->Dangling Reference Exception!
./foo5.o->Memory Leak Exception!
./foo6.o->Memory Leak Exception!
./foo7.o->Dangling Reference Exception!
./foo8.o->Dangling Reference Exception!


tombstones.h
1. We modified the code in the tombstones.h. We build every function on top of that. We had two error functions, one for memory leak and the other for dangling reference. The code will terminate if run into either situations.
2. We build a class of tombstone, and set three values. referenceCounting as int, rip as boolean and a pointer T* to the value, and write a default constuctor for tombstone. 
3. In the default constructor for our designed Pointer, set the rip to true because it's not inused. The copy constructor will take a normal pointer and change it to the our Pointer type. Remember to set the referenceCounting to 0 or increment it in different conditions. 
4. The destructor will set the ptr to NULL(the pointer to object) and decrement reference counting. If the reference counting is zero, it's going to be a memory leak situation.
5. For the operator* and operator-> functions, return the pointer or the actual value if not dangling reference or memory leak.
6. For assignment, we will first decrease the original reference counting since it's linked to another tombstone. Check for memory leak, and assign it to the other passed in tombstone. Return *this. 
7. For free function, we check first to see if the tombstone is in used. If not, delete the pointer to the object and set the tombstone to be RIP.
8. The rest functions are the equality comparisons and inequality comparisons with different types of parameters. 
9. Add two comparion functions outside the class of pointer to support number to pointer comparisons.
