#include "listLib.h"

List *getLast(List *root)
{
    List *tmpNode;
    tmpNode = root;
    int count = 0;
    while (tmpNode->next)
    {
        tmpNode = tmpNode->next;
        count++;
    }
    //printf("last = %d\n", count);
    return tmpNode;
}

void pushBack(List *root, int val)
{
    List *lastNode = (List *)malloc(sizeof(List));
    lastNode->val = val;
    lastNode->next = NULL;
    List *tmpNode = getLast(root);
    tmpNode->next = lastNode;
}

void deleteList(List **root)
{
    List *prev = NULL;
    int count = 0;
    while ((*root)->next)
    {
        prev = (*root);
        (*root) = (*root)->next;
        printf("delete %d \t count %d\n", prev->val, count);
        free(prev);
        count++;
    }
    count++;
    printf("delete %d \t count %d\n", (*root)->val, count);
    free(*root);
}

void deleteList2(List *root)
{

    List *prev = NULL;
    int count = 0;
    while (root->next)
    {
        prev = root;

        count++;
        root = root->next;
        free(prev);
    }
    count++;
    free(root);
}

int sizeList(List *root)
{
    int sizeList = 0;
    while (root)
    {
        sizeList++;
        root = root->next;
    }
    return sizeList - 1;
}

void displeyList(List *root)
{
    while (root)
    {
        printf("%p \t value = %d\n", root, root->val);
        root = root->next;
    }
}

void sortList(List *root, int size)
{
    int i, j;
    int bufVal = 0;
    List *prevNode = root;
    List *tmpNode = root;
    List *nextNode = tmpNode->next;
    for (i = 0; i < size; i++)
    {
        
        tmpNode = root;
        nextNode = tmpNode->next;
        prevNode = tmpNode;
        while (tmpNode && nextNode)
        {
            

            if (tmpNode->val > nextNode->val)
            {
                

                if (tmpNode == root)
                {
                    bufVal = root->val;
                    root->val = nextNode->val;
                    nextNode->val = bufVal;
                    tmpNode = tmpNode->next;
                    nextNode = nextNode->next;
                }
                else
                {
                    tmpNode->next = nextNode->next;
                    prevNode->next = nextNode;
                    nextNode->next = tmpNode;
                    
                    nextNode = tmpNode->next;
                    prevNode = prevNode->next;
                }
            }
            else
            {
                
                if (tmpNode == root)
                {
                }
                else
                {
                    prevNode = tmpNode;
                }
                tmpNode = tmpNode->next;
                nextNode = nextNode->next;
            }
        }
    }
}

int pop(List **root)
{
    List *prev = NULL;
    int val;
    if (root == NULL)
    {
        printf("root == null pop\n");
        exit(-5);
    }
    prev = (*root);
    val = prev->val;
    (*root) = (*root)->next;
    free(prev);
    return val;
}

void toCore(int **core, List *root, int size)
{
    root = root->next;
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            core[i][j] = root->val;
            root = root->next;
        }
    }
}

int getVal(List *root, int i)
{
    for(int j = 0;j<i;j++)
    {
        root = root->next;
    }
    return root->val;
}