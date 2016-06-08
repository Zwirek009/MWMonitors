#include "include.h"
#include "monitor.h"

using namespace std;

void producer(Monitor *m, int prior, int microSecPeriod)
{
    while (1)
    {
        // production time
        // suspend executing thread for requested number of microseconds
        if(microSecPeriod != 0 && prior == 1)
        {
            usleep(microSecPeriod);
        }

        // approx production time
        if(microSecPeriod != 0 && prior >= 2)
        {
            usleep(rand()%(microSecPeriod*2));
        }

        /// insert to buffer
        m->tryInsertElem(prior);

        if(microSecPeriod == 0)
        {
            return;
        }
    }
}

void producerOnDemand(Monitor *m, int prior, int microSecPeriod)
{
    while (1)
    {
        // wait for user request for prior product, x and enter - exit prior
        if((microSecPeriod != 0) && (getchar() == 'x')) return;

        // suspend executing thread for approx requested number of microseconds
        if(microSecPeriod != 0)
        {
            usleep(rand()%(microSecPeriod*2));
        }

        /// insert to buffer
        m->tryInsertElem(prior);

        if(microSecPeriod == 0)
        {
            return;
        }
    }
}

int consumer(Monitor *m, int microSecPeriod)
{
    int prior = 0;

    while (1)
    {
        /// remove from buffer
        prior = m->tryGetElem();

        // processing time
        // suspend executing thread for requested number of microseconds
        if(microSecPeriod != 0)
        {
            usleep(microSecPeriod);
        }
        else break;
    }

    return prior;
}

void prodCons(Monitor *mFarsz, Monitor *mCiasto, Monitor *mPierogi, int microSecPeriod)
{
    int prior;

    while (1)
    {
        /// get farsz and ciasto
        prior = consumer(mFarsz, 0);
        consumer(mCiasto, 0);

        /// production time
        usleep(microSecPeriod);

        /// insert pieroga
        producer(mPierogi, prior, 0);
    }
}

void visualization(Monitor *farsz, Monitor *ciasto, Monitor *pierogi)
{
    while(1)
    {
        ciasto->getMonitorStatus();
        farsz->getMonitorStatus();
        pierogi->getMonitorStatus();

        pierogi->getEverLeft();

        usleep(100000);
    }
}

int main()
{
    Monitor *mFarsz = new Monitor(1000, "Farsz");
    Monitor *mCiasto = new Monitor(1001, "Ciasto");
    Monitor *mPierogi = new Monitor(1002, "Pierogi");

    srand(time(NULL));

    // wait for user to start
    getchar();

    // stard all threads
    thread fMiesny (producer,mFarsz,1,200000);
    thread fSerowy (producer,mFarsz,2,1500000);
    thread fGrzybowy (producerOnDemand,mFarsz,3,3000000);
    thread wCiasto (producer,mCiasto,1,125000);
    thread wPierogi (prodCons,mFarsz,mCiasto,mPierogi,200000);
    thread dyspoz (consumer,mPierogi,333333);

    thread visio (visualization,mFarsz,mCiasto,mPierogi);

    // simulation time
    sleep(SIMULATION_TIME);

    delete mFarsz;
    delete mCiasto;
    delete mPierogi;

    return 0;
}
