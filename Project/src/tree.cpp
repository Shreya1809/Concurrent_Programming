// Recursive C program for level order traversal of Binary Tree 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "tree.h"

/* A binary tree node has data, pointer to left child 
and a pointer to right child */
struct treenode 
{ 
	int key;
    char* value; 
	struct treenode* left, *right; 
}; 

/* Function to print level order traversal a tree*/
void DisplayTree(struct treenode* root) 
{ 
	int h = getTreeHeight(root); 
	int i; 
	for (i=1; i<=h; i++) 
		DisplayLevel(root, i); 
} 

/* Print nodes at a given level */
void DisplayLevel(struct treenode* root, int level) 
{ 
	if (root == NULL) 
		return; 
	if (level == 1)
    { 
		printf("Key: %d ", root->key); 
        printf("Value: %s\n",root->value);
    }
	else if (level > 1) 
	{ 
		DisplayLevel(root->left, level-1); 
		DisplayLevel(root->right, level-1); 
	} 
} 

void InorderDisplay(struct treenode *root) 
{ 
    if (root != NULL) 
    { 
        InorderDisplay(root->left); 
        printf("Key: %d ", root->key);
        printf("Value: %s\n", root->value); 
        InorderDisplay(root->right); 
    } 
} 
/* Compute the "height" of a tree -- the number of 
	nodes along the longest path from the root node 
	down to the farthest leaf node.*/
int getTreeHeight(struct treenode* node) 
{ 
	if (node==NULL) 
		return 0; 
	else
	{ 
		/* compute the height of each subtree */
		int lheight = getTreeHeight(node->left); 
		int rheight = getTreeHeight(node->right); 

		/* use the larger one */
		if (lheight > rheight) 
			return(lheight+1); 
		else return(rheight+1); 
	} 
} 

/* Helper function that allocates a new node with the 
given data and NULL left and right pointers. */
struct treenode* newNode(int key , const char* value)
{ 
	struct treenode* node = (struct treenode*) 
						malloc(sizeof(struct treenode)); 
	node->key = key; 
    node->value = (char *)malloc(strlen(value) + 1);
    strcpy(node->value, value);
	node->left = NULL; 
	node->right = NULL; 
    
	return(node); 
} 

/* Driver program to test above functions*/
int TestNodeCreation(void)
{ 
	struct treenode *root = newNode(1, "ab"); 
	root->left	 = newNode(2, "bc"); 
	root->right	 = newNode(3, "cd"); 
	root->left->left = newNode(4, "de"); 
	root->left->right = newNode(5, "ef"); 

	printf("The contents of the database node creation test as follows:\n"); 
	DisplayTree(root); 
	return 0; 
}

struct treenode* PutEntry(struct treenode* node, int key, const char* value) //insertion
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key,value); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) 
        node->left  = PutEntry(node->left, key, value); 
    else if (key > node->key) 
        node->right = PutEntry(node->right, key, value);    
  
    /* return the (unchanged) node pointer */
    return node; 
} 

void TestPutEntry(void)
{
    printf("--------[PUT TEST]--------\n");
    struct treenode *root = NULL; 
    root = PutEntry(root, 50 , "abc"); 
    root = PutEntry(root, 30 , "def"); 
    root = PutEntry(root, 20 , "ghi"); 
    root = PutEntry(root, 40 , "jkl"); 
    root = PutEntry(root, 70 , "mno"); 
    root = PutEntry(root, 60 , "pqr"); 
    root = PutEntry(root, 80 , "stu");
    printf("The contents of the database for PUT test is as follows:\n"); 
	InorderDisplay(root);  
}
const char* GetValue(struct treenode* node, int key) 
{ 
    // Traverse untill root reaches to dead end 
    while (node != NULL) { 
        // pass right subtree as new tree 
        if (key > node->key) 
            node = node->right; 
  
        // pass left subtree as new tree 
        else if (key < node->key) 
            node = node->left; 
        else
            return node->value; // if the key is found return 1 
    } 
    return NULL; 
} 

