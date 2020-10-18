/** @file
 * Interfejs umożliwiający użycie krótkich funkcji z interfejsu gamma.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "struct.h"

void gamma_delete(gamma_t *g){
    if (g == NULL)
        return;
    
    free(g->board[0]);
    free(g->board);
    free(g->playersArray);
    free(g); 
}

// sprawca poprawność parametrów @p g i @p player
static bool correctParametersGPlayer(gamma_t *g, uint32_t player){
    return (g != NULL && player <= g->players && player > 0);    
}


uint64_t gamma_busy_fields(gamma_t *g, uint32_t player){
    if (correctParametersGPlayer(g, player) == false)
        return 0;
    
    return (g->playersArray)[player - 1].numberOfMyFields;
}

uint64_t gamma_free_fields(gamma_t *g, uint32_t player){
    if (correctParametersGPlayer(g, player) == false)
        return 0;

    //jeśli gracz (player) nie osiągnął limitu dostępnych obszarów (g->areas) to wynikiem jest liczba wolnych pól
    if ((g->areas) > (g->playersArray)[player - 1].numberOfMyAreas)
        return g->freeFieldsLeft;
    else// w przeciwnym przypadku liczba pól na jakie może postawić gracz bez zmiany liczby obszarów (areas) 
        return g->playersArray[player - 1].numberOfContactFields;
    
}
