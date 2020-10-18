#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "print.h"
#include "struct.h"

static void printSet(Set set){
    if (set != NULL) {
        printSet(set->left);
        printf("%s\n", set->name);
        printSet(set->right);
    }
}

void print(char *forest, char *tree){
     if (isArgumentEmpty(tree) == false){//PRINT las drzewo
        Set *whereForest = search(&forests, forest);
        if (*whereForest == NULL)
            return;

        Set *whereTree = search(&(*whereForest)->dataFirst, tree);
        if (*whereTree == NULL)
            return;

        printSet((*whereTree)->dataFirst);
    }
    else{
        if( isArgumentEmpty(forest)){//PRINT
            printSet(forests);
        }
        else{//PRINT las
            Set *whereForest = search(&forests, forest);
            if (*whereForest == NULL)
                return;
            
            printSet((*whereForest)->dataFirst);
        }
    }
}