#ifndef LAB4A_RBTREE_H
#define LAB4A_RBTREE_H

typedef enum Color{
    BLACK, RED
} Color;

typedef struct IntListNode{
    unsigned int data;
    struct IntListNode* next;
} IntListNode;

typedef struct RBTreeNode{
    Color color;
    unsigned int key;
    IntListNode* head;
    struct RBTreeNode *parent, *left, *right;
} RBTreeNode;

typedef struct RBTree{
    RBTreeNode* EList;
    RBTreeNode* root;
} RBTree;

typedef struct Vector{
    int size;
    RBTreeNode** nodes;
} Vector;


int addNewElement(RBTree*, unsigned int, unsigned int);
int deleteElement(RBTree*, unsigned int);
RBTreeNode* findByKey(RBTree*, unsigned int);
Vector* dfs(RBTreeNode*, int, Vector*, RBTreeNode*);
RBTreeNode* findMax(RBTree*);
void freeTree(RBTree*);
RBTree* createTree();

void freeList(IntListNode*);
IntListNode* copyList(IntListNode*);


#endif
