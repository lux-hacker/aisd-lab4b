#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>


unsigned int getUInt(){
    char *msg = "";
    while (1) {
        printf("%s", msg);
        char *input = readline("");
        msg = "======[MUST BE NUMBER]======\n--> ";
        char *ptr;
        int value = (int) strtol(input, &ptr, 10);
        if (strlen(input) != 0 && ptr == input + strlen(input)) {
            free(input);
            if(value < 0){
                msg = "======[NEGATIVE NUMBER ISN'T ALLOWED]======\n--> ";
                continue;
            }
            return value;
        }
        free(input);
    }
}

int getInt(){
    char *msg = "";
    while (1) {
        printf("%s", msg);
        char *input = readline("");
        msg = "======[MUST BE NUMBER]======\n--> ";
        char *ptr;
        int value = (int) strtol(input, &ptr, 10);
        if (strlen(input) != 0 && ptr == input + strlen(input)) {
            free(input);
            return value;
        }
        free(input);
    }
}

void menu(){
    printf("======[Tree to PNG]======\n");
    printf("Enter filename of future picture\n--> ");
    char* pict_name = readline("");
    RBTree* tree = createTree();
    while(1){
        printMenu();
        unsigned int n = getUInt();
        switch (n) {
            case 0:{
                if(tree->root != tree->EList)freeTree(tree);
                else free(tree->EList);
                free(tree);
                free(pict_name);
                return;
            }
            case 1:{
                printf("======[ADD ELEMENT]======\n");
                printf("Enter key\n--> ");
                unsigned int key = getUInt();
                printf("Enter data\n--> ");
                unsigned int data = getUInt();
                addNewElement(tree, key, data);
                treeToPNG(tree, pict_name);
                break;
            }
            case 2:{
                printf("======[DELETE ELEMENT]======\n");
                printf("Enter key\n--> ");
                unsigned int key = getUInt();
                int err = deleteElement(tree, key);
                if(err == 1){
                    printf("======[ERROR]======\n");
                    printf("Element with this key doesn't exist\n");
                }
                treeToPNG(tree, pict_name);
                break;
            }
            case 3:{
                printf("======[SEARCH IN TREE]======\n");
                printf("Enter key upper or -1\n--> ");
                int upper = getInt();
                Vector * answer = dfs(tree->root, upper, NULL, tree->EList);
                if(answer == NULL){
                    printf("======[ERROR]======\n");
                    printf("Keys upper this don't exist\n");
                } else {
                    printVector(answer);
                    free(answer->nodes);
                    free(answer);
                }
                break;
            }
            case 4:{
                printf("======[FIND ELEMENT]======\n");
                printf("Enter key\n--> ");
                unsigned int key = getUInt();
                RBTreeNode* ptr = findByKey(tree, key);
                if(ptr == tree->EList){
                    printf("======[ERROR]======\n");
                    printf("Key don't exist\n");
                } else {
                    printList(ptr->key, ptr->head);
                }
                break;
            }
            case 5:{
                printf("======[FIND MAX ELEMENT]======\n");
                RBTreeNode* ptr = findMax(tree);
                printList(ptr->key, ptr->head);
                break;
            }
            case 6:{
                printf("======[OUTPUT TREE]======\n");
                if(tree->root == tree->EList){
                    printf("======[ERROR]======\n");
                    printf("Tree is empty\n");
                } else {
                    printTree(tree->root, NULL, 0, tree->EList);
                }
                break;
            }
            case 7:{
                if(tree->root != tree->EList){
                    freeTree(tree);
                    free(tree);
                    tree = createTree();
                }
                int err = importFromFile(tree);
                if(err == 1){
                    printf("======[ERROR]======\n");
                    printf("This file doesn't exist\n");
                } else if (err == 2){
                    printf("======[ERROR]======\n");
                    printf("Data in file is incorrect\n");
                } else if (err == 3){
                    printf("======[ERROR]======\n");
                    printf("File name shouldn't be empty\n");
                }
                treeToPNG(tree, pict_name);
                break;
            }
            default:{
                printf("======[ERROR]======\n");
                printf("This menu point doesn't exist\n");
                break;
            }
        }
    }
}

char* freadline(FILE* fd){
    char buf[81] = {0};
    char* res = NULL;
    int len = 0;
    int n;
    do {
        n = fscanf(fd, "%80[^\n]", buf);
        if(n < 0){
            if(!res) return NULL;
        } else if(n > 0){
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = (char*) realloc(res, (str_len + 1)* sizeof(char));
            memcpy(res + len, buf, chunk_len);
            len = str_len;
            res[str_len] = '\0';
        } else {
            fscanf(fd, "%*c");
        }
    } while(n > 0);

    if(len > 0){
        res[len] = '\0';
    } else {
        res = (char*) calloc(1, sizeof(char));
    }
    return res;
}

int importFromFile(RBTree* tree){
    printf("======[IMPORT FROM FILE]======\n");
    char* filename = readline("Enter file name\n--> ");
    if(filename == NULL || strlen(filename) < 1) return 3;
    FILE* fd = fopen(filename, "r");
    if(fd == NULL){
        free(filename);
        return 1;
    }
    while(!feof(fd)){
        char* str_key = freadline(fd);
        char* str_data = freadline(fd);
        if(str_key){
            if(str_data){
                char* ptr = NULL;
                unsigned int key = strtoul(str_key, &ptr, 10);
                if(strlen(str_key) < 1 && ptr != str_key + strlen(str_key)){
                    free(str_data);
                    free(str_key);
		    fclose(fd);
	            free(filename);
                    return 2;
                }
                ptr = NULL;
                unsigned int data = strtoul(str_data, &ptr, 10);
                if(strlen(str_data) < 1 && ptr != str_data + strlen(str_data)){
                    free(str_data);
                    free(str_key);
		    fclose(fd);
		    free(filename);
                    return 2;
                }
                addNewElement(tree, data, key);
                free(str_data);
                free(str_key);
            } else {
                free(str_data);
		fclose(fd);
		free(filename);
                return 2;
            }
        } else {
	    fclose(fd);
	    free(filename);
            return 2;
        }
    }
    fclose(fd);
    free(filename);
    return 0;
}

