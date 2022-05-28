#ifndef LAB4A_VIEW_H
#define LAB4A_VIEW_H

#include "../model/RBTree.h"

typedef struct Trunk{
    struct Trunk* prev;
    char* str;
} Trunk;

void printMenu();
void printTree(RBTreeNode*, Trunk*, int, const RBTreeNode*);
void printVector(Vector*);
void printList(unsigned int, IntListNode*);
void treeToPNG(RBTree*, const char*);

#endif //LAB4A_VIEW_H
