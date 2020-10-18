/** @file
 * Interfejs udostępniający struktury wykorzystywane w projekcie.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#ifndef STRUCT_H
#define STRUCT_H

typedef struct field_struct fieldtype;
/** Struktura będąca polem na planszy.
 * whose - który gracz posiada to pole, jeśli żaden to 0
 * representant - reprezentant pola w struktórze find-union, domyślnie wskaźnik na samego siebie
 * quantityOfFields - liczba pól reprezentuje w strukturze find-union, domyślnie 0
 * x, y - współrzędne pola
*/
struct field_struct {
    uint32_t whose;
    fieldtype *representant;
    uint64_t quantityOfFields;
    uint32_t x, y;
};

typedef struct player_struct playertype;
/** Struktura będąca graczem.
 * numberOfMyAreas - liczba obszarów gracza
 * numberOfMyFields - liczba pól gracza
 * numberOfContactFields - liczba wolnych pól, 
 * takich, że po zajęciu któregoś nie zmieni się liczba obszarów gracza
*/
struct player_struct {
    bool usedGoldenMove;
    uint64_t numberOfMyAreas;
    uint64_t numberOfMyFields;
    uint64_t numberOfContactFields;
};

typedef struct gamma gamma_t;
/** Struktura przechowująca stan gry.
 * freeFieldsLeft - liczba wolnych pól na planszy
 * areas - limit obszarów dla graczy
*/
struct gamma {
	fieldtype **board;
    playertype *playersArray;
    uint32_t width, height, players;
    uint64_t freeFieldsLeft;
    uint64_t areas;
};

typedef struct request_struct requesttype;
/** Struktura przechowująca zapytanie.
 * command - znak komendy
 * arguments - tablica argumentów
*/
struct request_struct {
	char command;
    uint32_t arguments[4];
};
#endif /* STRUCT_H */