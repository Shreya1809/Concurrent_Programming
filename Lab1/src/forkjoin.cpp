/**
 * @file forkjoin.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "parse.h"
#include <pthread.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


pthread_barrier_t bar;

struct timespec start_time, end_time;
int count = 0;
struct _threadArg
{
    vector<int> *inputArray;
    size_t low;
    size_t high;
    int num;
};

// merge function for merging two parts 
void merge(vector<int> &inputArray, int low, int mid, int high) 
{ 
    count++; 
    vector<int> left;
    left.resize(mid - low + 1);
    vector<int> right;
    right.resize(high - mid);
    // n1 is size of left part and n2 is size 
    // of right part 
    int n1 = mid - low + 1, n2 = high - mid, i, j; 
  
    // storing values in left part 
    for (i = 0; i < n1; i++) 
        left[i] = inputArray[i + low]; 
  
    // storing values in right part 
    for (i = 0; i < n2; i++) 
        right[i] = inputArray[i + mid + 1]; 
  
    int k = low; 
    i = j = 0; 
  
    // merge left and right in ascending order 
    while (i < n1 && j < n2) { 
        if (left[i] <= right[j]) 
            inputArray[k++] = left[i++]; 
        else
            inputArray[k++] = right[j++]; 
    } 
  
    // insert remaining values from left 
    while (i < n1) { 
        inputArray[k++] = left[i++]; 
    } 
  
    // insert remaining values from right 
    while (j < n2) { 
        inputArray[k++] = right[j++]; 
    }
} 
  

// merge sort function 
void merge_sort(vector<int> &inputArray, int low, int high) 
{ 
    // calculating mid point of array 
    int mid = low + (high - low) / 2; 
    if (low < high) { 
  
        // calling first half 
        merge_sort(inputArray, low, mid); 
  
        // calling second half 
        merge_sort(inputArray, mid + 1, high); 
  
        // merging the two halves 
        merge(inputArray, low, mid, high); 
    } 
} 

void* sort(void* threadArg) 
{ 
    struct _threadArg *arg = (struct _threadArg*)threadArg;
    pthread_barrier_wait(&bar);
    if(arg->num ==1){
		clock_gettime(CLOCK_MONOTONIC,&start_time);
	}

    printf("Thread %zu reporting for duty\n",arg->num);
    if (arg->low < arg->high) { 
        merge_sort(*(arg->inputArray), arg->low, arg->high);
    }
	pthread_barrier_wait(&bar);

    clock_gettime(CLOCK_MONOTONIC,&end_time);
    return 0;
} 

void forkJoinMethod(vector<int> *inputArray, int numOfThreads)
{
    printf("In fork join method....\n");
    pthread_t threads[numOfThreads]; 
    struct _threadArg threadArg[numOfThreads];
    const size_t MAX_ELEMENTS = inputArray->size();
    // creating n threads 
    pthread_barrier_init(&bar, NULL, numOfThreads);
    int i = 0;
    for (i = 0; i < numOfThreads; i++)
    {
        threadArg[i].num = i+1;
        threadArg[i].inputArray = inputArray;
        threadArg[i].low = i * (MAX_ELEMENTS /numOfThreads ); 
        threadArg[i].high = (i + 1) * (MAX_ELEMENTS / numOfThreads) - 1; 
    }
    threadArg[i-1].high = MAX_ELEMENTS -1;

    for(i = 0; i < numOfThreads; i++)
    {
        pthread_create(&threads[i], NULL, sort, 
                                        (void*)&threadArg[i]); 
    }
    printf("%d threads created\n",numOfThreads);
    // joining all 4 threads 
    for (i = 0; i < numOfThreads; i++)
    { 
        pthread_join(threads[i], NULL);
        printf("joined thread number %zu\n",i+1); 
    }
    pthread_barrier_destroy(&bar);

    int kArrayIndex = 0;
    size_t l = threadArg[kArrayIndex].low;
    size_t m = threadArg[kArrayIndex].high;
    kArrayIndex++;
    size_t h = threadArg[kArrayIndex].high;
    while(h < MAX_ELEMENTS && kArrayIndex < numOfThreads)
    {
        merge(*inputArray, l, m, h);
        m = h;
        kArrayIndex++;
        kArrayIndex < numOfThreads ? h = threadArg[kArrayIndex].high : 0;
    }

    unsigned long long elapsed_ns;
	elapsed_ns = (end_time.tv_sec-start_time.tv_sec)*1000000000 + (end_time.tv_nsec-start_time.tv_nsec);
	printf("Elapsed (ns): %llu\n",elapsed_ns);
	double elapsed_s = ((double)elapsed_ns)/1000000000.0;
	printf("Elapsed (s): %lf\n",elapsed_s);
}