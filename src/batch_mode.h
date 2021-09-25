/** @file
 * Interfejs udostępniający tryb wsadowy.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "request.h"
#include "gamma.h"
#include "struct.h"

#ifndef BATCH_MODE_H
#define BATCH_MODE_H

/** @brief Udostępnia moduł wsadowy
 * Wczytuje kolejne linijki z zapytaniami i obsługuje je za pomocą modułu "gamma.h"
 * @param[in,out] g – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] line  – numer wczytanej lini,
 * @param[in] request - wskaźnik na obiekt typu requesttype będący miejscem na kolejne zapytania.
 */
extern void batchMode(gamma_t *g, uint64_t line, requesttype *request);

#endif /* BATCH_MODE_H */


