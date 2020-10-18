/** @file
 * Interfejs udostępniający tryb interaktywny.
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

#ifndef INTERACTIVE_MODE_H
#define INTERACTIVE_MODE_H

/** @brief Udostępnia moduł interaktywny
 * @param[in,out] g – wskaźnik na strukturę przechowującą stan gry,
 */
extern void interactiveMode(gamma_t *g, uint64_t line);

#endif /* INTERACTIVE_MODE_H */


