#include "monitor.h"

Monitor::Monitor()
{
    printf( RED "Blad podczas tworzenia monitora -> nie podano klucza semafora lub nazwy monitora\n" RED );
    exit(1);
}

Monitor::Monitor(int semKey, string name)
{
    s = new Semaphore(semKey);  // initiate semaphores
    mName = name;
}

Monitor::~Monitor()
{
    delete s;
}
void Monitor::enterToGetElem()
{
    // semaphore operations
    s->P(IN_QUEUE);
    s->P(MUTEX);
    s->V(FREE_SPACE);
}

void Monitor::enterToInsertElem()
{
    // semaphore operations
    s->P(FREE_SPACE);
    s->P(MUTEX);
    s->V(IN_QUEUE);
}

void Monitor::leave()
{
    s->V(MUTEX);
}

int Monitor::tryGetElem()
{
    int elem;

    enterToGetElem();

    elem = myqueue.getElem();

    leave();

    return elem;
}

int Monitor::tryInsertElem(int prior)
{
    int elemIndex;

    enterToInsertElem();

    elemIndex = myqueue.insertElem(prior);

    leave();

    return elemIndex;
}

void Monitor::getMonitorStatus()
{
    cout << mName << "-> ";
    myqueue.getQueueStatus();
}

void Monitor::getEverLeft()
{
    myqueue.getQueueHistory();
}

Monitor::MyQueue::MyQueue()
{
    for(int i = 0; i <= MAX_QUEUE; ++i)
    {
        buffer[i] = 0;
    }

    inBuffer = 0;
    normalInBuffer = 0;
    lowPriorInBuffer = 0;
    highPriorInBuffer = 0;
    historyNormal = 0;
    historyLowPrior = 0;
    historyHighPrior = 0;
}

int Monitor::MyQueue::insertNormalElem()
{
    int i;

    // find free place
    for(i = 0; buffer[i] != 0; ++i);

    // put value to storage
    buffer[i] = 1;

    // increase number of products in storage
    ++inBuffer;
    ++normalInBuffer;

    return i;   // return index where inserted
}

int Monitor::MyQueue::insertElem(int prior)
{
    int i = 0;
    int firstNotPrior;

    if (prior > 3 || prior < 1)
    {
        printf( RED "Blad podczas kolejkowania elementu -> bledny priorytet\n" RED );
        exit(1);
    }

    if (prior == 1)
    {
        return insertNormalElem();
    }

    /// priority element

    if(buffer[0] == 0)
    {
        buffer[0] = prior;

        ++inBuffer;
        if(prior == 2) ++lowPriorInBuffer;
        if(prior == 3) ++highPriorInBuffer;

        return 0;
    }

    // leave prior products as they lay (FIFO for prior)
    for(firstNotPrior = 0; buffer[firstNotPrior] >= prior; ++firstNotPrior);

    // go to the first place after last product in queue
    for(i=0 ; (buffer[i] != 0) && (i < MAX_QUEUE); ++i);

    // change placement of products
    for( ; i > firstNotPrior; --i)
    {
        buffer[i] = buffer[i-1];
    }

    // insert prior
    buffer[firstNotPrior] = prior;

    // increase number of products in storage
    ++inBuffer;
    if(prior == 2) ++lowPriorInBuffer;
    if(prior == 3) ++highPriorInBuffer;

    return firstNotPrior;   // return index where inserted
}

int Monitor::MyQueue::getElem()
{
    int i, elem = 0;

    elem = buffer[0];

    for(i = 0; (buffer[i+1] != 0) && (i < (MAX_QUEUE - 1)); ++i)
    {
        buffer[i] = buffer[i+1];
    }

    if(i < MAX_QUEUE) buffer[i] = 0;

    // decrease number of products in storage
    --inBuffer;
    if(elem == 1)
    {
        --normalInBuffer;
        ++historyNormal;
    }

    if(elem == 2)
    {
        --lowPriorInBuffer;
        ++historyLowPrior;
    }

    if(elem == 3)
    {
        --highPriorInBuffer;
        ++historyHighPrior;
    }

    return elem;
}

void Monitor::MyQueue::getQueueStatus()
{
    cout << "[" << inBuffer << "] ";
    cout << normalInBuffer << " " << lowPriorInBuffer;
    cout << " " << highPriorInBuffer << "\t\t";
}

void Monitor::MyQueue::getQueueHistory()
{
    cout << "< " << historyNormal << " > < " << historyLowPrior;
    cout << " > < " << historyHighPrior << " >" << endl;
}
