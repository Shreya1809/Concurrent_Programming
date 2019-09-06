/**
 * @file linklist.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "linklist.h"

static struct node* head = NULL;

int addtolist(struct node** head,int data) //add to tail
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    if(head == NULL)//invalid
    {
       return -1; 
    }
    if(*head == NULL)// list is empty
    {
        //printf("List is empty\n");
        *head = new_node;
        return 1;
    }
    //list has some entries, go to the last entry
    struct node* temp = *head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
    return 0;

}

int DisplayList(struct node **head)
{
    if(head == NULL)
    {
        return -1;
    }
    if(*head == NULL)
    {
        printf("List is Empty\n");
        return 1;
    }
    struct node* temp = *head;
    while(temp != NULL)
    {
        printf("%d\t",temp->data);
        temp = temp->next;
    }
    printf("\n");
    return 0;
}

int DisplayListStdio(struct node **head)
{
    if(head == NULL)
    {
        return -1;
    }
    if(*head == NULL)
    {
        printf("List is Empty\n");
        return 1;
    }
    struct node* temp = *head;
    while(temp != NULL)
    {
        printf("%d\n",temp->data);
        temp = temp->next;
    }
    printf("\n");
    return 0;
}

int SplitList(struct node *head,struct node **list1,struct node **list2)
{
    struct node *p = head->next;
    struct node *q = head;
    while(p != NULL)
    {
        p = p->next;
        if(p != NULL)
        {
            p = p->next; 
            q = q->next;    
        }
          
    }
    *list1 = head;
    *list2 = q->next;
    q->next = NULL;
    return 0;

}