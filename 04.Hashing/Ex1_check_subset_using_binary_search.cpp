/* Find whether an array is subset of another array
    Input: 1 -> # test case
        6 4
        11 1 13 21 3 7
        11 3 7 1
    Output: Yes
    It may be assumed that elements in both array are distinct.

    Method:
    1) Sort arr1[] O(NlogN)
    2) For each element of arr2[], do binary search for it in sorted arr1[]
    3) If all elements are present then return 1, otherwise return 0
*/
#include <iostream>
#include <fstream>

using namespace std;

#define MAX_N 100001

int N, M, A1[MAX_N], A2[MAX_N];

void printArr(int A[], int N) {
    for (int i = 0; i < N; i++)
        cout << A[i] << " ";
    cout << endl;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitioning(int A[], int left, int right) {
    int mid = left + (right - left) / 2;
    int pivot = A[mid];

    int i = left + 1;
    int j = right;
    swap(&A[left], &A[mid]);
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
    swap(&A[left], &A[i - 1]);

    return i - 1;
}

void quicksort(int A[], int left, int right) {
    if (left < right) {
        int part = partitioning(A, left, right);
        quicksort(A, left, part - 1);
        quicksort(A, part + 1, right);
    }
}

bool binarySearch(int key, int A[], int N) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (A[mid] == key)
            return true;
        if (A[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return false;
}

bool isSubsetArr() {
    /* sorting 2 arrays in ascending order */
    quicksort(A1, 0, N - 1);
    //printArr(A1, N);

    //quicksort(A2, 0, M - 1);
    //printArr(A2, M);

    /* searching each element of arr2 into arr1 by binary search */
    for (int i = 0; i < M; i++) {
        if (!binarySearch(A2[i], A1, N))
            return false;
    }

    return true;
}

int main()
{
    int tc;
    freopen("input.txt", "r", stdin);
    cin >> tc;
    while (tc > 0) {
        cin >> N >> M;
        for (int i = 0; i < N; i++) cin >> A1[i];
        for (int i = 0; i < M; i++) cin >> A2[i];

        //cout << N << " " << M << endl;
        if (isSubsetArr()) cout << "Yes\n";
        else
            cout << "No\n";
        tc--;
    }

    fclose(stdin);
    return 0;
}

