#include <readline/readline.h>
#include <stdlib.h>
#include "controller/controller.h"

void printResult(BinTreeNode*, FILE*);

int main(){
    printf("======[COUNTER]======\n");
    printf("Enter input filename\n--> ");
    char* fn = readline("");
    printf("Enter output filename\n--> ");
    char* ofn = readline("");
    FILE* fd;
    if((fd = fopen(fn, "r+b")) == NULL){
        printf("======[ERROR]======\n");
        printf("File doesn't exist\n");
        return 0;
    }
    free(fn);
    long t1 = ftell(fd);
    fseek(fd, 0L, SEEK_END);
    long t2 = ftell(fd);
    if(t1 == t2){
        printf("======[ERROR]======\n");
        printf("File is empty\n");
        fclose(fd);
        return 0;
    }
    fseek(fd, 0L, SEEK_SET);
    BinTree* tree = (BinTree*) malloc(sizeof(BinTree));
    tree->root = NULL;
    while(!feof(fd)) {
        unsigned int n;
        int k = fread(&n, sizeof(unsigned int), 1, fd);
        if(k != 1){
            break;
        }
        BinTreeNode *ptr = findByKey(tree, n, 1);
        if (ptr == NULL) {
            addNewElement(tree, 1, n);
        } else {
            ptr->data++;
        }
    }
    fclose(fd);
    printTree(tree->root, NULL, 0);
    FILE* file = fopen(ofn, "w");
    printResult(tree->root, file);
    fclose(file);
    free(ofn);
    freeTree(tree);
    free(tree);
}

void printResult(BinTreeNode* root, FILE* fd){
    if(root == NULL) return;
    printResult(root->left, fd);
    fprintf(fd, "%d - %d\n", root->key, root->data);
    printResult(root->right, fd);
}
