/**
 * @file linklist.h
 * @author Shreya Chakraborty
 * @brief 
 * @version 0.1
 * @date 2019-09-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef LINKLIST_H_
#define LINKLIST_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node* next;
};

//extern struct node* head;

/**
 * @brief Adding the integers read from the file using getline into the list
 * 
 * @param reference to head 
 * @param data 
 * @return int 
 */
int addtolist(struct node** head,int data); //add to tail

/**
 * @brief Iterates through the list till the end and prints the data with tab space
 * 
 * @param refernce to head 
 * @return int 
 */
int DisplayList(struct node **head);

/**
 * @brief same as , print the data on console line by line
 * 
 * @param refence to head 
 * @return int 
 */
int DisplayListStdio(struct node **head);

/**
 * @brief Splits the list into half with the first half getting an extra node in case the list size is odd
 * 
 * @param head to the list to split
 * @param list1 refence to the head of the first half list
 * @param list2 refence to the head of the second half list
 * @return int 
 */
int SplitList(struct node *head,struct node **list1,struct node **list2);

void PrintList(int A[], int size);
#endif