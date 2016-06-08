#include "semaphore.h"

Semaphore::Semaphore()
{
    printf( RED "Blad podczas tworzenia semaforow -> nie podano klucza semafora\n" RED );
    exit(1);
}

Semaphore::Semaphore(int key)
{
    // semaphores initialization
    semid = semget((key_t)key, 3, IPC_CREAT|0600);

    // set initial values
    semctl(semid, MUTEX, SETVAL, (int)1);
    semctl(semid, FREE_SPACE, SETVAL, (int)MAX_QUEUE);
    semctl(semid, IN_QUEUE, SETVAL, (int)0);
}

Semaphore::~Semaphore()
{
    // semaphores deallocation
    semctl(semid, 0, IPC_RMID, (struct semid_ds *)0);
}

int Semaphore::getSemid()
{
    return semid;
}

void Semaphore::P(int num)  // down
{
    struct sembuf buf;
    buf.sem_num = num;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    semop( semid, &buf, 1);
}

void Semaphore::V(int num)  // up
{
    struct sembuf buf;
    buf.sem_num = num;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    semop( semid, &buf, 1);
}
