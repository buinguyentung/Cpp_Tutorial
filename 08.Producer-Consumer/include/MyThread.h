#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <stdio.h>
#include <windows.h>
#include <thread>
#include "Thread.h"


class MyThread : public Thread
{
    public:
        MyThread();
        virtual ~MyThread();

        virtual void* run();

    protected:

    private:
};

#endif // MYTHREAD_H
