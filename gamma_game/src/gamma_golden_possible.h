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


#ifndef GAMMA_GOLDEN_POSSIBLE_H
#define GAMMA_GOLDEN_POSSIBLE_H

/** @brief Sprawdza, czy gracz może wykonać złoty ruch.
 * Sprawdza, czy gracz @p player jeszcze nie wykonał w tej rozgrywce złotego
 * ruchu, symujluje wykonanie takiego ruchu, a następnie wraca plasze do poprzedniej 
 * postaci i zwraca odpowiedź
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli gracz może wykonać złoty ruch 
 * a @p false w przeciwnym przypadku.
 */
extern bool gamma_golden_possible(gamma_t *g, uint32_t player);

#endif /* GAMMA_GOLDEN_POSSIBLE_H */



