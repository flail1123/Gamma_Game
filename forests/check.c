#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "check.h"
#include "struct.h"

void checkAsterisTreeAnimal(char *tree, char *animal){
    Set *whereTree = search(&trees, tree);
    if (*whereTree == NULL){
        printf("NO\n");
        return;
    }
    if (*(search(&(*whereTree)->dataFirst, animal)) == NULL){
        printf("NO\n");
        return;
    }
    printf("YES\n");
}

void checkForestTreekAnimal(char *forest, char *tree, char *animal){
    Set *whereForest = search(&forests, forest);
    if (*whereForest == NULL){
        printf("NO\n");
        return;
    }
    Set *whereTree = search(&(*whereForest)->dataFirst, tree);
    if (*whereTree == NULL){
        printf("NO\n");
        return;
    }
    Set *whereAnimal = search(&(*whereTree)->dataFirst, animal);
    if (*whereAnimal == NULL){
        printf("NO\n");
        return;
    }
    printf("YES\n");
}

void checkForestAsteriskAnimal(char *forest, char *animal){
    Set *whereForest = search(&forests, forest);
    if (*whereForest == NULL){
        printf("NO\n");
        return;
    }
    if (*(search(&(*whereForest)->dataSecond, animal)) == NULL){
        printf("NO\n");
        return;
    }
    printf("YES\n");
}

void checkForestTree(char *forest, char *tree){
    Set *whereForest = search(&forests, forest);
    if (*whereForest == NULL){
        printf("NO\n");
        return;
    }
    if (*(search(&(*whereForest)->dataFirst, tree)) == NULL){
        printf("NO\n");
        return;
    }
    printf("YES\n");
}

void checkAsteriskAsteriskAnimal(char *animal){
    if (*(search(&animals, animal)) == NULL)
        printf("NO\n");
    else
        printf("YES\n");
}

void checkAsteriskTree(char *tree){
    if (*(search(&trees, tree)) == NULL)
        printf("NO\n");
    else
        printf("YES\n");
}

void checkForest(char* forest){
    if (*(search(&forests, forest)) == NULL)
        printf("NO\n");
    else
        printf("YES\n");
}

void check(char *forest, char *tree, char *animal){
    if (isArgumentEmpty(animal)){
        if (isArgumentEmpty(tree)){//CHECK las
            checkForest(forest);
        }
        else if (isAterisk(forest)){//CHECK * drzewo
            checkAsteriskTree(tree);
        }
        else{//CHECK las drzewo
            checkForestTree(forest, tree);
        }
    }
    else if(isAterisk(tree)){
        if(isAterisk(forest)){//CHECK * * zwierzę
            checkAsteriskAsteriskAnimal(animal);
        }
        else{//CHECK las * zwierzę
            checkForestAsteriskAnimal(forest, animal);
        }
    }
    else if(isAterisk(forest)){//CHECK * drzewo zwierzę
        checkAsterisTreeAnimal(tree, animal);
    }
    else{//CHECK las drzewo zwierzę
        checkForestTreekAnimal(forest, tree, animal);
    }

}