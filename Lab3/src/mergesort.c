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
#include <omp.h>

struct node* MergeList(struct node* list1,struct node* list2)
{
    struct node* MergedList = NULL;
    if(list1 == NULL) // is either list exhausts, return the elements of the other
        return list2;
    if(list2 == NULL)
        return list1;
    
    if(list1->data < list2->data)
    {
        MergedList = list1;// list1 has smaller integer, add that node to the final merged node
        MergedList->next = MergeList(list1->next,list2);//compare the next element of list1 with list 2
    }
    else
    {
        MergedList = list2;// list2 has smaller integer, add that node to the final merged node
        MergedList->next = MergeList(list1,list2->next);//recursive call ,compare the next element of list1 with list 2   
    }
    return MergedList;

}

void MergeSortList(struct node **head)
{
    struct node* temp = *head;
    struct node* list1;
    struct node* list2;
    if(temp == NULL)
    {
        //length is 0
        return;
    }
    if(temp->next == NULL)
    {
        //length is 1
        return;
    }
    //find middle of the list and split
    SplitList(temp,&list1,&list2);
    MergeSortList(&list1);
    MergeSortList(&list2);
    *head = MergeList(list1,list2);
}

void MergeArray(int input[], int left, int mid, int right) 
{ 
    int i, j, k; 
    int n1 = mid - left + 1; 
    int n2 =  right - mid; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = input[left + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = input[mid + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = left; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
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
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        input[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        input[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void MergeSortArray(int input[], int left, int right) 
{ 
    if (left < right) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int mid = left+(right-left)/2; 
        #pragma omp parallel 
        {
            #pragma omp single
            {
                #pragma omp task
                {
                    MergeSortArray(input, left, mid); 
                }
                #pragma omp task
                {
                    MergeSortArray(input, mid+1, right); 
                }
            }
        }
        // Sort first and second halves 
        MergeArray(input, left, mid, right); 
       
    } 
} 

void OMP_merge(int input[], int left, int right) 
{
    omp_set_nested (1);
    MergeSortArray(input, left,right); 
}
