#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <malloc.h>
#include "locks.h"
#include "barriers.h"
#include "parse.h"

using namespace CP;

ILockSharedPtr _counterLock = nullptr;
IBarSharedPtr _counterBar = nullptr;
int lock_bar_flag = 0;
struct timespec counter_start, counter_end;
pthread_t tid[370]; //max threads possible
volatile int cntr = 0; //global counter


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
    if(lockType != CP::LockType::NONE)
    {
        _counterLock = LockFactory::GetLockObject(lockType);
        lock_bar_flag = 0;
    }
    else if(barType != CP::BarType::NONE)
    {
         _counterBar = BarFactory::GetBarObject(barType, numOfThreads);
         lock_bar_flag = 1;
    }
    else
    {
        return 1;
    }
    //printf("lock type is %d\n",_counterLock->GetLockType());
   
    //printf("Bar type is %d\n", _counterBar->GetBarType());
    //spawn n number of threads for i iterations
    int mytid[numOfThreads] = {0};
    clock_gettime(CLOCK_MONOTONIC,&counter_start);
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
    clock_gettime(CLOCK_MONOTONIC,&counter_end);
    printf("[counter]:\t%d\n",cntr);
    unsigned long long elapsed_ns;
	elapsed_ns = (counter_end.tv_sec-counter_start.tv_sec)*1000000000 + (counter_end.tv_nsec-counter_start.tv_nsec);
	printf("Elapsed (ns): %llu\n",elapsed_ns);
	double elapsed_s = ((double)elapsed_ns)/1000000000.0;
	printf("Elapsed (s): %lf\n",elapsed_s);
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
            if(lock_bar_flag)
            {
                cntr++;
                _counterBar->wait();
            }
            else 
            {
                _counterLock->Lock();
                cntr++;
                _counterLock->Unlock();
            }
            
        }
    }
    return NULL;
}