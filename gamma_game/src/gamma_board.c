/** @file
 * Interfejs umożliwiający użycie funkcji gamma_board.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "struct.h"
#include "gamma_board.h"

// Zwraca liczbę znaków potrzebnych do wypisania liczby @p a.
uint32_t howManyCharactersInInt(uint32_t a){
    if (a == 0){
        return 1;
    }
    uint64_t result = 0;
    while(a != 0){
        a /= 10;
        result++;
    }
    return result;
}

// Wpisuje liczbę @p a zamienioną na stringa na koniec @p string
static void intToString(char **string, uint32_t a, uint32_t fieldWidth){
    uint32_t len = howManyCharactersInInt(a);
    for (uint32_t k = 0; k < fieldWidth - len; ++k){
        **string = ' ';
        *string += 1;
    }
    if (a == 0){
        **string = '.';
        *string += 1;
        return;
    }
    *string += len;
    while(a != 0){
        *string -= 1;
        **string = (char)(a % 10 + 48);
        a /= 10;
    }
    *string += len;
}


char* gamma_board(gamma_t *g){
    /*jeśli graczy jest miej niż 10 wypisuje plansze bez spacji
    w przeciwnym przypadku numer każdego gracza na planszy odzielam spacją*/
    if (g == NULL)
        return NULL;
    uint32_t fieldWidth = howManyCharactersInInt(g->players);
    if (fieldWidth != 1)
        fieldWidth++;//na spację
    char *result = malloc(((uint64_t)g->width * (uint64_t)(g->height + 1) * (uint64_t)fieldWidth + 5) * sizeof(char));
    if (result == NULL)
        return NULL;
    
    char *pointer = result;
    for (uint32_t i = g->height; i > 0 ; i--){
        for (uint32_t j = 0; j < g->width; j++)
            intToString(&pointer, g->board[j][i-1].whose, fieldWidth);
        *pointer = '\n';
        pointer++;
    }
    *pointer = '\0';
    return result;

}
