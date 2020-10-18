#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "request.h"
#include "del.h"

#define START_SIZE 100

bool isWhiteCharacter(char a){
    if (a == ' ' || a == '\t' || a == '\v' || a == '\f' || a == '\r')
        return true;
    return false;
}

int main(){
    int size = START_SIZE, pointer = 0;
    char *string = malloc (size * sizeof(char));
    if (string == NULL) 
        exit(1);
    
    char bit;

    while (scanf("%c", &bit) == 1) {
		if (bit == '\n'){//if it is and of line I need to process it
            *(string + pointer) = ' ';//I need to ensure that there is space at the and of string
            *(string + pointer + 1) = '\0';
            if (ignore(string) == false){
                processRequest (string);
            }
            pointer = 0;
            free (string);
            string = malloc (size * sizeof(char));
            if (string == NULL)                     
                exit(1);
        }
        else if (pointer == 0 || isWhiteCharacter(*(string + pointer - 1)) == false || isWhiteCharacter(bit) == false){//I don't want two white characters next to each otder
            if (isWhiteCharacter(bit))//I change white charaters to space 
                *(string + pointer) = ' ';
            else if (bit == '\0')//I change this chraracter to some other wrong character, because this one is a sign of and of string 
                *(string + pointer) = (char)(2);
            else
                *(string + pointer) = bit;
            pointer ++;
            if (pointer + 5 == size){ //if string is too short double the size
                size *= 2;
                string = realloc(string, size * sizeof(char));
                if(string == NULL)                     
                    exit(1);
            }
        }
	}
    if (bit != '\n' && pointer > 0 && ignore(string) == false)//if there is a line without \n at the and of file
        fprintf(stderr, "ERROR\n");
    deleteEverything();
    free(string);
    return 0;
}