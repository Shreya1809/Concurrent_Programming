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
    int key;
    char val[10];
    int thread_no;
};

void *ThreadFunction(void *args)
{
    struct _ThreadArg *arg = (struct _ThreadArg*)args;
    if(arg == NULL)
    {
        printf("Thread arg is NULL\n");
        return (void*)1;
    }
    //printf("key: %d, val: %s\n",arg->key, arg->val);
    pthread_barrier_wait(&bar);
    root = FG_Insert(root,arg->key,arg->val);
    LOCK_UNLOCK(root_lock);
    // if(FG_searchTree(root,arg->key))
    // {
    //     printf("[%d] The Value corresponding to %d is %s\n", arg->thread_no,arg->key,FG_GetValue(root,arg->key));
    // }
    return 0;
}

int main(int argc , char *argv[])
{
    printf("******Final project by by Shreya*******\n");
    int commandFlag;
    int val = ParseCommandline(argc ,argv, commandFlag);
    if(val == 1) //name flag is on
    {
        return 0;
    }
    LOCK_INIT(root_lock);
    pthread_t threads[numOfThreads];
    struct _ThreadArg threadArg[numOfThreads] = {0};
    pthread_barrier_init(&bar, NULL, numOfThreads);
    int rand_array[numOfThreads] = {0};

    if(numOfThreads == 1)
    {
        ActualWork(commandFlag);
    }
    else
    {
        for (int i = 0; i < numOfThreads; i++)
        {
            threadArg[i].key = rand_key();
            rand_array[i] = threadArg[i].key;
            threadArg[i].thread_no = i;
            // memcpy(threadArg[i].val,(rand_value(mytext , sizeof(mytext), i)),sizeof(threadArg[i].val));
            rand_value(threadArg[i].val , sizeof(threadArg[i].val), i);
            printf("[%d] key %d -> val %s\n", i, threadArg[i].key, threadArg[i].val);
        }

        //clock_gettime(CLOCK_MONOTONIC,&start_time1);
        for(int i = 0; i < numOfThreads; i++)
        {
            pthread_create(&threads[i], NULL, ThreadFunction, 
                                            (void*)&threadArg[i]); 
        }
        printf("%d threads created\n",numOfThreads);
        for (int i = 0; i < numOfThreads; i++)
        { 
            pthread_join(threads[i], NULL);
            printf("joined thread number %zu\n",i); 
        }
        pthread_barrier_destroy(&bar);
        //clock_gettime(CLOCK_MONOTONIC,&end_time1);
        //InorderDisplay(root);
        // 
        // root = FG_Insert(root,4,"mno");
        // root = FG_Insert(root,10,"abc");
        // root = FG_Insert(root,11,"xyz");
        // root = FG_Insert(root,12,"pqr");
        // root = FG_Insert(root,14,"mno");
        // root = FG_Insert(root,15,"mno");
        // root = FG_Insert(root,18,"mno");
        // root = FG_Insert(root,24,"mno");
        // root = FG_Insert(root,32,"mno");
        // root = FG_Insert(root,50,"mno");
        // FG_RangeQuery(root,10,20);
        FG_InorderDisplay(root);

    }
    
    
    
    
    
   //clean everything before exit. 
    
    
    #if 0

    //append the file path to out source and output file
    srcfilepath = std::string("../files/") + srcfilepath;
    outfilepath = std::string("../files/") + outfilepath;    

    //check if the source file exists
    if(FileExistCheck(srcfilepath.c_str()))
    {
        printf("The file exists\n");
    }
    else printf("Source file %s does not exist\n",srcfilepath.c_str());
    
    fp = fopen(srcfilepath.c_str(), "r"); // read mode
 
    if (fp == NULL)
    { 
        perror("Error while opening the file\n");
        exit(EXIT_FAILURE);
    }

    printf("Reading the numbers into array....\n");
    std::vector<int> inputNumberArray;
    //reads the file line by line, converts the string into integer and adds to the list from tail
    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &data); 
        inputNumberArray.push_back(data);
    }
    fclose(fp);
    /*cout << "File read - ";
    for(size_t i = 0; i < inputNumberArray.size(); i++)
    {
        cout<<inputNumberArray[i]<< " ";
    }
    cout<<endl;*/
    int MAX_NUMBERS = inputNumberArray.size();
    if(numOfThreads > MAX_NUMBERS)
    {
        printf("Number of threads is greater than the number of integer! INVALID! \n");
        return -1;

    }
    vector<int> outputNumberArray(0,inputNumberArray.size());

    switch(algoType){
        case FORK_JOIN:
            forkJoinMethod(&inputNumberArray, numOfThreads);
        break;
        case BUCKET_SORT:
            bucketsortMethod(&inputNumberArray, numOfThreads);
        break;
        default:
            cout<<"Invalid Sorting Algorithm"<<endl;
            return 1;
        break;
    }

    /*cout << "Sorted Array: ";
    for(size_t i = 0;  i < inputNumberArray.size(); i++)
    {
        cout<<inputNumberArray[i] << " ";
    }
    cout<<endl;*/
    bool Result = std::is_sorted(inputNumberArray.begin(),inputNumberArray.end());
    if(Result)
    {
        cout << "The resultant array is sorted " << endl;
    }
    else{
        cout << "The resultant array is NOT sorted " << endl;   
    }
    

    fp2 = fopen(outfilepath.c_str(), "w+");
    if(fp2 == NULL)
    {
        printf("Failed to create output file\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Writing sorted integers to output file\n");
        for(int i = 0; i < MAX_NUMBERS; i++)
        {
            fprintf(fp2,"%d\n",inputNumberArray[i]);
        }
        
        fclose(fp2);
    }
    #endif
    printf("Program Done\n");      
    return 0;
}
    

