#include "RBTree.h"
#include <stdlib.h>
#include <stdio.h>

void left_rotate(RBTreeNode*, RBTree*);
void right_rotate(RBTreeNode*, RBTree*);

void add_fixup(RBTreeNode*, RBTree*);
void delete_fixup(RBTreeNode*, RBTree*);

RBTreeNode* min_element(RBTreeNode*, RBTree*);
RBTreeNode* next_element(RBTreeNode*, RBTree*);

void left_rotate(RBTreeNode* x, RBTree* tree){
    RBTreeNode* y = x->right;
    RBTreeNode* p = x->parent;

    x->right = y->left;
    if(y->left != tree->EList) y->left->parent = x;

    y->parent = p;
    if(p == tree->EList){
        tree->root = y;
    } else {
        if(x == p->left) p->left = y;
        else p->right = y;
    }

    y->left = x;
    x->parent = y;
}

void right_rotate(RBTreeNode* x, RBTree* tree){
    RBTreeNode* y = x->left;
    RBTreeNode* p = x->parent;

    x->left = y->right;
    if(y->right != tree->EList) y->right->parent = x;

    y->parent = p;
    if(p == tree->EList){
        tree->root = y;
    } else {
        if(x == p->left) p->left = y;
        else p->right = y;
    }

    y->right = x;
    x->parent = y;
}

void add_fixup(RBTreeNode* x, RBTree* tree){
    if(x == tree->root && x->color == RED){
        x->color = BLACK;
        return;
    }

    if(x == tree->root) return;

    RBTreeNode* p1 = x->parent;

    if(p1->color == BLACK) return;

    RBTreeNode* pp = p1->parent;
    RBTreeNode* p2;
    if(p1 == pp->right) {
        p2 = pp->left;
        if(p2->color == RED){
            pp->color = RED;
            p2->color = BLACK;
            p1->color = BLACK;
            add_fixup(pp, tree);
        } else {
            if(x == p1->left){
                right_rotate(p1, tree);
                x = p1;
                p1 = x->parent;
                pp = p1->parent;
            }
            pp->color = RED;
            p1->color = BLACK;
            left_rotate(pp, tree);
        }
    }
    else {
        p2 = pp->right;
        if(p2->color == RED){
            pp->color = RED;
            p2->color = BLACK;
            p1->color = BLACK;
            add_fixup(pp, tree);
        } else {
            if(x == p1->right){
                left_rotate(p1, tree);
                x = p1;
                p1 = x->parent;
                pp = p1->parent;
            }
            pp->color = RED;
            p1->color = BLACK;
            right_rotate(pp, tree);
        }
    }
    tree->root->color = BLACK;
}

int addNewElement(RBTree* tree, unsigned int key, unsigned int data){
    RBTreeNode* ptr = tree->root;
    RBTreeNode* par = tree->EList;

    while(ptr != tree->EList){
        par = ptr;
        if(key < ptr->key) ptr = ptr->left;
        else if(key > ptr->key) ptr = ptr->right;
        else {
            IntListNode* t = ptr->head;
            while(t->next != NULL) t = t->next;
            t->next = (IntListNode*) malloc(sizeof(IntListNode));
            t = t->next;
            t->next = NULL;
            t->data = data;
            return 0;
        }
    }
    if(par == tree->EList){
        tree->root = (RBTreeNode*) malloc(sizeof(RBTreeNode));
        ptr = tree->root;
    } else {
        ptr = (RBTreeNode*) malloc(sizeof(RBTreeNode));
    }
    ptr->parent = par;
    if(par != tree->EList){
        if(key < par->key) par->left = ptr;
        else par->right = ptr;
    }
    ptr->left = tree->EList;
    ptr->right = tree->EList;
    ptr->color = RED;
    ptr->key = key;
    ptr->head = (IntListNode*) malloc(sizeof(IntListNode));
    ptr->head->data = data;
    ptr->head->next = NULL;

    add_fixup(ptr, tree);

    return 0;
}

void freeList(IntListNode* head){
    while(head != NULL){
        IntListNode* t = head;
        head = head->next;
        free(t);
    }
}

void freeTree(RBTree* tree){
    if(tree->root == tree->EList) return;

    RBTree left = {tree->EList, tree->root->left};
    freeTree(&left);
    RBTree right = {tree->EList, tree->root->right};
    freeTree(&right);

    freeList(tree->root->head);
    if(tree->root->parent == tree->EList){
        free(tree->EList);
    } else {
        if(tree->root == tree->root->parent->left) tree->root->parent->left = tree->EList;
        else tree->root->parent->right = tree->EList;
    }
    free(tree->root);
    tree->root = NULL;
}

