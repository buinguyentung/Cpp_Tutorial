/*
    Author: buinguyentung2308@gmail.com
    Problem: Sort lexicographically a large text file
    Solution:
        Step 1: Split the big file into small sorted chunks (using multithreading for sorting)
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
#include <thread>
#include <time.h>
#include <list>
#include <pthread.h>

using namespace std;

/* User-defined variables */
#define MAX_LINE        1000000
#define MAX_TEMP_FILE   2000
#define FILE_INPUT      "unsorted_input4.txt"//"empty_input.txt"
#define FILE_OUTPUT     "sorted_output.txt"
#define FILE_TEMP       "temp-file-"
#define NUM_THREADS     4


int     numTempFiles = 0;   // total number of temp files


string getTempFileName(int num) {
    stringstream ss;
    ss << num;
    return FILE_TEMP + ss.str() + ".txt";
}

/* *********************************************************
 *   Split the big file in small sorted chunks
 *   + Open a stream reader on the big file
 *   + Keep reading until we have enough data
 *   + Sort the data in memory and write it on disk on a temp file
 *   + Repeat this operation until we finish processing the whole input file
 * *********************************************************
 */

bool sortLexicographically(char* a, char* b) {
    return strcmp(a, b) < 0;
}

// ************** Class WorkItem
class WorkItem
{
public:
    char*   strLines[MAX_LINE];
    long    numLines = 0;
    int     numTempFiles = 0;

    WorkItem(int nF) : numLines(0), numTempFiles(nF) {};

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
        sort(strLines, strLines + numLines, sortLexicographically);
        writeToTempFile();
        freeStrLines();
    }
};

// ************** Class wqueue
template <typename T>
class wqueue
{
    list<T> m_queue;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_condv;

    public:
        wqueue() {
            pthread_mutex_init(&m_mutex, NULL);
            pthread_cond_init(&m_condv, NULL);
        }
        virtual ~wqueue() {
            pthread_mutex_destroy(&m_mutex);
            pthread_cond_destroy(&m_condv);
        }

        void add(T item)  {
            pthread_mutex_lock(&m_mutex);
            m_queue.push_back(item);
            pthread_cond_signal(&m_condv);
            pthread_mutex_unlock(&m_mutex);
        }

        T remove() {
            pthread_mutex_lock(&m_mutex);
            while (m_queue.size() == 0) {
                pthread_cond_wait(&m_condv, &m_mutex);
            }
            T item = m_queue.front();
            m_queue.pop_front();
            pthread_mutex_unlock(&m_mutex);

            return item;
        }

        int size() {
            pthread_mutex_lock(&m_mutex);
            int size = m_queue.size();
            pthread_mutex_unlock(&m_mutex);

            return size;
        }
};

// ************** Class wqueue
class Thread
{
    public:
        Thread(): m_tid(0), m_running(0), m_detached(0) {};
        virtual ~Thread();

        int start();
        int join();
        int detach();
        pthread_t self();

        virtual void* run() = 0;

    protected:

    private:
        pthread_t m_tid;        // contains the thread ID
        int m_running;          // flag = 0 when the thread is not running, or 1 when it is running
        int m_detached;         // flag = 0 when the thread is not detached, or 1 when it is detached
};

Thread::~Thread()
{
    if (m_running == 1 && m_detached == 0) {
        pthread_detach(m_tid);
    }
    if (m_running == 1) {
        pthread_cancel(m_tid);
    }
}

static void* runThread(void* arg) {
    return ((Thread*)arg)->run();
}

int Thread::start() {
    int result = pthread_create(&m_tid, NULL, runThread, this);
    if (result == 0) {
        m_running = 1;
    }
    return result;
}

int Thread::join() {
    int result = -1;
    if (m_running == 1) {
        result = pthread_join(m_tid, NULL);
        if (result == 0) {
            m_detached = 1;
        }
    }
    return result;
}

