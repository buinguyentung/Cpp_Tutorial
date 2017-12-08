/* Use hashing to support following operations in O(1) time
    add(x): Inserts an item x to the data structure if not already present.
    remove(x): Removes an item x from the data structure if present.
    search(x): Searches an item x in the data structure.
    getRandom(): Returns a random element from current set of elements.

    To implement getRandom(), we can simply pick a random number from 0 to size-1 (size is number of current elements)
    and return the element at that index. The hash map stores array values as keys and array indexes as values.
*/
#include <iostream>
#include <map>
#include <vector>

using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

class my_hash {
private:
    map<int, int> my_map;
    vector<int> my_vector;
public:
    void add(int x) {
        if (my_map.find(x) != my_map.end()) {
            return;
        }
        int index = my_vector.size();
        my_map.insert(std::pair<int, int>(x, index));
        my_vector.push_back(x);
    }

    int search(int x) {
        if (my_map.find(x) == my_map.end()) {
            return -1;
        }
        return my_map.at(x);
    }

    void remove(int x) {
        if (my_map.find(x) == my_map.end()) {
            return;
        }
        int index = my_map.at(x);
        my_map.erase(x);

        int last = my_vector.size() - 1;
        swap(&my_vector[index], &my_vector[last]);
        my_vector.pop_back();
        my_map.at(my_vector[index]) = index;
    }

    void printMap() {
        cout << "map: ";
        for (map<int, int>::iterator it = my_map.begin(); it != my_map.end(); it++) {
            cout << it->first << " " << it->second << endl;
        }
        cout << "vector: ";
        for (int i = 0; i < my_vector.size(); i++) cout << my_vector[i] << " ";
        cout << endl;
        cout << endl;
    }
};

int main()
{
    my_hash mh;
    mh.add(10);
    mh.add(20);
    mh.add(40);
    mh.add(30);
    mh.printMap();

    cout << "search 40: " << mh.search(40) << endl;
    cout << "search 50: " << mh.search(50) << endl;
    mh.remove(20);
    mh.printMap();

    return 0;
}

