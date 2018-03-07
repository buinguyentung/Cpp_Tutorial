/* Sort lexicographically a large text file
    Step 1: Split the big file in small sorted chunks
    Step 2: Merge all chunks into a sorted output file
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>         /* qsort(base, num, sizeof(string), compare) */
#include <bits/stdc++.h>    /* sort(start, end, compare) */
#include <queue>

using namespace std;

#define MAX_LINE        10
#define MAX_TEMP_FILE   1000
#define FILE_INPUT      "unsorted_input.txt" //"english.txt"
#define FILE_OUTPUT     "sorted_output1.txt"
#define FILE_TEMP       "temp-file-"

char*   strLines[MAX_LINE];
long    numLines = 0;
int     numTempFiles = 0;


/* *********************************************************
 *   Split the big file in small sorted chunks
 *   + Open a stream reader on the big file
 *   + Keep reading until we have enough data
 *   + Sort the data in memory and write it on disk on a temp file
 *   + Repeat this operation until we finish processing the whole input file
 * *********************************************************
 */

/* UNUSED: compared function in qsort() */
/*int compareStr(const void* a, const void* b) {
    const char* aa = *(const char**) a;
    const char* bb = *(const char**) b;
    return strcmp(aa, bb);
}*/

/* Using as compared function in sort() */
bool sortLexicographically(char* a, char* b) {
    return strcmp(a, b) < 0;
}

void freeStrLines() {
    for (int i = 0; i < numLines; i++)
    if (strLines[i] != nullptr) {
        delete[] strLines[i];
        strLines[i] = nullptr;
    }
}

string getTempFileName(int num) {
    stringstream ss;
    ss << num;
    return FILE_TEMP + ss.str() + ".txt";
}

void writeToTempFile() {
    // std::to_string doesn't work on Code::Blocks
    //string file_name = FILE_TEMP + std::to_string(numTempFiles) + ".txt";
    string file_name = getTempFileName(numTempFiles);

    ofstream fout(file_name);
    if (!fout.is_open())
        perror("error while opening output file");
    else {
        //fout << numLines << endl;
        for (int i = 0; i < numLines; i++)
            fout << strLines[i] << endl;
        fout.close();
    }
    numTempFiles++;
}

void sortAndSplitLines() {
    // Sorting lines
    sort(strLines, strLines + numLines, sortLexicographically);
    // Writing sorted lines into a temp file
    writeToTempFile();
    // Freeing the memory
    freeStrLines();
    numLines = 0;
}

void processInputFile() {
    string single_line;

    ifstream fin(FILE_INPUT);
    if (!fin.is_open())
        perror("error while opening input file");
    else {
        while (getline(fin, single_line)) {
            strLines[numLines] = new char[single_line.size() + 1];
            strcpy(strLines[numLines], single_line.c_str());
            numLines++;

            if (numLines == MAX_LINE) {
                sortAndSplitLines();
            }
        }
        if (numLines > 0) {
            sortAndSplitLines();
        }
        if (fin.bad())
            perror("error while reading file");
        fin.close();
    }
}


/* *********************************************************
 *  K-way merge
 *  + Open K file stream
 *  + Read one line per file and take the smallest line each time
 *  + Repeat this operation until we finish reading all the file
 *  Keep the current line values in an ordered structure: priority queue
 * *********************************************************
 */

class Node {
public:
    char* strLine = nullptr;
    int num;

    Node() { }

    Node(string s, int n) : num(n) {
        strLine = new char[s.size() + 1];
        strcpy(strLine, s.c_str());
    }

    ~Node() {
        if (strLine != nullptr) {
            delete[] strLine;
            strLine = nullptr;
        }
    }

    void setStrLine(string s) {
        if (strLine != nullptr) {
            delete[] strLine;
            strLine = nullptr;
        }
        strLine = new char[s.size() + 1];
        strcpy(strLine, s.c_str());
    }

    void setNum(int n) {
        num = n;
    }
};

struct CompareNodePtrs {
    bool operator() (const Node* a, const Node* b) const {
        return strcmp(a->strLine, b->strLine) > 0;
    }
};

void processOutputFile() {
    string file_name[numTempFiles + 1];
    ifstream temp_fin[numTempFiles + 1];
    bool available_fin[numTempFiles + 1];  // Used to mark not opening or reaching eof files
    string single_line;
    Node* file_node[numTempFiles + 1];
    priority_queue<Node*, vector<Node*>, CompareNodePtrs> queueLines;

    /* Opening sorted output file */
    ofstream fout(FILE_OUTPUT);
    if (!fout.is_open())
        perror("error while opening output file");

    /* Opening all temp files */
    for (int num = 0; num < numTempFiles; num++) {
        available_fin[num] = true;
        file_name[num] = getTempFileName(num);
        temp_fin[num].open(file_name[num]);

        if (!temp_fin[num].is_open()) {
            perror("error while opening temporary input file");
            available_fin[num] = false;
        } else {
            /* Pushing the first line of each temp file into queue */
            if (getline(temp_fin[num], single_line)) {
                file_node[num] = new Node(single_line, num);
                //cout << file_node[num]->strLine << " " << file_node[num]->num << endl;
                queueLines.push(file_node[num]);
            }
            else {
                available_fin[num] = false;
            }
        }
    }

    /* Merging temp files into an output file */
    //cout << "size: " << queueLines.size() << endl;
    Node* temp;
    while (!queueLines.empty()) {
        temp = queueLines.top();
        queueLines.pop();
        //cout << "result: " << temp->strLine << "\n";
        fout << temp->strLine << "\n";

        // Getting the next line from chosen file if any and push into queue
        if (available_fin[temp->num]) {
            if (getline(temp_fin[temp->num], single_line)) {
                file_node[temp->num]->setStrLine(single_line);
                queueLines.push(file_node[temp->num]);
            } else {
                available_fin[temp->num] = false;
            }
        }
    }

    fout.close();
    /* Removing all temp files */
    for (int num = 0; num < numTempFiles; num++)
    if (temp_fin[num].is_open()) {
        temp_fin[num].close();
        //if (remove(file_name[num].c_str()) != 0)
            //perror("error while deleting temp file");
    }
}

int main(int argc, char* argv[]) {

    processInputFile();

    //processOutputFile();

    //cout << "End of End\n";
    //sort(strLines, strLines + numLines, sortLexicographically);
    //qsort(strLines, numLines, sizeof(char*), compareStr);

    return 0;
}
