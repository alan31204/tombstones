/////////////////////////////////////////////////////////////////////////////
// Tombstones.h, expected interface for CS254 assignment 5
// A5 Tombstones
// Po-Chun Chiu & Yujie Liu
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__


using namespace std;

void DRerror(){
	cout<<"Dangling Reference Exception!"<<endl;
	exit(1);
}

void MLerror(){
	cout<<"Memory Leak Exception!"<<endl;
	exit(1);
}

template <class T> class Pointer;
template <class T> class Tombstone;
//template <class T> void free(Pointer<T>& t); 

template <class T> 
class Tombstone {
public:
	int referenceCounting;	// reference counting for the Tombstone
	T* value;				// pointer of value to the actual address
	bool rip;				// boolean to check whether the tombstone is still inused or not
	Tombstone<T>(){			// constructor to initialize tombstone
        referenceCounting = 0;
        value = NULL;
        rip = false;
    }
};

template <class T>
class Pointer {	
public:
    Tombstone <T> *ptr;	//initialized a pointer to the tombstone
    Pointer<T>(){
		// default constructor
		ptr = new Tombstone<T>();
        ptr->rip = true;// not inused when inistialized
	}                            
    Pointer<T>(Pointer<T>& y){
		// copy constructor
		// y is a reference of Pointer<T>
		if(y.ptr->rip) {
			DRerror();//if tombstone of y is not in used, that means we are accessing a dangling reference
		}
		ptr = y.ptr;
		if(ptr->referenceCounting != 0) ptr->referenceCounting++; 
	}
    Pointer<T>(T* x){
		// bootstrapping constructor
        ptr = new Tombstone<T>();
		ptr->value = x;
        ptr->rip = false;
		if(x != NULL){
			ptr->referenceCounting = 1; 
		}
		else{
			ptr->referenceCounting = 0;
		}
	}
	
        // argument should always be a call to new
    ~Pointer<T>(){
		// destructor
		ptr->referenceCounting--; // only delete one pointer
		if(ptr->referenceCounting == 0 && !ptr->rip){
            MLerror();	// if the reference counting is 0 and rip is false, that means we have a memory leak exception
        }
        ptr = NULL;
	}

    T& operator*() const{
        //cout << "*: " << (ptr->referenceCounting) << endl;
		// dereferencing
		if(ptr->referenceCounting==0){
            MLerror();// usually when reference counting reaches to 0, we are going to run into memory leak excetion
		}
		else if(ptr->rip == true){
			DRerror();	// if rip is true, then it's a dangling reference exception
		}else{
            return *(ptr->value); //otherwise return the actual value
        }

	}
    T* operator->() const{
        //cout << "->: " << (ptr->referenceCounting) << endl;
		// field dereferencing
		if(ptr->referenceCounting==0){
            MLerror();// usually when reference counting reaches to 0, we are going to run into memory leak excetion
		}
		else if(ptr->rip == true){
			DRerror();	// if rip is true, then it's a dangling reference exception
		}else{
            return ptr->value; //otherwise return the the pointer to the object
        }

	}
    Pointer<T>& operator=(const Pointer<T>& t){ 	// assignment
        //cout << "pointer =: " << (ptr->referenceCounting) << endl;
        ptr->referenceCounting--;
        if(ptr->referenceCounting == 0){
            MLerror();// usually when reference counting reaches to 0, we are going to run into memory leak excetion
		}
		ptr = t.ptr;
		ptr->referenceCounting++; // increment the reference counting
		if(ptr->rip){
			DRerror();	// if rip is true, then it's a dangling reference exception
        }
		return *this; 
	}  
	
    friend void free(Pointer<T>& t){
		// delete pointed-at object
        //cout<<"Free: "<<t.ptr->referenceCounting<<endl;
        if(t.ptr->rip){
			DRerror();	// if rip is true, then it's a dangling reference exception
        }else{
            delete t.ptr->value; //delete the pointer to the object
			t.ptr->rip = true; // set this tombstone to rip
        }
    }
 
		// 
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.

    // equality comparisons:
    bool operator==(const Pointer<T>& t) const{
		//cout << "pointer ==: " << (ptr->referenceCounting) << endl;
		if(ptr->rip|| (t.ptr->rip)){
			DRerror();// if any of them is rip, it's dangling reference
		}
		else{
			return ptr->value == (t.ptr->value);		
		}

	}
    bool operator!=(const Pointer<T>& t) const{
        //cout << "pointer !=: " << (ptr->referenceCounting) << endl;
		if(ptr->rip|| (t.ptr->rip)){
			DRerror(); // if any of them is rip, it's dangling reference
		}
		else{
			return ptr->value != (t.ptr->value);	
		}
	}

    bool operator==(const int n) const{
        //cout << "==: " << (ptr->referenceCounting) << endl;
		return ptr->value == NULL && n == 0;
	}
        // true iff Pointer is null and int is zero
    bool operator!=(const int n) const{
        //cout << "!=: " << (ptr->referenceCounting) << endl;		
        return !(ptr->value == NULL && n == 0);		
	}
        // false iff Pointer is null and int is zero
	
};


template <class T>
bool operator==(const int n, const Pointer<T>& t) { 
	return t == n;
}
template <class T>
bool operator!=(const int n, const Pointer<T>& t) { 
	return t != n; 
}


#endif // __TOMBSTONES_H__
