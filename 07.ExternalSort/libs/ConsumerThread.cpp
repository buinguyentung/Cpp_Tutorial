#include "ConsumerThread.h"

//ConsumerThread::ConsumerThread() {}

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

