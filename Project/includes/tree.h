
#ifndef TREE_H_
#define TREE_H_

/* Function to print level order traversal a tree*/
void DisplayTree(struct treenode* root);


/* Print nodes at a given level */
void DisplayLevel(struct treenode* root, int level); 


/* Compute the "height" of a tree -- the number of 
	nodes along the longest path from the root node 
	down to the farthest leaf node.*/
int getTreeHeight(struct treenode* node);


/* Helper function that allocates a new node with the 
given data and NULL left and right pointers. */
struct treenode* newNode(int key , const char* value);

/* Driver program to test above functions*/
int TestNodeCreation(void);
void InorderDisplay(struct treenode *root);
/*insert key/value in tree*/
struct treenode* PutEntry(struct treenode* node, int key, const char* value);
void TestPutEntry(void);
const char* GetValue(struct treenode* node, int key);
void TestGetValue(int key);
struct treenode* DeleteEntry(struct treenode* node, int key);
void TestDeleteEntry(int key);
void RangeQuery(struct treenode *root, int k1, int k2);
void TestRangeQuery(int key1, int key2); 
bool KeySearch(struct treenode* root, int key);

#endif
