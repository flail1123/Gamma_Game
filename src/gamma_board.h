/** @file
 * Interfejs umożliwiający użycie funkcji gamma_board i howManyCharactersInInt.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#ifndef GAMMA_BOARD_H
#define GAMMA_BOARD_H

/** @brief Zwraca ilość cyfr w liczbie
 * @param[in] a – liczba
 * @return Ilość cyfr w liczbie.
 */
extern uint32_t howManyCharactersInInt(uint32_t a);

/** @brief Daje napis opisujący stan planszy.
 * Alokuje w pamięci bufor, w którym umieszcza napis zawierający tekstowy
 * opis aktualnego stanu planszy. Przykład znajduje się w pliku gamma_test.c.
 * Funkcja wywołująca musi zwolnić ten bufor.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry.
 * @return Wskaźnik na zaalokowany bufor zawierający napis opisujący stan
 * planszy lub NULL, jeśli nie udało się zaalokować pamięci.
 */
extern char* gamma_board(gamma_t *g);

#endif /* GAMMA_BOARD_H */