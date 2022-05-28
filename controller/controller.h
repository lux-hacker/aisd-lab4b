#ifndef LAB4A_CONTROLLER_H
#define LAB4A_CONTROLLER_H

#include "../view/view.h"
#include "../model/RBTree.h"
#include <stdio.h>

unsigned int getUInt();
void menu();

char* freadline(FILE*);
int importFromFile(RBTree*);

void timing(RBTree*);


#endif //LAB4A_CONTROLLER_H
