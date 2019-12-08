#include "fg_tree.h"
#include "lock.h"

LOCK_T root_lock;

bool FG_searchTree(struct fg_treenode *root, int key)
{
    if(root == NULL)
    {
        return false;
    }
    
    LOCK_RDLOCK(root->node_lock); 

    while(root)
    {
        if(key == root->key)
        {
            LOCK_UNLOCK(root->node_lock); 
            return true;
        }
        else if(key > root->key)
        {
            if(root->right)
            {
                LOCK_RDLOCK(root->right->node_lock);
                LOCK_UNLOCK(root->node_lock);
                root = root->right;
            } 
            else 
            {
                LOCK_UNLOCK(root->node_lock);
                return false;
            }
        }
        else
        {
            if(root->left) 
            {
                LOCK_RDLOCK(root->left->node_lock);  
                LOCK_UNLOCK(root->node_lock);
                root = root->left;
            }
            else 
            {
                LOCK_UNLOCK(root->node_lock);
                return false;
            }
        }
    }
    LOCK_UNLOCK(root->node_lock);
    return false;
}

struct fg_treenode* FG_newNode(int key , const char* value)
{ 
	struct fg_treenode* node = (struct fg_treenode*) 
						malloc(sizeof(struct fg_treenode)); 
	node->key = key; 
    node->value = (char *)malloc(strlen(value) + 1);
    strcpy(node->value, value);
	node->left = NULL; 
	node->right = NULL; 
    LOCK_INIT(node->node_lock);
    
	return(node); 
} 

struct fg_treenode* FG_Insert(struct fg_treenode *root, int key, char *value)
{
    struct fg_treenode *newNode = FG_newNode(key, value);
    
    LOCK_WRLOCK(root_lock);
    if(root == NULL)
    {
        return newNode;
    }
    LOCK_UNLOCK(root_lock);

    struct fg_treenode *current = root;    

    LOCK_WRLOCK(current->node_lock);

    while(current)
    {
        if(current->key == key)
        {
            //free(current->value);
            //copy value here;
            break;
        }
        else if(key > current->key)
        {
            if(current->right)
            {
                LOCK_WRLOCK(current->right->node_lock);
                LOCK_UNLOCK(current->node_lock);
                current = current->right;
            }
            else
            {
                current->right = newNode;
                LOCK_UNLOCK(current->node_lock);
                break;
            }
        }
        else
        {
            if(current->left)
            {
                LOCK_WRLOCK(current->left->node_lock);
                LOCK_UNLOCK(current->node_lock);
                current = current->left;
            }
            else
            {
                current->left = newNode;
                LOCK_UNLOCK(current->node_lock);
                break;
            }
        }
    }
    return root;
}

char * FG_GetValue(struct fg_treenode *root, int key)
{
    if(root)
    {
        LOCK_RDLOCK(root->node_lock); 
    }

    while(root)
    {
        if(key == root->key)
        {
            LOCK_UNLOCK(root->node_lock); 
            return root->value;
        }
        else if(key > root->key)
        {
            if(root->right)
            {
                LOCK_RDLOCK(root->right->node_lock); 
                LOCK_UNLOCK(root->node_lock);
            } 
            else 
            {
                LOCK_UNLOCK(root->node_lock);
                return NULL;
            }
            root = root->right;
        }
        else
        {
            if(root->left) 
            {
                LOCK_RDLOCK(root->left->node_lock);  
                LOCK_UNLOCK(root->node_lock);
            }
            else 
            {
                LOCK_UNLOCK(root->node_lock);
                return NULL;
            }
            root = root->left;
        }
    }
    LOCK_UNLOCK(root->node_lock);
    return NULL;
}

void FG_RangeQuery(struct fg_treenode* root,  int key1, int key2) 
{ 
    printf("The Key/Value pairs between %d and %d are:\n",key1,key2);
    if (!root) 
        return; 
  
    struct fg_treenode* curr = root; 
  
    //LOCK_RDLOCK(root->node_lock); 

    while (curr) { 
  
        if (curr->left == NULL)  
        { 
            // check if current node  
            // lies between n1 and n2 
            if (curr->key <= key2 &&  
                curr->key >= key1)  
            { 
                printf("Key: %d    Value: %s\n",curr->key,curr->value); 
            } 
  
            curr = curr->right; 

        } 
  
        else { 
            struct fg_treenode* pre = curr->left; 
            // finding the inorder predecessor- 
            // inorder predecessor is the right 
            // most in left subtree or the left  
            // child, i.e in BST it is the  
            // maximum(right most) in left subtree. 
            while (pre->right != NULL &&  
                   pre->right != curr) 
                        pre = pre->right; 
  
            if (pre->right == NULL)  
            { 
                pre->right = curr; 
                curr = curr->left; 
            } 
  
            else { 
                pre->right = NULL; 
  
                // check if current node lies  
                // between n1 and n2 
                if (curr->key <= key2 &&  
                    curr->key >= key1)  
                { 
                    printf("Key: %d    Value: %s\n",curr->key,curr->value);
                } 
  
                curr = curr->right; 
            } 
        } 
    } 
} 
/*
struct fg_treenode* FG_Insert(struct fg_treenode *root, int key, char* value)
{
    struct fg_treenode * newnode = FG_newNode(key,value);
    if(root == NULL)/// tree empty
    {
        root = newnode;
        return root;
    }
    struct fg_treenode *curr = root;
    struct fg_treenode *prev = NULL;

    while(curr)
    {
        prev = curr;
        if(curr->key == key)
        {
            memcpy(curr->value,value,strlen(value)+1);
        }
        if(curr->key > key)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;           
        }
        
    }
    if(key < prev->key)
    {
        prev->left = newnode;
    }
    else{
        prev->right = newnode;
    }
    return prev;
}*/

void FG_InorderDisplay(struct fg_treenode *root) 
{ 
    if (root != NULL) 
    { 
        FG_InorderDisplay(root->left); 
        printf("Key: %d ", root->key);
        printf("Value: %s\n", root->value); 
        FG_InorderDisplay(root->right); 
    } 
} 

// void FG_Range(struct fg_treenode *root, int key1, int key2) 
// { 
//     if (root != NULL) 
//     { 
//         FG_InorderDisplay(root->left); 
//         printf("Key: %d ", root->key);
//         printf("Value: %s\n", root->value); 
//         FG_InorderDisplay(root->right); 
//     } 
// } 

// void inOrder(struct fg_treenode *root) 
// { 
//     stack<fg_treenode *> s; 
//     struct fg_treenode *curr = root; 
  
//     while (curr != NULL || s.empty() == false) 
//     { 
//         /* Reach the left most Node of the 
//            curr Node */
//         while (curr !=  NULL) 
//         { 
//             /* place pointer to a tree node on 
//                the stack before traversing 
//               the node's left subtree */
//             s.push(curr); 
//             curr = curr->left; 
//         } 
  
//         /* Current must be NULL at this point */
//         curr = s.top(); 
//         s.pop(); 
  
//         cout << curr->data << " "; 
  
//         /* we have visited the node and its 
//            left subtree.  Now, it's right 
//            subtree's turn */
//         curr = curr->right; 
  
//     } /* end of while */
// }
  
  