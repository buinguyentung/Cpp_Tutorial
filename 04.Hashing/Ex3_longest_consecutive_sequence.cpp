/* Longest consecutive subsequence
    Input:
        2
        7
        2 6 1 9 4 5 3
        7
        1 9 3 10 4 20 2
    Output:
        6
        4
    Method:
        Hash using map. Store in ascending order then traverse from left to right.
*/
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

#define MAX_N 101

int N, A[MAX_N];

int getLongestConsecutiveSubsequence() {
    int ret = 1;
    std::map<int, int> my_map;

    for (int i = 0; i < N; i++)
    if (my_map.find(A[i]) == my_map.end()) {
        my_map.insert(std::pair<int, int>(A[i], 1));
    }
    /*cout << my_map.size() << " : ";
    for (std::map<int, int>::iterator it = my_map.begin(); it != my_map.end(); it++) {
        cout << it->first << " ";
    }
    cout << endl;*/

    int count = 0;
    int last_value = my_map.begin()->first;
    for (std::map<int, int>::iterator it = my_map.begin(); it != my_map.end(); it++) {
        if (last_value != it->first - 1) {
            count = 1;
        }
        else {
            count++;
        }
        if (ret < count)
            ret = count;
        last_value = it->first;
        //cout << last_value << " " << count << endl;
    }

    return ret;
}

int main()
{
    int tc;
    freopen("input.txt", "r", stdin);
    cin >> tc;
    while (tc > 0) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> A[i];
        cout << getLongestConsecutiveSubsequence() << endl;
        tc--;
    }

    fclose(stdin);
    return 0;
}

