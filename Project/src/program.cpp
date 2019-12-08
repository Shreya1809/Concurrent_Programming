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
struct timespec start_time1, end_time1;
pthread_barrier_t bar;

struct _ThreadArg
{
    int key[1000];
    char val[1000][10];
    int thread_no;
};

void *InsertFunction(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg*)args;
    if(arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void*)1;
    }
    //printf("key: %d, val: %s\n",arg->key, arg->val);
    pthread_barrier_wait(&bar);
    //FG_Insert(&root,arg->key,arg->val);
    for(int i = 0; i < iteration; i++)
    {
        FG_Insert_char(&root,arg->key[i],arg->val[i]);
    }
    //free(arg);
    return NULL;
}
void *SearchFunction(void *args)
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
            printf("Key not found: key[%d] Thread[%d]\n",arg->key[i],arg->thread_no);
        }
        //printf("Thread[%d]      Key[%d]     status[%d]      value[%d]\n",arg->thread_no, arg-> key,status,FG_GetValue(root,arg->key));
        printf("Thread[%d]      Key[%d]     status[%d]      value[%s]\n",arg->thread_no,arg-> key[i],status,FG_GetValue_char(root,arg->key[i]));
    }
    //free(arg);
    return NULL;
}
int main(int argc , char *argv[])
{
    printf("******Final project by by Shreya*******\n");
    int commandFlag;
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
    //int rand_array[numOfThreads] = {0};

    if(numOfThreads == 1)
    {
        ActualWork(commandFlag);
    }
    else
    {
        for (int i = 0; i < numOfThreads; i++)
        {
            //threadArg[i].val[i] = (char*)malloc(iteration*sizeof(char));
            for(int j = 0; j < iteration; j++)
            {
                threadArg[i].key[j] = rand();
                memcpy(threadArg[i].val[j],(rand_value(mytext , sizeof(mytext), i)),sizeof(threadArg[i].val[j]));
                //strcpy(threadArg[i].val[j],std::string(rand_value(mytext , sizeof(mytext), i)));
                //threadArg[i].val[j] = std::string(rand_value(mytext , sizeof(mytext), i));
                printf("Thread[%d] key %d -> val %s\n", i, threadArg[i].key[j], threadArg[i].val[j]);
            }
            threadArg[i].thread_no = i;
        }
        printf("Total number of Nodes is %d\n",numOfThreads*iteration);
        //clock_gettime(CLOCK_MONOTONIC,&start_time1);
        for(int i = 0; i < numOfThreads; i++)
        {
            pthread_create(&threads[i], NULL, InsertFunction, 
                                            (void*)&threadArg[i]); 
        }
        printf("%d threads created\n",numOfThreads);
        for (int i = 0; i < numOfThreads; i++)
        { 
            pthread_join(threads[i], NULL);
            printf("joined thread number %d\n",i); 
        }
        //FG_Destroy(root);
        for(int i = 0; i < numOfThreads; i++)
        {
            pthread_create(&threads[i], NULL, SearchFunction, 
                                            (void*)&threadArg[i]); 
        }
        printf("%d threads created\n",numOfThreads);
        for (int i = 0; i < numOfThreads; i++)
        { 
            pthread_join(threads[i], NULL);
            //printf("joined thread number %d\n",i); 
        }
        deleteTree(root);
        //free(threadArg);
        pthread_barrier_destroy(&bar);
        //clock_gettime(CLOCK_MONOTONIC,&end_time1);
        

    }
   //clean everything before exit. 
    printf("Program Done\n");      
    return 0;
}
    