int Thread::detach() {
    int result = -1;
    if (m_running == 1 && m_detached == 0) {
        result = pthread_detach(m_tid);
        if (result == 0) {
            m_detached = 1;
        }
    }
    return result;
}

pthread_t Thread::self() {
    return m_tid;
}

// ************** Class ConsumerThread
class ConsumerThread : public Thread
{
    wqueue<WorkItem*>& m_queue;

    public:
        ConsumerThread(wqueue<WorkItem*>& q) : m_queue(q) { }
        virtual ~ConsumerThread();

        void* run();
};

ConsumerThread::~ConsumerThread()
{
    //cout << "free ComsumerThread\n";
}

void* ConsumerThread::run() {
    for (int i = 0; ;i++) {
        WorkItem* item = (WorkItem*) m_queue.remove();
        if (item->numTempFiles >= 0) {
            item->sortAndSplitLines();
        }
        //cout << "Complete sort " << item->numTempFiles << "\n";
        if (item->numTempFiles < 0) {
            delete item;
            return nullptr;
        }
        delete item;
    }

    return NULL;
}

// ************** Processing large input file
void processInputFile() {
    string single_line;
    wqueue<WorkItem*> wQ;
    list<ConsumerThread*> threadPool;

    ifstream fin(FILE_INPUT);
    if (!fin.is_open())
        perror("error while opening input file");
    else {
        // Create pool of threads
        ConsumerThread* thread;
        for (int i = 0; i < NUM_THREADS; i++) {
            thread = new ConsumerThread(wQ);
            thread->start();
            threadPool.push_back(thread);
        }

        // Create first new WorkItem
        WorkItem* wItem = new WorkItem(numTempFiles);
        numTempFiles++;

        while (getline(fin, single_line)) {
            wItem->strLines[wItem->numLines] = new char[single_line.size() + 1];
            strcpy(wItem->strLines[wItem->numLines], single_line.c_str());
            wItem->numLines++;

            if (wItem->numLines == MAX_LINE) {
                // Complete a WorkItem, add to queue
                wQ.add(wItem);

                // Wait for threads to process items in queue
                //cout << "Just added new item, wQ.size() = " << wQ.size() << "\n";
                while (wQ.size() >= NUM_THREADS);

                wItem = new WorkItem(numTempFiles);
                numTempFiles++;
            }
        }
        if (wItem->numLines > 0) {
            // Complete last WorkItem, add to queue
            wQ.add(wItem);
        }
        // Push [NUM_THREADS] empty items to make sure all data are processed
        for (int i = 0; i < NUM_THREADS; i++) {
            wItem = new WorkItem(-1);
            wQ.add(wItem);
        }
        //cout << "Justtt added new item, wQ.size() = " << wQ.size() << "\n";
        while (wQ.size() > 0);

        if (fin.bad())
            perror("error while reading file");
        fin.close();

        std::list<ConsumerThread*>::iterator it;
        for (it = threadPool.begin(); it != threadPool.end(); ++it) {
            delete *it;
        }
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
                //cout << file_node[num]->strLine << " " << file_node[num]->num << "\n";
                queueLines.push(file_node[num]);
            }
            else {
                available_fin[num] = false;
            }
        }
    }

    /* Merging temp files into an output file */
    //cout << "size: " << queueLines.size() << "\n";
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
        if (remove(file_name[num].c_str()) != 0)
            perror("error while deleting temp file");
    }
}

int main(int argc, char* argv[]) {

    clock_t t1, t2;
    t1 = clock();

    processInputFile();

    t2 = clock();
    float diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
    cout << "Processing input in: " << diff << "\n";

    processOutputFile();

    t2 = clock();
    diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
    cout << "Total running time: " << diff << "\n";

    //sort(strLines, strLines + numLines, sortLexicographically);
    //qsort(strLines, numLines, sizeof(char*), compareStr);

    return 0;
}
