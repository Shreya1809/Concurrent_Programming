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

struct node* Merge(struct node* list1,struct node* list2)
{
    struct node* MergedList = NULL;
    if(list1 == NULL) // is either list exhausts, return the elements of the other
        return list2;
    if(list2 == NULL)
        return list1;
    
    if(list1->data < list2->data)
    {
        MergedList = list1;// list1 has smaller integer, add that node to the final merged node
        MergedList->next = Merge(list1->next,list2);//compare the next element of list1 with list 2
    }
    else
    {
        MergedList = list2;// list2 has smaller integer, add that node to the final merged node
        MergedList->next = Merge(list1,list2->next);//recursive call ,compare the next element of list1 with list 2   
    }
    return MergedList;

}

void MergeSort(struct node **head)
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
    MergeSort(&list1);
    MergeSort(&list2);
    *head = Merge(list1,list2);
}
