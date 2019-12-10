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
struct timespec start_time[5],end_time[5];
double diff[5];
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
    struct _ThreadArg *arg = (struct _ThreadArg *)args;
    if (arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void *)1;
    }
    pthread_barrier_wait(&bar);
    for (int i = 0; i < iteration; i++)
    {
        FG_Insert_char(&root, arg->key[i], arg->val[i]);
        if(log_mode)
        {
            printf("INSERT_LC-->Thread[%d]\tkey[%d]\tvalue[%s]\n",arg->thread_no,arg->key[i],arg->val[i]);
        }
        
    }
    return NULL;
}

void *InsertFunction_HC(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg *)args;
    if (arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void *)1;
    }
    pthread_barrier_wait(&bar);
    for (int i = 0; i < iteration; i++)
    {
        FG_Insert_char(&root, 1, arg->val[i]);
        if(log_mode)
        {
            printf("INSERT_HC-->Thread[%d]\tkey[1]\tvalue[%s]\n",arg->thread_no,arg->val[i]);
        }
    }
    return NULL;
}
void *SearchFunction_LC(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg *)args;
    if (arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void *)1;
    }
    //printf("key: %d, val: %s\n",arg->key, arg->val);
    pthread_barrier_wait(&bar);
    for (int i = 0; i < iteration; i++)
    {
        bool status = FG_searchTree(root, arg->key[i]);
        if (!status)
        {
            printf("Key not found LC: key[%d]\tThread[%d]\n", arg->key[i], arg->thread_no);
        }
        if(log_mode)
        {
            printf("SEARCH_LC-->Thread[%d]      Key[%d]     status[%d]      value[%s]\n",arg->thread_no, arg->key[i],status,FG_GetValue_char(root,arg->key[i]));
        }
    }

    return NULL;
}

void *SearchFunction_HC(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg *)args;
    if (arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void *)1;
    }
    pthread_barrier_wait(&bar); //do i need barriers?
    for (int i = 0; i < iteration; i++)
    {
        bool status = FG_searchTree(root, 1); //hardcoded find key 1
        if (!status)
        {
            printf("Key not found HC: Thread[%d]\n", arg->thread_no);
        }
        if(log_mode)
        {
            printf("SEARCH_HC-->Thread[%d]      Key[1]     status[%d]      value[%s]\n",arg->thread_no,status,FG_GetValue_char(root,1));
        }
    }
    return NULL;
}

void *Range(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg *)args;
    if (arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void *)1;
    }
    pthread_barrier_wait(&bar); //do i need barriers?
    FG_Range(root, 0, 20000000,arg->thread_no,log_mode);
    return NULL;
}

void *(*ThreadFunction[5])(void *ptr) =
    {
        InsertFunction_LC,
        SearchFunction_LC,
        Range,
        InsertFunction_HC,
        SearchFunction_HC
    };

int main(int argc, char *argv[])
{
    printf("******Final project by by Shreya*******\n");
    int commandFlag, rc;
    char mytext[20] = {0};
    int val = ParseCommandline(argc, argv, commandFlag);
    if (val == 1) //name flag is on
    {
        return 0;
    }
    LOCK_INIT(root_lock);
    pthread_t threads[numOfThreads];
    struct _ThreadArg threadArg[numOfThreads] = {0};
    // pthread_barrier_init(&bar, NULL, numOfThreads);

    if (numOfThreads == 1)
    {
        ActualWork(commandFlag);
    }
    else
    {
        for (int i = 0; i < numOfThreads; i++)
        {
            for (int j = 0; j < iteration; j++)
            {
                threadArg[i].key[j] = rand();
                memcpy(threadArg[i].val[j], (rand_value(mytext, sizeof(mytext), i)), sizeof(threadArg[i].val[j]));
                if(log_mode){printf("Thread[%d] key[%d]\tval[%s]\n", i, threadArg[i].key[j], threadArg[i].val[j]);
                }
            }
            threadArg[i].thread_no = i;
        }
        printf("Total number of Nodes is %d\n", numOfThreads * iteration);

        for(int j = 0; j < 5; j++)
        {
            pthread_barrier_init(&bar, NULL, numOfThreads);
            // if(j == 3)
            // {
            //     root = deleteTree(root);
            // }

            clock_gettime(CLOCK_REALTIME, &start_time[j]);
            for (int i = 0; i < numOfThreads; i++)
            {
                rc = pthread_create(&threads[i], NULL, ThreadFunction[j],
                                    (void *)&threadArg[i]);
                if (rc)
                {
                    printf("pthread_create failed for thread %d\n", i);
                }
            }
            for (int i = 0; i < numOfThreads; i++)
            {
                pthread_join(threads[i], NULL);
            }
            clock_gettime(CLOCK_REALTIME, &end_time[j]);
            diff[j] = (end_time[j].tv_sec - start_time[j].tv_sec) * 1000000 + (end_time[j].tv_nsec - start_time[j].tv_nsec) / 1000;
            pthread_barrier_destroy(&bar);
        }
        root = deleteTree(root);
        FG_InorderDisplay(root);
        // pthread_barrier_destroy(&bar);
    }
    //clean everything before exit.
    printf("\n**********************************************************\n");
    printf("Timing analysis of the operations--->\n");
    printf("Low Contention write:\n");
    printf("Threads\tIterations\tNodes\tTime(us)\n");
    printf("%d\t%d\t\t%d\t%lf\n", numOfThreads, iteration, numOfThreads * iteration, diff[0]);
    printf("High Contention write:\n");
    printf("Threads\tNodes\tTime(us)\n");
    printf("%d\t%d\t%lf\t\n", numOfThreads, numOfThreads, diff[3]);
    printf("Low Contention Read:\n");
    printf("Threads\tIterations\tNodes\tTime(us)\n");
    printf("%d\t%d\t\t%d\t%lf\n", numOfThreads, iteration, numOfThreads * iteration, diff[1]);
    printf("High Contention read:\n");
    printf("Threads\tNodes\tTime(us)\n");
    printf("%d\t%d\t%lf\t\n", numOfThreads, numOfThreads, diff[4]);
    printf("Range Query:\n");
    printf("Threads\tNodes\tTime(us)\n");
    printf("%d\t%d\t%lf\t\n", numOfThreads, numOfThreads, diff[2]);
    printf("Program Done\n");

    std::ofstream ofr("samplesN" + std::to_string(numOfThreads) + ".csv", std::ios::app);
    if(ofr.fail())
    {
        printf("Cannot open samples.csv to write\n");
        return 1;
    }
    ofr << diff[1] << "," << diff[0] << "," << diff[4] << ","<< diff[3] << ","<< diff[2] << "\n";
    ofr.close();
    return 0;
}
