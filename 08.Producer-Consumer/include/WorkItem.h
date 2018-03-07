#ifndef WORKITEM_H
#define WORKITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
//#include "wqueue.h"

using namespace std;


class WorkItem
{
    string m_message;
    int m_number;

    public:
        WorkItem(const char* message, int number);
        virtual ~WorkItem();
        const char* getMessage();
        int getNumber();

    protected:

    private:
};

#endif // WORKITEM_H
