#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>

class Thread
{
    public:
        Thread();
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

#endif // THREAD_H

