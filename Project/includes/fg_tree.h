#ifndef FG_TREE_H_
#define FG_TREE_H_

#include <stdio.h>
#include<bits/stdc++.h>
#include <pthread.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "lock.h"

struct fg_treenode{
    int key;
    char* value; 
    struct fg_treenode *left ,*right;
    LOCK_T node_lock;
};

using namespace std; 

bool FG_searchTree(struct fg_treenode *root, int key);
char * FG_GetValue(struct fg_treenode *root, int key);
struct fg_treenode* FG_newNode(int key , const char* value);
struct fg_treenode* FG_Insert(struct fg_treenode *root, int key, char* value);
//struct fg_treenode* FG_Insert2(struct fg_treenode *root, int key, char* value);
void FG_InorderDisplay(struct fg_treenode *root);
void FG_RangeQuery(struct fg_treenode* root,  int key1, int key2);

#endif