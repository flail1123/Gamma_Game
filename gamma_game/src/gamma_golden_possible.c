/** @file
 * Interfejs umożliwiający użycie funkcji gamma_golden_possible z interfejsu gamma.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "struct.h"
#include "gamma_short_functions.h"
#include "manage_move.h"

static bool gamma_golden_possible_in_x_y(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    uint32_t formerOwner = g->board[x][y].whose; 
    if (formerOwner == 0 || formerOwner == player)
        return false;

    if (tooMuchAreas(g, player, x, y))
        return false;

    if (removeField(g, formerOwner, x, y)){//symuluje wykonanie golden move, a następnie wracam planszę do poprzedniego stanu i zwracam odpowiedź
        addField(g, formerOwner, x, y);
        return true;
    }
    else{
        addField(g, formerOwner, x, y);
        return false;
    }
}

bool gamma_golden_possible(gamma_t *g, uint32_t player){
    if ((g != NULL && player <= g->players && player > 0) == false)
        return false;
    
    if (g->playersArray[player - 1].usedGoldenMove == true)//jeśli użyłeś golden move to false
        return false;

    if (g->freeFieldsLeft + g->playersArray[player - 1].numberOfMyFields == (uint64_t)(g->width) * (uint64_t)(g->height))//jeśli nie ma żadnego pola zajętego przez innego gracza to false
        return false;
    //teraz wiemy, że istnieje pole zajęte przez innego gracza
    
    for (uint32_t i = g->height; i > 0 ; i--){
        for (uint32_t j = 0; j < g->width; j++){
            if (gamma_golden_possible_in_x_y(g, player, j, i - 1))
                return true;
        }
    }
    return false;
}


