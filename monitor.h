#ifndef MONITOR_H
#define MONITOR_H

#include "include.h"
#include "semaphore.h"

using namespace std;

class Monitor
{
private:
    class MyQueue   // inner class, up to 3 priorities buffer
    {               // 1 - normal, 2 - low prior, 3 - high prior
    private:
        int buffer[MAX_QUEUE];

        // number of elements in queue
        int inBuffer;
        int normalInBuffer;
        int lowPriorInBuffer;
        int highPriorInBuffer;

        // number of elem that ever left queue
        int historyNormal;
        int historyLowPrior;
        int historyHighPrior;

        int insertNormalElem();

    public:
        MyQueue();
        ~MyQueue() {}

        int insertElem(int prior);
        int getElem();

        void getQueueStatus();
        void getQueueHistory();
    };

    MyQueue myqueue;
    Semaphore *s;

    string mName;

public:
    Monitor();
    Monitor(int semKey, string name);
    ~Monitor();

    // shared space protection
    void enterToGetElem();
    void enterToInsertElem();
    void leave();

    int tryGetElem();   // returns element
    int tryInsertElem(int prior);   // returns index where elem inserted

    void getMonitorStatus();
    void getEverLeft();
};

#endif // MONITOR_H
