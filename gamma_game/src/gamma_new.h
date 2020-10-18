/** @file
 * Interfejs umożliwiający użycie funkcji gamma_new.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#ifndef GAMMA_NEW_H
#define GAMMA_NEW_H

/** @brief Tworzy strukturę przechowującą stan gry.
 * Alokuje pamięć na nową strukturę przechowującą stan gry.
 * Inicjuje tę strukturę tak, aby reprezentowała początkowy stan gry.
 * @param[in] width   – szerokość planszy, liczba dodatnia,
 * @param[in] height  – wysokość planszy, liczba dodatnia,
 * @param[in] players – liczba graczy, liczba dodatnia,
 * @param[in] areas   – maksymalna liczba obszarów,
 *                      jakie może zająć jeden gracz.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 * zaalokować pamięci lub któryś z parametrów jest niepoprawny.
 */
extern gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas);

#endif /* GAMMA_NEW_H */