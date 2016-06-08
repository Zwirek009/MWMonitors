/// File: include.h
/// Contents: All library includes and defines for project

#ifndef INCLUDE_H
#define INCLUDE_H

#include <iostream>
#include <thread>

#include </usr/include/sys/shm.h>
#include </usr/include/sys/types.h>
#include </usr/include/sys/ipc.h>
#include </usr/include/sys/sem.h>
#include </usr/include/sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sched.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MUTEX 0
#define FREE_SPACE 1
#define IN_QUEUE 2

#define MAX_QUEUE 100
#define SIMULATION_TIME 60

#endif // INCLUDE_H