void TestGetValue(int key)
{
    printf("--------[GET TEST]--------\n");
    struct treenode* root = NULL;
    int ret = 0;
    char mystring[19] = "Shreya chakraborty";
    root = PutEntry(root, key , "Shreya chakraborty"); 
    const char* getValue = GetValue(root, key);
    ret = memcmp(mystring, getValue,19);
    if(!ret)
    {
        printf("Test for Get value successful, key: %d Value: %s\n", key,GetValue(root, key));
    }
    else
    {
        printf("GetValue test failed, ret is %d\n",ret);
    }
}
struct treenode * getMinKeyNode(struct treenode* node) 
{ 
    struct treenode* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
  
/* Given a binary search tree and a key, this function deletes the key 
   and returns the new root */
struct treenode* DeleteEntry(struct treenode* node, int key) 
{ 
    // base case 
    if (node == NULL) return node; 
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (key < node->key) 
        node->left = DeleteEntry(node->left, key); 
  
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (key > node->key) 
        node->right = DeleteEntry(node->right, key); 
  
    // if key is same as root's key, then This is the node 
    // to be deleted 
    else
    { 
        // node with only one child or no child 
        if (node->left == NULL) 
        { 
            struct treenode *temp = node->right;
            free(node->value); 
            free(node); 
            return temp; 
        } 
        else if (node->right == NULL) 
        { 
            struct treenode *temp = node->left; 
            free(node->value); 
            free(node); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        struct treenode* temp = getMinKeyNode(node->right); 
  
        // Copy the inorder successor's content to this node 
        node->key = temp->key; 
  
        // Delete the inorder successor 
        node->right = DeleteEntry(node->right, temp->key); 
    } 
    return node; 
} 

void TestDeleteEntry(int key)
{
    printf("--------[DEL TEST]--------\n");
    struct treenode* root = NULL;
    root = PutEntry(root, key , "Shreya chakraborty");
    root = PutEntry(root, 50 , "abc"); 
    root = PutEntry(root, 30 , "def"); 
    root = PutEntry(root, 20 , "ghi"); 
    root = PutEntry(root, 40 , "jkl"); 
    printf("Database Entries before deletion:\n");
    InorderDisplay(root); 
    root = DeleteEntry(root, key);
    printf("Database Entries After deletion:\n");  
    InorderDisplay(root); 
    printf("Attempt to get deleted entry :\n");
    const char* getValue = GetValue(root, key);
    if(!getValue)
    {
        printf("Confirmed,key/value entry deleted\n");
    }
}

void RangeQuery(struct treenode *root, int k1, int k2) 
{ 
   /* base case */
   if ( NULL == root ) 
      return; 
  
   /* Since the desired o/p is sorted, recurse for left subtree first 
      If root->data is greater than k1, then only we can get o/p keys 
      in left subtree */
   if ( k1 <= root->key ) 
     RangeQuery(root->left, k1, k2); 
  
   /* if root's data lies in range, then prints root's data */
   if ( k1 <= root->key && k2 >= root->key ) 
     printf("Key: %d Value: %s\n", root->key, root->value); 
  
  /* If root->data is smaller than k2, then only we can get o/p keys 
      in right subtree */
   if ( k2 >= root->key ) 
     RangeQuery(root->right, k1, k2); 
} 

void TestRangeQuery(int key1, int key2)
{
    printf("-------[RANGE TEST]-------\n");
    struct treenode* root = NULL;
    root = PutEntry(root, 0 , "Shreya chakraborty");
    root = PutEntry(root, 50 , "abc"); 
    root = PutEntry(root, 30 , "def"); 
    root = PutEntry(root, 20 , "ghi"); 
    root = PutEntry(root, 40 , "jkl");
    root = PutEntry(root, 70 , "mno"); 
    root = PutEntry(root, 60 , "pqr"); 
    root = PutEntry(root, 80 , "stu");
    root = PutEntry(root, 15 , "abc"); 
    root = PutEntry(root, 35 , "def"); 
    root = PutEntry(root, 25 , "ghi"); 
    root = PutEntry(root, 45 , "jkl"); 
    root = PutEntry(root, 75 , "mno"); 
    root = PutEntry(root, 65 , "pqr"); 
    root = PutEntry(root, 85 , "stu");
    printf("Complete Database Entries:\n");
    InorderDisplay(root); 
    printf("Database entries in range %d to %d are as follows:\n", key1, key2);
    RangeQuery(root, key1, key2);   
}

bool KeySearch(struct treenode* root, int key) 
{ 
    // Traverse untill root reaches to dead end 
    while (root != NULL) {
        // pass right subtree as new tree 
        if (key > root->key)
        {
            root = root->right; 
        }
        // pass left subtree as new tree 
        else if (key < root->key) 
        {
            root = root->left; 
        }
        else
            return true; // if the key is found return 1 
    } 
    return false; 
}

