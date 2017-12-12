/* Given an array with n distinct elements, convert the given array to a reduced form where all elements are in range from 0 to n-1.
    Input:
        2
        3
        10 40 20
        5
        5 10 40 30 20
    Output:
        0 2 1
        0 1 4 3 2
    Method:
        1. Copy data to new tempArr[], then sort tempArr[] in ascendant order
        2. Push all elements of tempArr[] to a map with value is index increasing by 1
        3. Simply return index of map[A[i]]
*/
#include <iostream>
#include <map>
using namespace std;

#define MAX_N 201

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitioning(int A[], int left, int right) {
    int mid = left + (right - left) / 2;
    int pivot = A[mid];

    swap(&A[mid], &A[left]);
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while (i <= j && A[i] <= pivot) {
            i++;
        }
        while (i <= j && A[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(&A[i], &A[j]);
        }
    }

    swap(&A[i - 1], &A[left]);
    return i - 1;
}

void quicksort(int A[], int left, int right) {
    if (left < right) {
        int part = partitioning(A, left, right);
        quicksort(A, left, part - 1);
        quicksort(A, part + 1, right);
    }
}

void convertArr(int A[], int N) {
    int tempArr[MAX_N];

    for (int i = 0; i < N; i++)
        tempArr[i] = A[i];
    quicksort(tempArr, 0, N - 1);

    int val = 0;
    map<int, int> my_map;
    for (int i = 0; i < N; i++) {
        my_map.insert(pair<int, int>(tempArr[i], val));
        val++;
    }

    for (int i = 0; i < N; i++)
        cout << my_map[A[i]] << " ";
    cout << endl;
}

int main() {
	int tc, N, A[MAX_N];

	cin >> tc;
	while (tc > 0) {
	    cin >> N;
	    for (int i = 0; i < N; i++)
	        cin >> A[i];
	    convertArr(A, N);
	    tc--;
	}

	return 0;
}
