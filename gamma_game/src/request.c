/** @file
 * Interfejs udostępniający funkcję interpretującą linie zapytania.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>
#include "struct.h"

static inline bool isWhiteCharacter(char a){
    if (a == ' ' || a == '\t' || a == '\v' || a == '\f' || a == '\r' || a == '\n')
        return true;
    return false;
}

static inline bool isnumberOfParemetersCorrect(char c, uint32_t j){
    if (c == 'p' && j != 0)
        return false;
    
    if ((c == 'I' || c == 'B') && j != 4)
        return false;
 
    if ((c == 'b' || c == 'f' || c == 'q') && j != 1)
        return false;

    if ((c == 'm' || c == 'g') && j != 3)
        return false;

    return true;
}

static inline bool isDigit(char a){
    if ((uint32_t)a >= 48 && (uint32_t)a <= 57)
        return true;
    return false;
}

static bool correctCharacters(char *str){
    if (!(*str == 'p' || *str == 'B' || *str == 'I' || *str == 'f' || *str == 'g' || *str == 'q' || *str == 'm' || *str == 'b'))
        return false;
    str++;
    if (!isWhiteCharacter(*str))
        return false;
    for (int i = 0; *(str + i) != '\n'; ++i){
        if (!isDigit(*(str + i)) && !isWhiteCharacter(*(str + i)))
            return false;
    }
    return true;
}

static uint64_t stringNaInt(char **str){
    if (**str == '0' && isWhiteCharacter(*(*str + 1))){//pojedyńcze 0 jako argument
        *str = *str + 1;
        return 0;
    }
    if(**str == '0')//liczby z zerami wiodącymi uznaje za niepoprawne 
        return 4294967296;
    
    uint32_t result = 0;
    while (isDigit(*(*str + result))){
        result++; 
    }
    if (result > 12)//jesli liczba ma za dużo cyfr to jest za duża
        return 4294967296;
    
    uint64_t m=1, suma=0;
    while(result > 1){
        m*=10;
        result--;
    }
    while (isDigit(**(str)))
    {
        suma+=((uint64_t)((**str)-48))*m;
        m/=10;
        *str = *str + 1;
    }
    return suma;
}

bool prossesRequest(char *str, requesttype* request){
    if(!correctCharacters(str))
        return false;
    
    request->command = *str;
    str++;
    uint32_t j =0;
    while (isWhiteCharacter(*str))
            str++;
    
    while (*str != '\0')//wyciąganie argumentów ze stringa
    {
        if (j == 4)//jeśli więcej niż 4 argumenty to zakończ
            return false;
        uint64_t a = stringNaInt(&str);
        if (a > 4294967295)//jeśli za duży argument to zakończ
            return false;
        request->arguments[j] = (uint32_t)a;
        j++;
        while (isWhiteCharacter(*str))
            str++;
    }
    if (!isnumberOfParemetersCorrect(request->command, j))
        return false;

    if (request->command == 'I'){
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        if (request->arguments[0]>w.ws_col || 120 > w.ws_col || request->arguments[1]>w.ws_row){//plansza jest za duża na ten terminal
            return false;
        }
    }

    return true;
}
