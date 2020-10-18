#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "add.h"
#include "struct.h"


static Set newNode(char* name) {
	Set set = calloc(1, sizeof(struct Node));
    if(set == NULL)                     
        exit(1);

    char *namecopy = malloc ((((int)strlen(name)) + 1) * sizeof(char));
    if(namecopy == NULL)                     
        exit(1);
    
    strcpy (namecopy, name);
    *(namecopy + strlen(name)) = '\0';
	set->name = namecopy;
    set->count = 1;
	set->left = set->right = set->dataFirst = set->dataSecond = NULL;
	return set;
}

static Set* insert(Set *set, char* name) {//it adds object to set and returns pointer to it, if it already exists it won't add it second time only increments count parameter
	if (*set == NULL) {
		*set = newNode(name);
		return set;
	}

	if (strcmp((*set)-> name, name) == 0) {
        (*set)->count += 1; 
		return set;
	} 
    else if (strcmp((*set)->name, name) > 0) {
		return insert(&((*set)->left), name);
	} 
    else {
		return insert(&((*set)->right), name);
	}
}

void addForestTreeAnimal(char *forest, char *tree, char *animal){
    Set *whereForest = insert(&forests, forest);
    Set *whereTreeInForest, *whereTreeInTrees;

    if ( *(search(&(*whereForest)->dataFirst, tree)) == NULL){//if tree already exists
        whereTreeInForest = insert(&(*whereForest)->dataFirst, tree);
        whereTreeInTrees = insert(&trees, tree);
    }
    else{
        whereTreeInForest = search(&(*whereForest)->dataFirst, tree);
        whereTreeInTrees = search(&trees, tree);
    }

    if (*search(&(*whereTreeInForest)->dataFirst, animal) == NULL){//if animal already exists
        insert(&(*whereTreeInForest)->dataFirst, animal);
        insert(&(*whereForest)->dataSecond, animal);
        insert(&animals, animal);
        insert(&(*whereTreeInTrees)->dataFirst, animal);
    }
}

void addForestTree(char *forest, char *tree){
    Set *whereForest = insert(&forests, forest);

    if ( *(search(&(*whereForest)->dataFirst, tree)) == NULL){//if tree already exists
        insert(&(*whereForest)->dataFirst, tree);
        insert(&trees, tree);
    }
}

void addForest(char *forest){
    insert(&forests, forest);
}

void add(char *forest, char *tree, char *animal){
    if (isArgumentEmpty(animal) == false){//ADD las drzewo zwierzę
       addForestTreeAnimal(forest, tree, animal);
    }
    else{
        if (isArgumentEmpty(tree)){//ADD las
            addForest(forest);
        }
        else{//ADD las drzewo
            addForestTree(forest, tree);
        }
    }
    printf("OK\n");
}
