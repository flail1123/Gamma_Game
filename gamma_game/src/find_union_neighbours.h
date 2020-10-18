/** @file
 * Interfejs struktury find-union oraz funkcja zapisująca sąsiadów danego pola.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#ifndef FIND_UNION_H
#define FIND_UNION_H

/** @brief Łączy dwa pola.
 * Łączy dwa pola w strukturze find-union i zwraca prawdę jeśli 
 * były to pola w różnych grupach oraz fałsz w przeciwnym przypadku
 * @param[in] field1 - wskaźnik na pierwsze pole,
 * @param[in] field2 - wskaźnik na drugie pole,
 * @return Wartość @p true lub @p false.
 */
extern bool unionn(fieldtype *field1, fieldtype *field2);

/** @brief Zwraca reprezentanta grupy, do której należy dane pole. 
 * Zwraca wskaźnik na reprezentanta danego pola w strukturze find-union
 * @param[in] field - wskaźnik na pole.
 * @return Wskaźnik na reprezentanta danego pola.
 */
extern fieldtype *find(fieldtype *field);

/** @brief Zapisuje sąsiadów pola w @p tab.
 * Wpisuje w @p tab pola sąsiadujące (lub NULL jeśli takiego pola nie ma) 
 * z polem o współrzędnych @p x @p y.
 * @param[in] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x  – współrzędna x,
 * @param[in] y - współrzędna y.
 */
extern void neighbours (fieldtype **tab, gamma_t *g, uint32_t x, uint32_t y);

#endif /* FIND_UNION_H */