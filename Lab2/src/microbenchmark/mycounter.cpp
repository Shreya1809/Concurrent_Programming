#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <malloc.h>
#include "parse.h"
#include "locks.h"

using namespace CP;

ILockSharedPtr _counterLock = nullptr;

pthread_t tid[370]; //max threads possible
int cntr = 0; //global counter


void *counter(void *args);
int main(int argc , char *argv[])
{
    string dummy = "\0";
    printf("******Micro Benchmark by Shreya*******\n");
    int val1 = ParseCommandline(argc ,argv, dummy , dummy);
    if(val1 == 1) //name flag is on
    {
        return 0;
    }
    //get the type of lock from commandline
    _counterLock = LockFactory::GetLockObject(lockType);
    //spawn n number of threads for i iterations
    int mytid[numOfThreads] = {0};
    for(int i = 0; i < numOfThreads ; ++i)
    {
        mytid[i] = i;
        printf("i is %d\n", mytid[i]);
        pthread_create(&tid[i], NULL, counter, (void*)&mytid[i]); 
    }
    
    for(int i = 0; i< numOfThreads ; i++)
    {
        pthread_join(tid[i], NULL); 
    }

    printf("[counter]:\t%d\n",cntr);
    return 0;
}

void *counter(void *args)
{
    int my_tid =  *((int*)args);
    int mythreaditer = numofiterations * numOfThreads;
    printf("my_tid = %d and my iterations %d\n",my_tid, mythreaditer);
    for(int i = 0; i< mythreaditer; i++)
    {
        if(i % numOfThreads == my_tid)
        {
            //lock();
            _counterLock->Lock();
            cntr++;
            printf("my_tid = %d, counter %d\n",my_tid,cntr);
            _counterLock->Unlock();
            //unlock();
        }
    }
    return NULL;
}