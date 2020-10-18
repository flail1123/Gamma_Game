/** @file
 * Interfejs umożliwiający użycie funkcji gamma_new.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "struct.h"
#include "gamma_new.h"

/* Inicjalizuje tablice dwuwymiarową  struktur typu fieldtype. Najpierw tworzy tablice 
  wskaźników na pola i ustawia je na pola rozpoczynające kolejne rzędy 
  (aby można było odwoływać sie do pola board[x][y]),a potem inicjallizuje współrzędne 
  i ustawia wskaźnik na reprezentanta pola w strukturze find-union na siebie samego. */
static fieldtype** initalizeNewBoard(uint64_t width, uint64_t height){    
    fieldtype **board = calloc(width, sizeof(fieldtype *));
    if(board == NULL) 
        return NULL;
    fieldtype *temporaryBoard = calloc(width * height, sizeof(fieldtype));
    if(temporaryBoard == NULL){  
        free(board);
        return NULL;
    }
    for (uint64_t i = 0; i < width; i++)
         *(board + i) = temporaryBoard + i * height ;
    
    for (uint64_t i = 0; i < width; i++)
    {
        for (uint64_t j = 0; j < height; j++) {
            board[i][j].representant = &board[i][j]; 
            board[i][j].x = i; 
            board[i][j].y = j; 
        }
    }    
    return board;
}
// Zwraca wskaźnik na zainicjowaną tablicę graczy lub NULL, gdy nie udało się zaalokować pamięci.
static playertype* initalizeNewPlayersArray(uint32_t players){
    playertype *playersArray = calloc(players,  sizeof(playertype));
    if(playersArray == NULL)                     
        return NULL;

    return playersArray;
}

gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas){
    if (players == 0 || areas == 0 || width == 0 || height == 0)
        return NULL;
    
    gamma_t *g = calloc(1, sizeof(struct gamma));
    if(g == NULL)                     
        return NULL;
    
    g->width = width;
    g->height = height;
    g->areas = areas;
    g->players = players;
    g->freeFieldsLeft = (uint64_t)width * (uint64_t)height;

    g->playersArray = initalizeNewPlayersArray(players);
    if (g->playersArray == NULL){
        free(g);
        return NULL;
    }
    g->board = initalizeNewBoard(width, height);
    if (g->board == NULL){
        free(g->board);
        free(g);
        return NULL;
    }
    return g;
}