// CodeProject: A Beginner's Guide to Pointers
// Ref: https://www.codeproject.com/Articles/627/A-Beginner-s-Guide-to-Pointers
//

#include <iostream>

using namespace std;

void add23(int nNumber) {
	nNumber = nNumber + 23;
}

void add23_p(int* pNumber) {
	*pNumber += 23;
}

int main() {

	// Passing Pointers to Functions
	{
		int nNumber = 8;
		add23(nNumber);		//a copy of the variable nNumber passed to the function
		cout << "add23(nNumber) = " << nNumber << endl;

		add23_p(&nNumber);	// passing a memory address
		cout << "add23_p(&nNumber) = " << nNumber << endl;

		int* pNumber = &nNumber;
		add23_p(pNumber);	// passing a memory address
		cout << "add23_p(pNumber) = " << nNumber << endl;
	}

	//Reference: 
	// (&) is read as "the address of", or
	//  "a reference to."
	// Unlike pointer, you cannot "reseat" a reference
	int myFirstNumber = 23;
	int mySecondNumber = 8;
	int& myReference = myFirstNumber;

	myReference = mySecondNumber;

	printf("%d", myFirstNumber);


	return 0;
}
