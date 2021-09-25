/** @file
 * Interfejs udostępniający funkcję interpretującą linie zapytania.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include "struct.h"

#ifndef REQUEST_H
#define REQUEST_H

/** @brief Przetwarza zapaytanie.
 * Przetwarza linije tekstu będącą zapytaniem, zapisuje przetworzone informacje
 * w obiekcie request i zwraca prawdę. Chyba, że linijka jest błędna to zwraca fałsz.
 * @param[in] str - linijki tekstu będąca zapytaniem.
 * @param[in, out] request - struktura dająca miejsce na zapisanie zapytania
 * @return @true jeśli udało się przetworzyć zapytanie i @false w przeciwnym przypadku.
 */
extern bool prossesRequest(char *str, requesttype *request);


#endif /* REQUEST_H */