void delete_fixup(RBTreeNode* x, RBTree* tree){
    if(x == tree->root && x->color == RED){
        x->color = BLACK;
        return;
    }
    if(x == tree->root) return;
    printf("Node %d\n", x->parent->key);
    RBTreeNode* p = x->parent;
    if(x == p->left){
        RBTreeNode* w = p->right;
        if(w->color == RED){
            p->color = BLACK;
            w->color = RED;
            left_rotate(p, tree);
        }
        if(w->left->color == BLACK && w->right->color == BLACK){
            if(p->color == BLACK) {
                w->color = RED;
                x = p;
                delete_fixup(x, tree);
            } else {
                p->color = BLACK;
                w->color = RED;
            }
        } else {
            if(w->right->color == BLACK){
                w->color = RED;
                w->left->color = BLACK;
                right_rotate(w, tree);
                w = p->right;
            }
            w->color = p->color;
            p->color = BLACK;
            w->right->color = BLACK;
            left_rotate(p, tree);
            x = tree->root;
            delete_fixup(x, tree);
        }
    } else {
        RBTreeNode* w = p->left;
        if(w->color == RED){
            p->color = BLACK;
            w->color = RED;
            right_rotate(p, tree);
        }
        if(w->left->color == BLACK && w->right->color == BLACK){
            if(p->color == BLACK) {
                w->color = RED;
                x = p;
                delete_fixup(x, tree);
            } else {
                p->color = BLACK;
                w->color = RED;
            }
        } else {
            if(w->left->color == BLACK){
                w->color = RED;
                w->right->color = BLACK;
                left_rotate(w, tree);
                w = p->left;
            }
            w->color = p->color;
            p->color = BLACK;
            w->left->color = BLACK;
            right_rotate(p, tree);
            x = tree->root;
            delete_fixup(x, tree);
        }
    }
    tree->root->color = BLACK;
}

RBTreeNode* min_element(RBTreeNode* root, RBTree* tree){
    while(root->left != tree->EList){
        root = root->left;
    }
    return root;
}

RBTreeNode* next_element(RBTreeNode* x, RBTree* tree){
    if(x->right != tree->EList){
        return min_element(x->right, tree);
    } else {
        RBTreeNode* ptr = x;
        RBTreeNode* par = ptr->parent;
        while(par != tree->EList && par->right == ptr){
            ptr = par;
            par = ptr->parent;
        }
        return ptr;
    }
}

int deleteElement(RBTree* tree, unsigned int key){
    RBTreeNode* x = findByKey(tree, key);

    if(x == tree->EList) return 1;
    if(x->head->next != NULL){
        IntListNode* t = x->head;
        x->head = x->head->next;
        free(t);
        return 0;
    }
    if(x->left == tree->EList & x->right == tree->EList){
        if(x != tree->root) {
            if (x->color == BLACK) {
                delete_fixup(x, tree);
            }
            RBTreeNode *p = x->parent;
            if (x == p->left) {
                p->left = tree->EList;
            } else {
                p->right = tree->EList;
            }
        } else {
            tree->root = tree->EList;
        }
        freeList(x->head);
        free(x);
    } else if(x->left == tree->EList) {
        if(x != tree->root) {
            RBTreeNode *p = x->parent;
            if (x == p->left) {
                p->left = x->right;
            } else {
                p->right = x->right;
            }
            x->right->color = BLACK;
            x->right->parent = p;
        } else {
            tree->root = x->right;
            tree->root->parent = tree->EList;
            tree->root->color = BLACK;
        }
        freeList(x->head);
        free(x);
    } else if(x->right == tree->EList) {
        if(x != tree->root) {
            RBTreeNode *p = x->parent;
            if (x == p->left) {
                p->left = x->left;
            } else {
                p->right = x->left;
            }
            x->left->color = BLACK;
            x->left->parent = p;
        } else {
            tree->root = x->left;
            tree->root->parent = tree->EList;
            tree->root->color = BLACK;
        }
        freeList(x->head);
        free(x);
    } else {
        RBTreeNode* y = next_element(x, tree);
        unsigned int _key = y->key;
        IntListNode* head = copyList(y->head);
        deleteElement(tree, y->key);
        freeList(x->head);
        x->head = head;
        x->key = _key;
    }
    return 0;
}

RBTreeNode* findByKey(RBTree* tree, unsigned int key){
    RBTreeNode* x = tree->root;
    while(x != tree->EList && x->key != key){
        if(key < x->key) x = x->left;
        else x = x->right;
    }
    return x;
}

IntListNode* copyList(IntListNode* head){
    IntListNode* new_head = (IntListNode*) malloc(sizeof(IntListNode));
    new_head->data = head->data;
    new_head->next = NULL;
    head = head->next;
    while(head != NULL){
        new_head->next = (IntListNode*) malloc(sizeof(IntListNode));
        new_head = new_head->next;
        new_head->data = head->data;
        new_head->next = NULL;
        head = head->next;
    }
    return new_head;
}

RBTree* createTree(){
    RBTree* tree = (RBTree*) malloc(sizeof(RBTree));
    tree->EList = (RBTreeNode*) malloc(sizeof(RBTreeNode));
    tree->EList->color = BLACK;
    tree->EList->head = NULL;
    tree->EList->right = NULL;
    tree->EList->left = NULL;
    tree->EList->parent = NULL;
    tree->EList->key = 0;
    tree->root = tree->EList;
    return tree;
}

RBTreeNode* findMax(RBTree* tree){
    RBTreeNode* root = tree->root;
    while(root->right != tree->EList) root = root->right;
    return root;
}

Vector* dfs(RBTreeNode* root, int upper, Vector* vector, RBTreeNode* EList){
    Vector* answer = vector;
    RBTreeNode* ptr = root;
    if(ptr == EList) return answer;
    answer = dfs(root->right, upper, answer, EList);
    if(ptr->key > upper || upper == -1){
        if(answer == NULL) {
            answer = (Vector *) malloc(sizeof(Vector));
            answer->nodes = (RBTreeNode**) calloc(1 , sizeof(RBTreeNode*));
            answer->size = 0;
        }
        answer->size++;
        answer->nodes = (RBTreeNode **) realloc(answer->nodes, answer->size * sizeof(RBTreeNode*));
        answer->nodes[answer->size - 1] = ptr;
    }
    answer = dfs(root->left, upper, answer, EList);
    return answer;
}
