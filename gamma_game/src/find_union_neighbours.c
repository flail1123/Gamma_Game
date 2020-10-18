/** @file
 * Interfejs struktury find-union oraz funkcja zapisująca sąsiadów danego pola.
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

fieldtype *find(fieldtype *field){
    fieldtype *representant = field->representant;

    if (representant != field)
        field->representant = find(representant);

    return field->representant;
}

bool unionn(fieldtype *field1, fieldtype *field2){
    if(field1 == NULL || field2 == NULL)
        return false;

    fieldtype *representant1 = find(field1), *representant2 = find(field2);

    if (representant1 == representant2)
        return false;

    if (representant1->quantityOfFields > representant2->quantityOfFields){
        representant2->representant = representant1;
        representant1->quantityOfFields += representant2->quantityOfFields +1;
    }
    else{
        representant1->representant = representant2;
        representant2->quantityOfFields += representant1->quantityOfFields +1;
    }

    return true;
}

void neighbours (fieldtype **tab, gamma_t *g, uint32_t x, uint32_t y){
    for (uint32_t i = 0; i<4; i++)
        tab[i] = NULL;
    
    if (x > 0)
        tab[0] = &(g->board[x - 1][y]);
    
    if(x + 1 < g->width)
        tab[1] = &(g->board[x + 1][y]);
    
    if (y > 0)
        tab[2] = &(g->board[x][y - 1]);
    
    if(y + 1 < g->height)
        tab[3] = &(g->board[x][y + 1]);
}