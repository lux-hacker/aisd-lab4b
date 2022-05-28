#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "controller/controller.h"

RBTree *generateTree(int);
void timingAddElement();
void timingDeleteElement();
void timingFindElement();

int main() {
    srand(time(NULL));
    printf("======[TIMING]======\n");
    printf("0)Exit\n");
    printf("1)Add element\n");
    printf("2)Delete element\n");
    printf("3)Find element\n");
    printf("--> ");
    int n = getUInt();
    switch (n) {
        case 1: {
            timingAddElement();
            break;
        }
        case 2: {
            timingDeleteElement();
            break;
        }
        case 3: {
            timingFindElement();
            break;
        }
        default: {
            break;
        }
    }
    return 0;
}

RBTree *generateTree(int size) {
    RBTree *tree = createTree();
    for (int i = 0; i < size; i++) {
        unsigned int key = rand();
        unsigned int data = key;
        addNewElement(tree, key, data);
    }
    return tree;
}

void timingAddElement() {
    FILE *fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for (int size = 1000; size <= 110000; size += 1000) {
        double sum = 0;
        for (int k = 0; k < 10; k++) {
            RBTree *tree = generateTree(size);
            unsigned int keys[100] = {0};
            for (int i = 0; i < 100; i++) {
                keys[i] = rand();
            }
            clock_t start = clock();
            for (int i = 0; i < 100; i++) {
                addNewElement(tree, keys[i], keys[i]);
            }
            clock_t end = clock();
            sum += (double) (end - start) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
        }
        fprintf(fd, "%d,%f,%s\n", size, sum / 10, "addElement");
    }
    fclose(fd);
}

void timingDeleteElement(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for (int size = 1000; size <= 110000; size += 1000) {
        double sum = 0;
        for (int k = 0; k < 10; k++) {
            RBTree *tree = generateTree(size);
            unsigned int keys[100] = {0};
            for (int i = 0; i < 100; i++) {
                keys[i] = rand();
            }
            clock_t start = clock();
            for (int i = 0; i < 100; i++) {
                deleteElement(tree, keys[i]);
            }
            clock_t end = clock();
            sum += (double) (end - start) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
        }
        fprintf(fd, "%d,%f,%s\n", size, sum / 10, "deleteElement");
    }
    fclose(fd);
}

void timingFindElement(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for (int size = 1000; size <= 110000; size += 1000) {
        double sum = 0;
        for (int k = 0; k < 10; k++) {
            RBTree *tree = generateTree(size);
            unsigned int keys[100] = {0};
            for (int i = 0; i < 100; i++) {
                keys[i] = rand();
            }
            clock_t start = clock();
            for (int i = 0; i < 100; i++) {
                findByKey(tree, keys[i]);
            }
            clock_t end = clock();
            sum += (double) (end - start) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
        }
        fprintf(fd, "%d,%f,%s\n", size, sum / 10, "findElement");
    }
    fclose(fd);
}
