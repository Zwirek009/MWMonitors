#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "include.h"

class Semaphore // 3 semaphores set - MUTEX, FREE_SPACE, INQUEUE
{
private:
    int semid;

public:
    Semaphore();        // default constructor, returns error
    Semaphore(int key); // constructor
    ~Semaphore();       // default destructor

    int getSemid();

    void P(int num);    // semaphore down
    void V(int num);    // semaphore up

};

#endif // SEMAPHORE_H
