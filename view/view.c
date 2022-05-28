#include "view.h"
#include <stdio.h>
#include <stdlib.h>

void showTrunks(Trunk*);
void _treeToPNG(RBTreeNode*, FILE*, const RBTreeNode*);

void printMenu(){
    printf("======[WELCOME TO THE MENU]======\n");
    printf("0)Exit program\n");
    printf("1)Add new element\n");
    printf("2)Delete element\n");
    printf("3)Search in tree\n");
    printf("4)Find element\n");
    printf("5)Find max element\n");
    printf("6)Print tree\n");
    printf("7)Import tree from file\n");
    printf("--> ");
}

void showTrunks(Trunk *p) {
    if (p == NULL) {
        return;
    }
    showTrunks(p->prev);
    printf("%s", p->str);
}

void printTree(RBTreeNode* root, Trunk* prev, int isLeft, const RBTreeNode* EList){
    if(root == EList) return;
    char* prev_str = "     ";
    Trunk trunk = {prev, prev_str};
    printTree(root->right, &trunk, 1, EList);
    if(!prev){
        trunk.str = "----";
    } else if(isLeft){
        trunk.str = ".----";
        prev_str = "    |";
    } else {
        trunk.str = "`----";
        prev->str = prev_str;
    }

    showTrunks(&trunk);
    printf(" (%d,%d)\n", root->key, root->head->data);
    if(prev){
        prev->str = prev_str;
    }
    trunk.str = "    |";
    printTree(root->left, &trunk, 0, EList);
}

void printVector(Vector* vector){
    for(int i = 0; i < vector->size; i++){
        printList(vector->nodes[i]->key, vector->nodes[i]->head);
    }
    printf("\n");
}

void printList(unsigned int key, IntListNode* _head){
    printf("%d: ", key);
    IntListNode* head = _head;
    while(head->next != NULL){
        printf("%d, ", head->data);
        head = head->next;
    }
    printf("%d\n", head->data);
}

void treeToPNG(RBTree* tree, const char* fn){
    FILE* fd = fopen("buf.dot", "w");
    fprintf(fd, "digraph G{\n");
    RBTreeNode* pnt = tree->root;
    if(pnt == NULL){
        fprintf(fd, "\n");
    } else if(pnt->left == tree->EList && pnt->right == tree->EList){
        fprintf(fd, "   u_%d_%d;\n",pnt->key, 1);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\", color=%s];\n", pnt->key, 1, pnt->key, pnt->head->data, pnt->color == RED ? "red": "black");
    } else {
        _treeToPNG(pnt, fd, tree->EList);
    }
    fprintf(fd, "}");
    fclose(fd);
    char cmd[255] = {0};
    sprintf(cmd, "dot -Tpng buf.dot -o %s", fn);
    system(cmd);
    remove("buf.dot");
}

void _treeToPNG(RBTreeNode* root, FILE* fd, const RBTreeNode* EList){
    static int nil = 0;
    if(root->left != EList) {
        fprintf(fd, "   u_%d_%d -> u_%d_%d;\n", root->key, 1, root->left->key, 1);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\", color=%s];\n", root->key, 1, root->key, root->head->data, root->color == RED ? "red": "black");
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\", color=%s];\n", root->left->key, 1, root->left->key, root->left->head->data, root->left->color == RED ? "red": "black");
        _treeToPNG(root->left, fd, EList);
    } else {
        fprintf(fd, "   null%d [shape=point];\n", nil);
        fprintf(fd, "   u_%d_%d -> null%d;\n",root->key, 1, nil);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\", color=%s];\n", root->key, 1, root->key, root->head->data, root->color == RED ? "red": "black");
        nil++;
    }
    if(root->right != EList){
        fprintf(fd, "   u_%d_%d -> u_%d_%d;\n", root->key, 1, root->right->key, 1);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\", color=%s];\n", root->key, 1, root->key, root->head->data, root->color == RED ? "red": "black");
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\", color=%s];\n", root->right->key, 1, root->right->key, root->right->head->data, root->right->color == RED ? "red": "black");
        _treeToPNG(root->right, fd, EList);
    } else {
        fprintf(fd, "   null%d [shape=point];\n", nil);
        fprintf(fd, "   u_%d_%d -> null%d;\n",root->key, 1, nil);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\", color=%s];\n", root->key, 1, root->key, root->head->data, root->color == RED ? "red": "black");
        nil++;
    }
}
