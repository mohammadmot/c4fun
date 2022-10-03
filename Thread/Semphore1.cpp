/*
SEMAPHORE HEADER C++(MULTI_THREADING)Introduction

Introduction to semphore library header
    A semaphore is a variable or abstract data type used to control access to
    a common resource by multiple processes in a concurrent system such as
    a multitasking operating system.
    A semaphore is simply a variable and basically a counting and signalling mechanism.
    If there is a single item, then a semaphore is virtually the same as a mutex.

The <semaphore.h> header defines the sem_t type,
used in performing semaphore operations.
An unnamed semaphore is initialized with a call to semi_init().
There are 4 basic semaphore functions and they start with sem_.

A semaphore is created with the sem_init function, and it is declared in semaphore.h:
int sem_init(sem_t *sem, int pshared, unsigned int val);
    - It initializes a semaphore object pointed by sem,
      sets its sharing option, and gives it an initial integer value.
    - The pshared parameter controls the type of semaphore.
      If the value of pshared is 0, the semaphore is local to the current process,
      i.e. private to a single process.
      Otherwise, the semaphore may be shared between processes.
    - The third parameter is the value with which to initialize the semaphore.
    - Semaphore is destroyed with a call to sem_destroy().

*/

/*
    In the code, we initialized a semaphore with a count of 3.
    The second parameter of the call to sem_init() is 0,
     and this makes the semaphore private to the thread.
    Passing the value of one would enable the semaphore to be shared between
     multiple processes.
    Compilation should be done with gcc Semphore1.cpp -lpthread -lrt

    2 threads are created, one 1 seconds after the first one.
    But the first thread will sleep for 5 seconds after acquiring the lock.
    Therefore the second thread will not enter immediately after it is called,
    it will enter 5 %u2013 1= 3 secs after it is called.
*/
#include <semaphore.h>
#include <pthread.h>
#include <iostream>

#include <thread> // sleep
#include <chrono>

sem_t mySemaphore;
using namespace std;

void *threadFunc(void *arg)
{
    // wait
    sem_wait(&mySemaphore);
    printf("\nEntered..\n");

    // critical section
    // sleep(5);
    this_thread::sleep_for(chrono::milliseconds(5));

    // signal
    printf("\nExiting..\n");
    sem_post(&mySemaphore);
}

int main()
{
    sem_t mySemaphore;
    sem_init(&mySemaphore, 0, 3);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, threadFunc, NULL);

    // sleep(1);
    this_thread::sleep_for(chrono::milliseconds(1));

    pthread_create(&t2, NULL, threadFunc, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&mySemaphore);

    return 0;
}

/*
// We can also use a named semaphore  which is named rather than initialised.
// The sem_open() returns a pointer to the semaphore.

#include <semaphore.h>
#include <fcntl.h>

int main()
{
        sem_t *mySemaphore;
        mySemaphore = sem_open("./my_sem", O_CREAT, 0777, 5);
        //your code
        sem_close(mySemaphore);
        sem_unlink("./my_sem");

        return 0;
}
*/