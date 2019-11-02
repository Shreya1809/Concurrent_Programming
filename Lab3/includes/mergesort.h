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

void MergeArray(int input[], int left, int mid, int right);

void MergeSortArray(int arr[], int size);

void OMP_merge(int a[], int size, int threads);

int merge (int a[], int size);

void OMP_mergesort(int a[], int size,int threads);

#endif
