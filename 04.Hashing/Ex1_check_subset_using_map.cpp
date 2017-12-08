/* Find whether an array is subset of another array
    Input: 1 -> # test case
        6 4
        11 1 13 21 3 7
        11 3 7 1
    Output: Yes
    It may be assumed that elements in both array are distinct.

    Method:
    1) Hashing using map<int, int>
    2) It still is true if the elements are not distinct
*/
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

#define MAX_N 100001

int N, M, A1[MAX_N], A2[MAX_N];

void printArr(int A[], int N) {
    for (int i = 0; i < N; i++)
        cout << A[i] << " ";
    cout << endl;
}

bool isSubsetArr() {
    std::map<int, int> my_map;

    for (int i = 0; i < N; i++)
        my_map[A1[i]]++;
    //cout << my_map.size() << endl;

    for (int i = 0; i < M; i++) {
        std::map<int, int>::iterator it = my_map.find(A2[i]);
        if (it == my_map.end())
            return false;
        my_map[A2[i]]--;
        if (my_map[A2[i]] == 0) {
            my_map.erase(it);
        }
    }
    //cout << my_map.size() << endl;

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
