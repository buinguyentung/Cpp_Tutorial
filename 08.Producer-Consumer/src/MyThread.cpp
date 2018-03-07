#include "MyThread.h"

MyThread::MyThread()
{
    //ctor
}

MyThread::~MyThread()
{
    //dtor
}

void* MyThread::run() {
    for (int i = 0; i < 5; i++) {
        printf("thread %lu running - %d\n", (long unsigned int) self(), i + 1);
        Sleep(2);
    }
    printf("thread done %lu\n", (long unsigned int) self());
    return NULL;
}
