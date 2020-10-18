/** @file
 * Interfejs udostępniający funkcję changeContactFields.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "struct.h"
#include "find_union_neighbours.h"
#include "contact_fields.h"

/* Sprawdza czy wśród sąsiadów pola o współrzędnych @p x @p y znajduje się
  dokładnie jedno pole o takim samym właścicielu co pole o współrzędnych @p x @p y */
bool isItCandidateForNewContanctField(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    uint32_t counter = 0;
    fieldtype *tab[4]; 
    neighbours (tab, g, x, y);
    
    for (uint32_t i = 0; i<4; i++){
        if (tab[i] != NULL && tab[i]->whose == player){
            counter++;
        }
    }
    if(counter == 1)
        return true;
    
    return false;
} 

/* Obsługuje zmiane numberOfContactFields gracza (player), przy dodaniu lub usunięciu pola.
  Dla 'a' równego 1 dodaje do numberOfContactFields graczowi, który dodał swoje nowe pole,
  dla 'a' równego -1 odejmuje od numberOfContactFields graczowi, który usunął swoje pole.
 */
static void addNewContactFieldsToPlayer(fieldtype **tab, gamma_t *g, uint32_t player, uint64_t a){
    for (uint32_t i = 0; i<4; i++){

        if (tab[i] != NULL && tab[i]->whose == 0)
            if (isItCandidateForNewContanctField(g, player, tab[i]->x, tab[i]->y))
                g->playersArray[player - 1].numberOfContactFields += a;
    }
}

/* Obsługuje zmiane numberOfContactFields właścicieli sąsiadów pola, które zostało usunięte lub dodane.
  dla 'a' równego -1 dodaje do numberOfContactFields graczy, którzy zystkali na usunięciu nowego pola
*/
static void substractContractFields(fieldtype **tab, gamma_t *g, uint64_t a){
    for (uint32_t i = 0; i<4; i++){
        if(tab[i] != NULL){
            bool f = false;
            for (uint32_t j = 0; j<i; j++){
                if (tab[j] != NULL && tab[i]->whose == tab[j]->whose)
                    f = true;
            }
            if (f == false && tab[i]->whose != 0){
                g->playersArray[tab[i]->whose - 1].numberOfContactFields-=a; 
            }
        }
    }
}

void changeContactFields(gamma_t *g, uint32_t x, uint32_t y, uint64_t a){
    fieldtype *tab[4]; 
    neighbours (tab, g, x, y);

    substractContractFields(tab, g, a);

    addNewContactFieldsToPlayer(tab, g, g->board[x][y].whose, a);
}