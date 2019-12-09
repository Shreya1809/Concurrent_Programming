/**
 * @file program.c
 * @author your name Shreya Chakraborty
 * @brief Sort a file of integers and write the output in another file
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
 
/*
Program Approach
1. Get the command line options and parse it using getopt_long()
2. Check of the existence of sourcefile using access()
3. Open the source file, read each line of it using getline(), convert string into integer and add to tail of list
4. Apply mergesort algorithm to the linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>
#include <time.h>
using namespace std;

#include "parse.h"
#include "tree.h"
#include "utils.h"
#include "commandhandler.h"
#include "fg_tree.h"
#include "lock.h"

extern LOCK_T root_lock;
//pthread_mutex_t bst_lock;

struct fg_treenode *root = NULL;
struct timespec wr_hi_start, wr_hi_end, rd_hi_start, rd_hi_end, wr_low_start,wr_low_end,rd_low_start,rd_low_end,rg_hi_start,rg_hi_end;
double wr_hi, wr_low,rd_hi,rd_low,rg_time;
pthread_barrier_t bar;
int counter = 1;
int key = 0;
struct _ThreadArg
{
    int key[100];
    char val[100][10];
    int thread_no;
};

void *InsertFunction_LC(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg*)args;
    if(arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void*)1;
    }
    //printf("key: %d, val: %s\n",arg->key, arg->val);
    pthread_barrier_wait(&bar);
    for(int i = 0; i < iteration; i++)
    {
        FG_Insert_char(&root,arg->key[i],arg->val[i]);
        
    }
    return NULL;
}

void *InsertFunction_HC(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg*)args;
    if(arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void*)1;
    }
    //printf("key: %d, val: %s\n",arg->key, arg->val);
    pthread_barrier_wait(&bar);
    for(int i = 0; i < iteration; i++)
    { 
        FG_Insert_char(&root,1,arg->val[i]);
    }
    return NULL;
}
void *SearchFunction_LC(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg*)args;
    if(arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void*)1;
    }
    //printf("key: %d, val: %s\n",arg->key, arg->val);
    pthread_barrier_wait(&bar);
    for(int i = 0; i < iteration; i++)
    {
        bool status = FG_searchTree(root,arg->key[i]);   
        if(!status)
        {
            printf("Key not found LC: key[%d]\tThread[%d]\n",arg->key[i],arg->thread_no);
        }
        //printf("Thread[%d]      Key[%d]     status[%d]      value[%d]\n",arg->thread_no, arg-> key,status,FG_GetValue(root,arg->key));
        //printf("Read Intensive, Low Contention: Thread[%d]\tEntry[%d]\tKey[%d]\tstatus[%d]\tvalue[%s]\n",arg->thread_no, counter++,arg-> key[i],status,FG_GetValue_char(root,arg->key[i]));
    }
    
    return NULL;
}

void *SearchFunction_HC(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg*)args;
    if(arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void*)1;
    }
    pthread_barrier_wait(&bar); //do i need barriers?
    for(int i = 0; i < iteration; i++)
    {
        bool status = FG_searchTree(root,1); //hardcoded find key 1
        if(!status)
        {
            printf("Key not found HC: Thread[%d]\n",arg->thread_no);
        }
        //printf("Thread[%d]      Key[%d]     status[%d]      value[%d]\n",arg->thread_no, arg-> key,status,FG_GetValue(root,arg->key));
        //printf("Read Intensive, Low Contention: Thread[%d]\tEntry[%d]\tKey[%d]\tstatus[%d]\tvalue[%s]\n",arg->thread_no, counter++,arg-> key[i],status,FG_GetValue_char(root,arg->key[i]));
    }
    return NULL;
}

void *Range(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg*)args;
    if(arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void*)1;
    }
    pthread_barrier_wait(&bar); //do i need barriers?
    printf("Thread[%d]\n",arg->thread_no);
    FG_Range(root,0, 200000000);
    return NULL;
}
int main(int argc , char *argv[])
{
    printf("******Final project by by Shreya*******\n");
    int commandFlag,rc;
    char mytext[20] = {0};
    int val = ParseCommandline(argc ,argv, commandFlag);
    if(val == 1) //name flag is on
    {
        return 0;
    }
    LOCK_INIT(root_lock);
    pthread_t threads[numOfThreads];
    struct _ThreadArg threadArg[numOfThreads] = {0};
    pthread_barrier_init(&bar, NULL, numOfThreads);

    if(numOfThreads == 1)
    {
        ActualWork(commandFlag);
    }
    else
    {
        for (int i = 0; i < numOfThreads; i++)
        {
            for(int j = 0; j < iteration; j++)
            {
                threadArg[i].key[j] = rand();
                memcpy(threadArg[i].val[j],(rand_value(mytext , sizeof(mytext), i)),sizeof(threadArg[i].val[j]));
                //printf("Thread[%d] key %d -> val %s\n", i, threadArg[i].key[j], threadArg[i].val[j]);
            }
            threadArg[i].thread_no = i;
        }
        printf("Total number of Nodes is %d\n",numOfThreads*iteration);


        //threads for loc contention insert
        clock_gettime(CLOCK_REALTIME, &wr_low_start); 
        for(int i = 0; i < numOfThreads; i++)
        {
            rc = pthread_create(&threads[i], NULL, InsertFunction_LC, 
                                            (void*)&threadArg[i]); 
            if(rc)
            {
                printf("pthread_create failed for thread %d\n",i);
            }
                
        }
        for (int i = 0; i < numOfThreads; i++)
        { 
            pthread_join(threads[i], NULL);
        }
        clock_gettime(CLOCK_REALTIME, &wr_low_end);
        wr_low = (wr_low_end.tv_sec - wr_low_start.tv_sec) * 1000000 + (wr_low_end.tv_nsec - wr_low_start.tv_nsec) / 1000; 

        //threads for low contention search
        clock_gettime(CLOCK_REALTIME, &rd_low_start); 
        for(int i = 0; i < numOfThreads; i++)
        {
            rc = pthread_create(&threads[i], NULL, SearchFunction_LC, 
                                            (void*)&threadArg[i]);
            if(rc)
            {
                printf("pthread_create failed for thread %d\n",i);
            }
        }
        for (int i = 0; i < numOfThreads; i++)
        { 
            pthread_join(threads[i], NULL);
            //printf("joined thread number %d\n",i); 
        }
        clock_gettime(CLOCK_REALTIME, &rd_low_end);
        rd_low = (rd_low_end.tv_sec - rd_low_start.tv_sec) * 1000000 + (rd_low_end.tv_nsec - rd_low_start.tv_nsec) / 1000;    
        
        //threads for range query
        clock_gettime(CLOCK_REALTIME, &rg_hi_start); 
        for(int i = 0; i < numOfThreads; i++)
        {
            rc = pthread_create(&threads[i], NULL, Range, 
                                            (void*)&threadArg[i]);
            if(rc)
            {
                printf("pthread_create failed for thread %d\n",i);
            }
        }
        for (int i = 0; i < numOfThreads; i++)
        { 
            pthread_join(threads[i], NULL);
            //printf("joined thread number %d\n",i); 
        }
        clock_gettime(CLOCK_REALTIME, &rg_hi_end);
        rg_time = (rg_hi_end.tv_sec - rg_hi_start.tv_sec) * 1000000 + (rg_hi_end.tv_nsec - rg_hi_start.tv_nsec) / 1000;    
        //threads for high contention insert 
        clock_gettime(CLOCK_REALTIME, &wr_hi_start); 
        for(int i = 0; i < numOfThreads; i++)
        {
            rc = pthread_create(&threads[i], NULL, InsertFunction_HC, 
                                            (void*)&threadArg[i]);
            if(rc)
            {
                printf("pthread_create failed for thread %d\n",i);
            }
        }
        for (int i = 0; i < numOfThreads; i++)
        { 
            pthread_join(threads[i], NULL);
            //printf("joined thread number %d\n",i); 
        }
        clock_gettime(CLOCK_REALTIME, &wr_hi_end);
        wr_hi += (wr_hi_end.tv_sec - wr_hi_start.tv_sec) * 1000000 + (wr_hi_end.tv_nsec - wr_hi_start.tv_nsec) / 1000;    

        //threads for high contention search
        clock_gettime(CLOCK_REALTIME, &rd_hi_start); 
        for(int i = 0; i < numOfThreads; i++)
        {
            rc = pthread_create(&threads[i], NULL, SearchFunction_HC, 
                                            (void*)&threadArg[i]);
            if(rc)
            {
                printf("pthread_create failed for thread %d\n",i);
            }
        }
        for (int i = 0; i < numOfThreads; i++)
        { 
            pthread_join(threads[i], NULL);
            //printf("joined thread number %d\n",i); 
        }
        clock_gettime(CLOCK_REALTIME, &rd_hi_end);
        rd_hi = (rd_hi_end.tv_sec - rd_hi_start.tv_sec) * 1000000 + (rd_hi_end.tv_nsec - rd_hi_start.tv_nsec) / 1000;    
        
        deleteTree(root);
        pthread_barrier_destroy(&bar);
        

    }
   //clean everything before exit. 
    printf("Low Contention write:\n");
    printf("Threads\tIterations\tNodes\tTime(us)\n");
    printf("%d\t%d\t\t%d\t%lf\n",numOfThreads,iteration,numOfThreads*iteration,wr_low);
    printf("High Contention write:\n");
    printf("Threads\tNodes\tTime(us)\n");
    printf("%d\t%d\t%lf\t\n",numOfThreads,numOfThreads,wr_hi);
    printf("Low Contention Read:\n");
    printf("Threads\tIterations\tNodes\tTime(us)\n");
    printf("%d\t%d\t\t%d\t%lf\n",numOfThreads,iteration,numOfThreads*iteration,rd_low);
    printf("High Contention read:\n"); 
    printf("Threads\tNodes\tTime(us)\n");
    printf("%d\t%d\t%lf\t\n",numOfThreads,numOfThreads,rd_hi); 
    printf("Range Query:\n"); 
    printf("Threads\tNodes\tTime(us)\n");
    printf("%d\t%d\t%lf\t\n",numOfThreads,numOfThreads,rg_time); 
    printf("Program Done\n");    
    return 0;
}
    

