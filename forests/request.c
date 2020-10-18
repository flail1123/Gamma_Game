#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "del.h"
#include "print.h"
#include "add.h"
#include "request.h"
#include "check.h"
#include "struct.h"

#define EMPTY '\t'

static void doRequest(char *command, char *forest, char *tree, char *animal){
    if (strcmp(command, "ADD") == 0)
        add(forest, tree, animal);
    
    if (strcmp(command, "PRINT") == 0){
        print(forest, tree);
    }
    
    if (strcmp(command, "DEL") == 0)
        del(forest, tree, animal);
    
    if (strcmp(command, "CHECK") == 0){
        check(forest, tree, animal);
    }
}

static char *cutWord (char** request){//takes line and returs next word, if line is empty I return "empty" string 
    if (**request == '\0'){
        char *word = malloc(3 * sizeof(char));
        if(word== NULL) 
            exit(1);
        *word = EMPTY;
        *(word + 1) = '\0';
        return word;
    }

    int where = (strcspn(*request, " "));
    *(*request + where) = '\0';
    char *word = malloc((where + 1 ) * sizeof(char));
    if(word == NULL) 
        exit(1);

    strcpy (word, *request);
    *(word + where) ='\0';
    *request = (*request + where + 1);
    if(**request == ' ')
        *request += 1;
    return word;
}

static bool isCommand(char *command){
    if (strcmp(command, "ADD") != 0 && strcmp(command, "DEL") != 0 && strcmp(command, "PRINT") != 0 && strcmp(command, "CHECK") != 0){
        return false;
    }
    return true;
}

static bool correctCharacters(char *name){
    while(*name != '\0'){
        if ((unsigned int)(*name) < 33 && *name != ' '){
            return false;
        }
        name++;
    }
    return true;
}

static bool isAsteriskLastArgument(char *forest, char *tree, char *animal){
    if (isArgumentEmpty(animal) && isArgumentEmpty(tree) && isAterisk(forest))
        return true;
    
    if (isArgumentEmpty(animal) && isAterisk(tree))
        return true;

    if (isAterisk(animal))
        return true;

    return false;    
}

static bool correctRequest(char *request, char *command, char *forest, char *tree, char *animal){
    if (*request != '\0' || isCommand(command) == false)
        return false;

    if ((strcmp(command, "ADD") == 0 || (strcmp(command, "CHECK")) == 0) && isArgumentEmpty(forest))
        return false; 

    if (strcmp(command, "PRINT") == 0 && isArgumentEmpty(animal) == false)
        return false; 

    if(strcmp(command, "CHECK") == 0 && isAsteriskLastArgument(forest, tree, animal))
        return false; 

    return true;
}

void processRequest(char *request){
    if (correctCharacters(request) == false){
        fprintf(stderr,"ERROR\n");
        return;
    }
    while(*request == ' ')
        request = request + 1;
    
    char *command = cutWord(&request);
    char *forest = cutWord(&request);
    char *tree = cutWord(&request);
    char *animal = cutWord(&request);
    
    if (correctRequest(request, command, forest, tree, animal) == false){
        free(command);
        free (forest);
        free(tree);
        free(animal);
        fprintf(stderr,"ERROR\n");
        return;
    }
    doRequest(command, forest, tree, animal);
    free(command);
    free (forest);
    free(tree);
    free(animal);
}

bool ignore (char *request){
    if(*request == '#')
        return true;
    while(isWhiteCharacter(*request))
        request++;
    if (*request == '\0')
        return true;
    return false;
}