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

/*struct fg_treenode* FG_newNode(int key , int value)
{ 
	struct fg_treenode* node = (struct fg_treenode*) 
						malloc(sizeof(struct fg_treenode));
    if(node == NULL)
    {
        exit(EXIT_FAILURE);
    }
	node->key = key; 
    node->value = value;
	node->left = NULL; 
	node->right = NULL; 
    LOCK_INIT(node->node_lock);
	return(node); 
}*/

struct fg_treenode* FG_newNode(int key , char *value)
{ 
	struct fg_treenode* node = (struct fg_treenode*) 
						malloc(sizeof(struct fg_treenode));
    if(node == NULL)
    {
        exit(EXIT_FAILURE);
    }
	node->key = key; 
    //node->value = (char*)malloc(sizeof(value));
    memcpy(node->value,value,sizeof(node->value));
    //strcpy(node->value,value);
	node->left = NULL; 
	node->right = NULL; 
    LOCK_INIT(node->node_lock);
	return(node); 
} 
struct fg_treenode* FG_Insert_char(struct fg_treenode **root, int key, char* value)
{    
    if(root == NULL)
    {
        return NULL;
    }
    LOCK_WRLOCK(root_lock);
    if(*root == NULL)
    {
        *root = FG_newNode(key, value);
        LOCK_UNLOCK(root_lock);
        return *root;
    }

    LOCK_WRLOCK((*root)->node_lock);
    struct fg_treenode *current = *root;
    LOCK_UNLOCK(root_lock);

    while(current)
    {
        if(current->key == key)
        {
            memset((current->value),0, sizeof(current->value));
            //copy value here;
            memcpy(current->value,value,sizeof(current->value));
            LOCK_UNLOCK(current->node_lock);
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
                current->right = FG_newNode(key, value);
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
                current->left = FG_newNode(key, value);
                LOCK_UNLOCK(current->node_lock);
                break;
            }
        }
    }
    return *root;
}
/*struct fg_treenode* FG_Insert(struct fg_treenode **root, int key, int value)
{    
    if(root == NULL)
    {
        return NULL;
    }
    LOCK_WRLOCK(root_lock);
    if(*root == NULL)
    {
        *root = FG_newNode(key, value);
        LOCK_UNLOCK(root_lock);
        return *root;
    }

    LOCK_WRLOCK((*root)->node_lock);
    struct fg_treenode *current = *root;
    LOCK_UNLOCK(root_lock);

    while(current)
    {
        if(current->key == key)
        {
            //free(current->value);
            //copy value here;
            current->value = value;
            LOCK_UNLOCK(current->node_lock);
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
                current->right = FG_newNode(key, value);
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
                current->left = FG_newNode(key, value);
                LOCK_UNLOCK(current->node_lock);
                break;
            }
        }
    }
    return *root;
}*/

/*int FG_GetValue(struct fg_treenode *root, int key)
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
                return -1;
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
                return -1;
            }
            root = root->left;
        }
    }
    LOCK_UNLOCK(root->node_lock);
    return -1;
}*/
char* FG_GetValue_char(struct fg_treenode *root, int key)
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

void FG_Range(struct fg_treenode *root, int key_low, int key_high , int threadno, int logging)
{
    _FG_Range(root, NULL, key_low, key_high,threadno,logging);
}

void _FG_Range(struct fg_treenode *root, struct fg_treenode *parent, int key_low, int key_high,int threadno, int logging)
{
    if(parent == NULL)
    {
        LOCK_RDLOCK(root_lock);
        if (root == NULL)
        {
            LOCK_UNLOCK(root_lock);
            return;
        }
        LOCK_RDLOCK(root->node_lock);
        LOCK_UNLOCK(root_lock);
    }

    if (key_low < root->key)
    {
        if(root->left)
        {
            LOCK_RDLOCK(root->left->node_lock);
            LOCK_UNLOCK(root->node_lock);
            _FG_Range(root->left, root, key_low, key_high,threadno,logging);
            LOCK_RDLOCK(root->node_lock);
        }
        
    }

    if (root->key >= key_low && root->key <= key_high)
    {
        //std::cout << "Key: " << root->key << std::endl;
        if(logging)
        {
            printf("RANGE------>Thread[%d]\tLow[%d]\tHigh[%d]\tRange [Key: %d\tValue: %s]\n",threadno,key_low,key_high,root->key,root->value);
        }
    }

    if (key_high > root->key)
    {
        if(root->right)
        {
            LOCK_RDLOCK(root->right->node_lock);
            LOCK_UNLOCK(root->node_lock);
            _FG_Range(root->right, root, key_low, key_high,threadno,logging);
            LOCK_RDLOCK(root->node_lock);
        }
    }
    LOCK_UNLOCK(root->node_lock);
}

void FG_InorderDisplay(struct fg_treenode *root) 
{ 
    if (root != NULL) 
    {
        FG_InorderDisplay(root->left); 
        printf("Key: %d ", root->key);
        //printf("Value: %d\n", root->value); 
        printf("Value: %s\n", root->value); 
        FG_InorderDisplay(root->right); 
    } 
}

void FG_Destroy(struct fg_treenode *root) 
{ 
    if(root->left == NULL && root->right == NULL)
    {
        free(root);
        return;
    }
    if(root != NULL)
    { 
        FG_Destroy(root->left);
        FG_Destroy(root->right); 
    } 
}

struct fg_treenode* deleteTree(struct fg_treenode* node)  
{ 
    if (node == NULL) return node; 
  
    /* first delete both subtrees */
    deleteTree(node->left); 
    deleteTree(node->right); 
    
    /* then delete the node */
    //printf("\n Deleting node: %d", node->key); 
    free(node);
    node = NULL;
    return node;
}  

  
  