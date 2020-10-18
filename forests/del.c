#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "del.h"
#include "struct.h"

static void deleteStructure(Set *set){
    if ((*set) == NULL)
        return;
    deleteStructure(&(*set)->dataFirst);
    deleteStructure(&(*set)->dataSecond);
    deleteStructure(&(*set)->left);
    deleteStructure(&(*set)->right);
    free((*set)->name);
    free(*set);
    *set = NULL;
}

static Set* findBiggestElement(Set *set){
    if ((*set)->right == NULL){
        return set;
    }
    else{
        return findBiggestElement(&(*set)->right);
    }
}

static void deleteObject(Set *set){
    if ((*set) == NULL) {
		return;
	}
    deleteStructure(&(*set)->dataFirst);
    deleteStructure(&(*set)->dataSecond);
    free((*set)->name);
    if ((*set)->right == NULL){
        Set oldSet = *set;
		*set = (*set)->left;
		free(oldSet);
    }
    else{
        if ((*set)->left == NULL){
            Set oldSet = *set;
		    *set = (*set)->right;
		    free(oldSet);
        }
        else{
            Set *newSet = findBiggestElement(&(*set)->left);
		    (*set)->dataFirst = (*newSet)->dataFirst;
            (*set)->dataSecond = (*newSet)->dataSecond;
            (*set)->name = (*newSet)->name;
            (*set)->count = (*newSet)->count;
            Set oldSet = *newSet;
            *newSet = (*newSet)->left;
            free(oldSet);
        }
    }
    
}

static void deleteObjectIfCount1(Set *set){
    if ((*set) == NULL)
        return;
    if ((*set)->count > 1){
        (*set)->count -= 1;
        return;
    }
    deleteObject(set);
}

static void deleteAnimalKnowingWhereItIs(Set *animalInAnimals, Set *animalOnTreeInTrees, Set *animalInSetOfAnimalsInForest, Set *animalOnTreeInForest){
    //delete animal from animals
    deleteObjectIfCount1(animalInAnimals);

    //delete animal from its tree in trees
    deleteObjectIfCount1(animalOnTreeInTrees);

    //delete animal from its forest's set of animals
    deleteObjectIfCount1(animalInSetOfAnimalsInForest);

    //delete animal from its tree in its forest
    deleteObject(animalOnTreeInForest);
}

static void deleteAnimal(char *forest, char *tree, char *animal){
    Set *animalInAnimals = search(&animals, animal);

    Set *whereTreeInTrees = search(&trees, tree);
    if (*whereTreeInTrees == NULL)
        return;
    Set *animalOnTreeInTrees = search (&(*whereTreeInTrees)->dataFirst, animal);

    Set *whereForest = search(&forests, forest);
    if (*whereForest == NULL)
        return;
    Set *animalInSetOfAnimalsInForest = search (&(*whereForest)->dataSecond, animal);

    Set *whereTreeInForest = search(&(*whereForest)->dataFirst, tree);
    if (*whereTreeInForest == NULL)
        return;
    Set *animalOnTreeInForest = search (&(*whereTreeInForest)->dataFirst, animal);
    if (*animalOnTreeInForest == NULL)
        return;

    deleteAnimalKnowingWhereItIs(animalInAnimals, animalOnTreeInTrees, animalInSetOfAnimalsInForest, animalOnTreeInForest);
}

static void deleteAnimalsFromTree(Set *animalOnTreeInForest, Set *whereForest, Set *whereTreeInTrees){
    if (*animalOnTreeInForest == NULL)
        return;
    
    deleteAnimalsFromTree(&(*animalOnTreeInForest)->left, whereForest, whereTreeInTrees);
    deleteAnimalsFromTree(&(*animalOnTreeInForest)->right, whereForest, whereTreeInTrees);
    char *animal = (*animalOnTreeInForest)->name;

    Set *animalInAnimals = search(&animals, animal);

    Set *animalOnTreeInTrees = search (&(*whereTreeInTrees)->dataFirst, animal);

    Set *animalInSetOfAnimalsInForest = search (&(*whereForest)->dataSecond, animal);

    deleteAnimalKnowingWhereItIs(animalInAnimals, animalOnTreeInTrees, animalInSetOfAnimalsInForest, animalOnTreeInForest);
    
}

static void deleteTree(char *forest, char *tree){

    Set *whereForest = search(&forests, forest);
    if (*whereForest == NULL)
        return;
    
    Set *whereTreeInForest = search(&(*whereForest)->dataFirst, tree);
    if (*whereTreeInForest == NULL)
        return;

    Set *whereTreeInTrees = search(&trees, tree);
    if (*whereTreeInTrees == NULL)
        return;
    
    Set *animalOnTreeInForest = &(*whereTreeInForest)->dataFirst;
    deleteAnimalsFromTree(animalOnTreeInForest, whereForest, whereTreeInTrees);
    deleteObjectIfCount1(whereTreeInTrees);
    deleteObject(whereTreeInForest);
}

static void deleteTreesFromForest(Set *whereTreeInForest, Set *whereForest){
    if (*whereTreeInForest == NULL)
        return;

    deleteTreesFromForest(&(*whereTreeInForest)->left, whereForest);
    deleteTreesFromForest(&(*whereTreeInForest)->right, whereForest);
    char *tree = (*whereTreeInForest)->name;

    Set *whereTreeInTrees = search(&trees, tree);
    if (*whereTreeInTrees == NULL)
        return;
    
    Set *animalOnTreeInForest = &(*whereTreeInForest)->dataFirst;
    deleteAnimalsFromTree(animalOnTreeInForest, whereForest, whereTreeInTrees);

    deleteObjectIfCount1(whereTreeInTrees);
    
}

static void deleteForest(char *forest){
    Set *whereForest = search(&forests, forest);
    if (*whereForest == NULL)
        return;
    deleteTreesFromForest(&(*whereForest)->dataFirst, whereForest);
    deleteObject(whereForest);
}

void deleteEverything(){
    deleteStructure(&animals);
    deleteStructure(&trees);
    deleteStructure(&forests);
}

void del(char *forest, char *tree, char *animal){
    if(isArgumentEmpty(animal) ==false){//DEL las drzewo zwierzę
        deleteAnimal(forest, tree, animal);
    }
    else if (isArgumentEmpty(tree) == false){//DEL las drzewo
        deleteTree(forest, tree);
    }
    else if (isArgumentEmpty(forest) == false){////DEL las
        deleteForest(forest);
    }
    else{//DEL
        deleteEverything();
    }
    printf("OK\n");
}
