/**
 * @file mergesort.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//extern struct node* head;

/**
 * @brief Merges the 2 sorted sub lists
 * and returns the head to the sorted and merged list
 * 
 */
struct node* MergeList(struct node* list1,struct node* list2);

/**
 * @brief splits the list into halves recursively and then starts merging them back
 * 
 */
void MergeSortList(struct node **head);

void MergeArray(int input[], int left, int mid, int right);

void MergeSortArray(int input[], int left, int right);

void OMP_merge(int input[], int left, int right);

#endif
