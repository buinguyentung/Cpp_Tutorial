// Pointer to Class, Class Array
// Ref: https://simplesnippets.tech/pointer-to-class-in-cpp/
//
//===========================================================
//
// (1) Pointer to Class
// A class pointer is a pointer variable that stores address of an object of a class.
// Ex.	Rectangle obj1(10, 20);
//		Rectangle* ptr = &obj1;
//
// (2) Pointer to Class array
// Ex.	Rectangle arr1[2];
//		Rectangle* ptr = arr;
//		std::cout << (ptr + i)->getArea() << std::endl;
//
// Note:
//	+ If we initialize a class pointer using new, we must delete it later.
// Question:
//	+ Why we usually use class pointer instead of normal object? heap memory, polymorphysim.
//

#include <iostream>

using namespace std;

class Foo {
public:
	Foo() : myVar(0) {
		cout << "Create Foo class" << endl;
	}

	~Foo() {
		cout << "Destroy Foo class" << endl;
	}

	virtual void Print() {
		cout << "---Foo called myVar= " << myVar << endl;
	}

	void setMyVar(unsigned v) {
		myVar = v;
	}

private:
	unsigned myVar;
};

class Foo2 : public Foo {
public:
	Foo2() {
		cout << "Create Foo222 class" << endl;
	}

	~Foo2() {
		cout << "Destroy Foo222 class" << endl;
	}

	void Print() {
		cout << "---Foo222 called" << endl;
	}
};

int main() {

	{
		Foo bar;	// auto call default constructor
		bar.Print();
	}

	{
		Foo2 *bar2 = new Foo2();	// cout: Create Foo class (parent contructor) 
									// => Create Foo222 class (child contructor)
		bar2->Print();		// cout: --- Foo222 called
		delete bar2;		// cout: Destroy Foo222 class (child contructor) 
							// => Destroy Foo class (parent constructor)
	}

	// Pointer to Class
	{
		Foo obj1;
		obj1.setMyVar(23);
		Foo* ptr1 = &obj1;
		std::cout << &obj1 << " " << ptr1 << " " << &ptr1 << std::endl;
		ptr1->Print();
	}

	// Pointer to Class Array
	Foo arr1[3];
	arr1[0].setMyVar(1);
	arr1[1].setMyVar(2);
	arr1[2].setMyVar(3);
	
	Foo *ptr = arr1;
	
	for (int i = 0; i < 3; i++) {
		(ptr + i)->Print();
	}

	return 0;
}
