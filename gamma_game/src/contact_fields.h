/** @file
 * Interfejs udostępniający funkcję changeContactFields.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#ifndef CONTACT_FIELDS_H
#define CONTACT_FIELDS_H

/** @brief Uaktualnia atrybut numberOfContactFields
 * Uaktualnia wszystkim atrybut numberOfContactFields
 * po dodaniu lub usunięciu pola na planszy o współrzędnych @p x @p y
 * @param[in,out] g – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x  – współrzędna x,
 * @param[in] y - współrzędna y,
 * @param[in] a - liczba równa -1 jeśli pole zostało usunięte lub 1 jeśli pole zostało dodane.
 */
extern void changeContactFields(gamma_t *g, uint32_t x, uint32_t y, uint64_t a);

#endif /* CONTACT_FIELDS_H */


