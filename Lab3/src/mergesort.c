/**
 * @file mergesort.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "mergesort.h"
#include <string.h>
#include <omp.h>

/*
*Refernce : https://www.geeksforgeeks.org/iterative-merge-sort/ 
*/
void MergeArray(int input[], int left, int mid, int right) 
{ 
    int i, j, k; //index of 1st subarray, 2nd subarray and resultant array
    int L_size = mid - left + 1; 
    int R_size =  right - mid; 
  
    /* creating 2 left and right temporary arrays */
    int L[L_size], R[R_size]; 
  
    /* Copying from input array into temp arrays L[] and R[] */
    for (i = 0; i < L_size; i++) 
        L[i] = input[left + i]; 
    for (j = 0; j < R_size; j++) 
        R[j] = input[mid + 1+ j]; 
  
    i = 0; j = 0; k = left;
    //actual comparing and rewriting into input array 
    while (i < L_size && j < R_size) 
    { 
        if (L[i] <= R[j]) 
        { 
            input[k] = L[i]; 
            i++; 
        } 
        else
        { 
            input[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    //Copying the remaining elements of L[] and R[]
    while (i < L_size) 
    { 
        input[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < R_size) 
    { 
        input[k] = R[j]; 
        j++; 
        k++; 
    } 
} 


// function to find min of 2 integers 
int min(int x, int y) { return (x<y)? x :y; } 
  
/*Reference : https://www.geeksforgeeks.org/iterative-merge-sort/  
* Iterative mergesort function to sort arr[0...n-1] 
*/
void MergeSortArray(int arr[], int size) 
{ 
   int i;  
   int start; 
   for (i = 1; i <= size-1; i = 2*i) 
   { 
       for (start=0; start< size-1; start += 2*i) 
       {
           int mid = min(start + i - 1, size-1); 
           int end = min(start + 2*i - 1, size-1); 
           MergeArray(arr, start, mid, end); 
       } 
   } 
} 

void OMP_mergesort(int arr[], int size, int threads)
{
    if (threads == 1)
    {
        MergeSortArray(arr, size);  
    }
    else if (threads > 1)
    {
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                OMP_mergesort(arr, size / 2, threads / 2);
            }
            #pragma omp section
            {	
                OMP_mergesort(arr + size / 2, size - size / 2, threads - threads / 2);
            }
        }
      
      merge (arr, size);//, temp);
    }
  else
    {
      printf ("Error: %d threads\n", threads);
      return;
    }
}

int merge(int arr[], int size)
{
    int *temp = (int*)malloc(sizeof(int) * size);
    if (temp == NULL)
    {
      printf ("Error: Could not allocate array of size %d\n", size);
      return 1;
    }
    int L_index = 0;
    int R_index = size / 2;
    int i = 0; //index for temporary list
    while (L_index < size / 2 && R_index < size)
    {
        if (arr[L_index] < arr[R_index])
        {
            temp[i] = arr[L_index];
            L_index++;
        }
        else
        {
            temp[i] = arr[R_index];
            R_index++;
        }
        i++;
    }
    while (L_index < size / 2)
        {
        temp[i] = arr[L_index];
        L_index++;
        i++;
        }
    while (R_index < size)
        {
        temp[i] = arr[R_index];
        R_index++;
        i++;
        }
  // Copy sorted temp array into main array, arr
    memcpy (arr, temp, size * sizeof (int));
    free(temp);
    return 0;
}

void OMP_merge(int arr[], int size, int threads)
{
  omp_set_nested (1);
  // Parallel mergesort
  OMP_mergesort(arr, size, threads);
}  


