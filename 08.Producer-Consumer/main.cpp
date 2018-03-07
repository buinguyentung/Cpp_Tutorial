#include <iostream>
#include <stdio.h>
#include "WorkItem.h"
#include "wqueue.h"
#include "MyThread.h"
#include "ConsumerThread.h"

using namespace std;

int main()
{
    WorkItem *workItem = new WorkItem("wqueue_example", 23);
    string strx = workItem->getMessage();
    cout << strx << endl;
/*
    MyThread* thread1 = new MyThread();
    MyThread* thread2 = new MyThread();
    thread1->start();
    thread2->start();
    thread1->join();
    thread2->join();
    printf("main done\n");
*/
    wqueue<WorkItem*> queue;
    ConsumerThread* thread1 = new ConsumerThread(queue);
    ConsumerThread* thread2 = new ConsumerThread(queue);
    thread1->start();
    thread2->start();

    WorkItem* item;
    for (int i = 0; i < 3; i++) {
        item = new WorkItem("abc", 123);
        queue.add(item);
        item = new WorkItem("def", 456);
        queue.add(item);
        item = new WorkItem("ghi", 789);
        queue.add(item);
    }

    while (queue.size() > 0);
    printf("done\n");
    return 0;
}
