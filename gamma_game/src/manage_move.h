/** @file
 * Interfejs umożliwiający użycie funkcji gamma_move oraz gamma_golden_move.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#ifndef GAMMA_MOVE_H
#define GAMMA_MOVE_H


/** Dodaje pole na planszy
 * Zmienia właściciela planszy z nikogo na gracza ( @p player ), 
 * łączy pole z sąsiadami (w strukturze find-union) i uaktualnia 
 * liczbę obszarów gracza (numberOfMyAreas), a następnie uaktualnia liczbę
 * "contact fields" (numerOfMyContactFields).
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 */
void addField(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** Sprawdza czy po dodaniu pola gracza ( @p player) jego liczba obszarów (numerOfMyAreas) nie przekroczy limitu (g->areas)
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli liczba obszarów będzie w porządku, a @p false,
*/
bool tooMuchAreas(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** Usuwa pole z planszy.
 * Uaktualnia liczbę "contact fields" (numerOfMyContactFields),rozczłonkowuje 
 * grupe (w strukturze find-union) do której należy pole @p x @p y
 * uwalnia pole od poprzedniego właściciela ( @p formerOwner ) i rekurencyjnie łączy 
 * wcześniej rozczłąkowaną grupę (w strukturze find-union), ale już
 * bez pola @p x @p y, uaktualnia liczbę obszarów gracza (numberOfMyAreas), a na koniec 
 * zwraca prawdę jeśli ilość obszarów danego gracza (numberOfMyAreas) jest poniżej 
 * limitu (g->areas) lub fałsz w przedzwnym przypadku.
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] formerOwner  – numer gracza, będącego poprzednim włąścielem pola, 
                        liczba dodatnia niewiększa od wartości @p formerOwner z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli ilość obszarów danego gracza (numberOfMyAreas) jest poniżej 
 limitu (g->areas), a @p false, w przeciwnym wypadku.
 */
bool removeField(gamma_t *g, uint32_t formerOwner, uint32_t x, uint32_t y);

/** @brief Wykonuje ruch.
 * Ustawia pionek gracza @p player na polu (@p x, @p y).
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli ruch został wykonany, a @p false,
 * gdy ruch jest nielegalny lub któryś z parametrów jest niepoprawny.
 */
extern bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Wykonuje złoty ruch.
 * Ustawia pionek gracza @p player na polu (@p x, @p y) zajętym przez innego
 * gracza, usuwając pionek innego gracza.
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli ruch został wykonany, a @p false,
 * gdy gracz wykorzystał już swój złoty ruch, ruch jest nielegalny
 * lub któryś z parametrów jest niepoprawny.
 */
extern bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y);

#endif /* GAMMA_MOVE_H */











