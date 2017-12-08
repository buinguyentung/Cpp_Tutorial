/* Return maximum occurring character in an input string
    Input:
        2 -> # test case
        test sample
        cbbbbccc
    Output:
        t
        c
    There are three characters with same and maximum count two i.e. “t”, “e” and “s” but our program will result “t” because “t” comes first in input string.

    Method:
    In this, when we traverse through the string, we would hash each character into an array of ASCII characters.
    Typically, ASCII characters are 256, so we use our Hash array size as 256.
*/
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

#define MAX_N 256

char str[MAX_N];

char getMaxChar(char* str) {
    int count[MAX_N] = {0};
    int len = strlen(str);

    cout << str << endl;
    for (int i = 0; i < len; i++)
        count[str[i]]++;

    int max = -1;
    char ret;
    for (int i = 0; i < len; i++)
    if (count[str[i]] > max) {
        max = count[str[i]];
        ret = str[i];
    }

    return ret;
}

int main()
{
    int tc;
    freopen("input.txt", "r", stdin);
    cin >> tc;
    while (tc > 0) {
        cin >> str;
        cout << getMaxChar(str) << endl;
        tc--;
    }

    fclose(stdin);
    return 0;
}

