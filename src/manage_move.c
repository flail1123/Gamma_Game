/** @file
 * Interfejs umożliwiający użycie funkcji gamma_move oraz gamma_golden_move.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "struct.h"
#include "manage_move.h"
#include "find_union_neighbours.h"
#include "contact_fields.h"

// Tworzy z pola pojedyńczą grupę (w strukturze find-union) i wykonuje się rekurencyjnie na sąsiadach pola.
static void dfsDifision(gamma_t *g, uint32_t formerOwner, uint32_t x, uint32_t y){
    g->board[x][y].representant = &(g->board[x][y]);
    g->board[x][y].quantityOfFields = 0;
    fieldtype *tab[4]; 
    neighbours (tab, g, x, y);
    for (uint32_t i = 0; i < 4; i++){
        if (tab[i] != NULL && tab[i]->whose == formerOwner && tab[i]->representant != tab[i])
            dfsDifision(g, formerOwner, tab[i]->x, tab[i]->y);
    }
}

// Łączy pole z jego sąsiadami (w strukturze find-union) i wykonuje się rekurencyjnie na sąsiadach pola.
static void dfsUnion(gamma_t *g, uint32_t formerOwner, uint32_t x, uint32_t y){
    fieldtype *tab[4]; 
    neighbours (tab, g, x, y);
    for (uint32_t i = 0; i < 4; i++){
        if (tab[i] != NULL && tab[i]->whose == formerOwner && tab[i]->representant == tab[i]){
            unionn(&(g->board[x][y]), tab[i]);
            dfsUnion(g, formerOwner, tab[i]->x, tab[i]->y);
        }
    }
}

// Uaktualnia pole numberOfMyAreas gracza formerOwner po usunięciu pola o wsp x y.
static void changeAreas(gamma_t *g, uint32_t formerOwner, uint32_t x, uint32_t y){
    g->playersArray[formerOwner - 1].numberOfMyAreas --;
    fieldtype *tab[4]; 
    neighbours (tab, g, x, y);
    
    for (uint32_t i = 0; i < 4; i++){
        if(tab[i] != NULL && tab[i]->whose == formerOwner){
            bool f = false;
            for (uint32_t j = 0; j < i; j++){
                if (tab[j] != NULL && tab[i]->representant == tab[j]->representant)
                    f = true;
            }
            if (f == false)
                g->playersArray[formerOwner - 1].numberOfMyAreas++;
        }
    }
}

// Uwalnia pola o wsp @p x @p y od właściciela ( @p formerOwner )
static inline void freeThisField(gamma_t *g, uint32_t formerOwner, uint32_t x, uint32_t y){
    g->board[x][y].representant = &(g->board[x][y]);
    g->board[x][y].whose = 0;
    g->playersArray[formerOwner - 1].numberOfMyFields--;
    g->freeFieldsLeft++;
}

bool removeField(gamma_t *g, uint32_t formerOwner, uint32_t x, uint32_t y){
    changeContactFields(g, x, y, -1);
    fieldtype formerRepresentant = *(g->board[x][y].representant);

    dfsDifision(g, formerOwner, formerRepresentant.x, formerRepresentant.y);
    freeThisField(g, formerOwner, x, y);
    
    fieldtype *tab[4]; 
    neighbours (tab, g, x, y);
    for (uint32_t i = 0; i < 4; ++i){
        if (tab[i] != NULL &&tab[i]->whose == formerOwner)
            dfsUnion(g, formerOwner, tab[i]->x, tab[i]->y);
    }
    changeAreas(g, formerOwner, x, y);
    return g->playersArray[formerOwner - 1].numberOfMyAreas <= g->areas;
}

bool tooMuchAreas(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    fieldtype *tab[4]; 
    neighbours (tab, g, x, y);
    bool isOneOfMyNeighboursOwnerPlayer = false;
    for (uint32_t i = 0; i < 4; ++i){
        if (tab[i] != NULL && tab[i]->whose == player){
            isOneOfMyNeighboursOwnerPlayer = true;
        }
    }
    return (isOneOfMyNeighboursOwnerPlayer == false && g->playersArray[player - 1].numberOfMyAreas == g->areas);
}

// sprawca poprawność parametrów @p g, @p player i współrzędnych @p x @p y
static inline bool correctParametersGPlayerXY(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    if (g == NULL)
        return false;

    if (player > g->players || player == 0 || x >= g->width || y >= g->height)
        return false;
    return true;    
}

void addField(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    g->board[x][y].whose = player;
    g->playersArray[player - 1].numberOfMyAreas++;
    g->playersArray[player - 1].numberOfMyFields++;
    g->freeFieldsLeft--;    

    fieldtype *tab[4]; 
    neighbours (tab, g, x, y);
    for (uint32_t i = 0; i < 4; ++i){
        if (tab[i] != NULL && tab[i]->whose == player && unionn(&g->board[x][y],  tab[i]))
            g->playersArray[player - 1].numberOfMyAreas--;
    }
    changeContactFields(g, x, y, 1);
}


bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    if (correctParametersGPlayerXY(g, player, x, y) == false)
        return false;

    if (tooMuchAreas(g, player, x, y) == true || g->board[x][y].whose != 0)
        return false;

    addField(g, player, x, y);
    return true;
}


bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    if (correctParametersGPlayerXY(g, player, x, y) == false)
        return false;

    if (tooMuchAreas(g, player, x, y) || g->playersArray[player - 1].usedGoldenMove)
        return false;

    uint32_t formerOwner = g->board[x][y].whose; 
    if(formerOwner == 0 || formerOwner == player)
        return false;

    //jeśli usunięcie się powiodło to dodaje pole gracza (player)
    if (removeField(g, formerOwner, x, y)){
        addField(g, player, x, y);
        g->playersArray[player - 1].usedGoldenMove = true;
        return true;
    }
    else{//jeśli nie to dodaje pole poprzedniego właściciela (fomerOwner) przywracając planszę do pierwotnej postaci
        addField(g, formerOwner, x, y);
        return false;
    }
}