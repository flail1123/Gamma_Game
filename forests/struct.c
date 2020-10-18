#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"


Set forests = NULL, trees = NULL, animals = NULL;

Set* search(Set *pointerToSet, char* name){
    Set set = *pointerToSet;
    if (set == NULL){
        return pointerToSet;
    }
    if (strcmp(set->name, name) == 0){
        return pointerToSet;
    }
    else if (strcmp(set->name, name) < 0){
        return search(&set->right, name);
    }
    else{
        return search(&set->left, name);
    }
}

bool isAterisk(char *string){
    if (*string == '*' && *(string + 1) == '\0')
        return true;
    return false;
}

bool isArgumentEmpty(char *string){
    if (*string == EMPTY)
        return true;
    return false;
}