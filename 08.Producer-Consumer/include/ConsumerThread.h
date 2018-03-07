#ifndef CONSUMERTHREAD_H
#define CONSUMERTHREAD_H
#include <string>
#include <thread>
#include <pthread.h>
#include "Thread.h"
#include "wqueue.h"
#include "WorkItem.h"


class ConsumerThread : public Thread
{
    wqueue<WorkItem*>& m_queue;

    public:
        ConsumerThread(wqueue<WorkItem*>& q) : m_queue(q) {
            //pthread_mutex_init(&m_mutex, NULL);
        }
        virtual ~ConsumerThread();

        void* run();

    protected:

    private:
};

#endif // CONSUMERTHREAD_H
