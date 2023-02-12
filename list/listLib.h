#include <stdio.h>
#include <stdlib.h>
typedef struct List{
    int val;
    struct List *next;
}List;


void pushBack(List *root, int val);

void deleteList(List **root);

List *getLast(List *root);

void deleteList2(List *root);

void sortList(List *root , int size);

int sizeList(List *root);

void displeyList(List *root);

void toCore(int **core, List *root, int size);

int getVal(List *root, int i);