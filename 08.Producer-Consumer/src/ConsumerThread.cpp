#include "ConsumerThread.h"

//ConsumerThread::ConsumerThread() {}

ConsumerThread::~ConsumerThread()
{
    //pthread_mutex_destroy(&m_mutex);
}

void* ConsumerThread::run() {
    for (int i = 0; ;i++) {
        //pthread_mutex_lock(&m_mutex);
        printf("thread %lu, loop %d - waiting for item..\n", (long unsigned int) self(), i);
        //pthread_mutex_unlock(&m_mutex);
        WorkItem* item = (WorkItem*) m_queue.remove();
        printf("thread %lu, loop %d - got one item\n", (long unsigned int) self(), i);
        printf("thread %lu, loop %d - message=%s , number=%d\n", (long unsigned int) self(), i, item->getMessage(), item->getNumber());
        delete item;
    }

    return NULL;
}
