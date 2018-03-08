#ifndef WORKITEM_H
#define WORKITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>    /* sort(start, end, compare) */

using namespace std;

#define MAX_LINE        100000
#define FILE_TEMP       "temp-file-"

/* Using as compared function in sort() */
bool sortLexicographically(char* a, char* b);

class WorkItem
{
public:
    char*   strLines[MAX_LINE];
    long    numLines = 0;
    int     numTempFiles = 0;

    WorkItem(int nF) : numLines(0), numTempFiles(nF) {};

    string getTempFileName(int num) {
        stringstream ss;
        ss << num;
        return FILE_TEMP + ss.str() + ".txt";
    }

    void writeToTempFile() {
        string file_name = getTempFileName(numTempFiles);

        ofstream fout(file_name);
        if (!fout.is_open())
            perror("error while opening output file");
        else {
            //fout << numLines << "\n";
            for (int i = 0; i < numLines; i++)
                fout << strLines[i] << "\n";
            fout.close();
        }
    }

    void freeStrLines() {
        for (int i = 0; i < numLines; i++)
        if (strLines[i] != nullptr) {
            delete[] strLines[i];
            strLines[i] = nullptr;
        }
    }

    void sortAndSplitLines() {
        // Sorting lines
        sort(strLines, strLines + numLines, sortLexicographically);
        // Writing sorted lines into a temp file
        writeToTempFile();
        // Freeing the memory
        freeStrLines();
    }
};

#endif // WORKITEM_H

