/** @file
 * Interfejs udostępniający tryb interaktywny.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "request.h"
#include "gamma.h"
#include "struct.h"

//wczytuje klawisz jaki wcisnął użytkownik
static uint32_t getKey(){
    char input = getchar();
    while(true){
        if (input == 71 || input == 103)
            return 'g';
        else if (input == 32)
            return 'm';
        else if (input == 67 || input == 99)
            return 'c';
        else if (input == 4)
            return 'k';
        else if (input == 27){
            input = getchar();
            if(input == 91)
            {
                input = getchar();
                if (input == 65)
                    return 'w';
                else if (input == 66)
                    return 's';
                else if (input == 67)
                    return 'd';
                else if (input == 68)
                    return 'a';
            }
        }
        else
            return 'q';
    }
}

//ustala kolejnego wolnego gracza
static uint32_t nextPlayer(gamma_t *g, uint32_t player){
    uint32_t newPlayer = player;
    do{
        newPlayer++;
        if (newPlayer > g->players)
            newPlayer = 1;
        if (gamma_free_fields(g, newPlayer) != 0 || gamma_golden_possible(g, newPlayer))
            return newPlayer;
    }while (newPlayer != player);
    return 0;
}

static void displayPlayer(uint32_t player, uint32_t fieldWidth){
    if (player == 0){
        for (uint32_t i = 0; i < fieldWidth - 1; ++i)
            printf(" ");
        printf("\x1b[3%dm.", 6);
    }
    else{
        for (uint32_t i = 0; i < fieldWidth - howManyCharactersInInt(player); ++i)
            printf(" ");
        printf("\x1b[3%dm%d", player%5+1, player);
    }
}

//obsługuje poruszenie kursora na planszy
static void arrows(gamma_t *g, char a, uint32_t *x, uint32_t *y, uint32_t fieldWidth){
    printf("\x1b[4%dm", 0);
    displayPlayer(g->board[*x][*y].whose, fieldWidth);
    printf("\x1b[%dD", fieldWidth);
    if (a == 'w' && *y != g->height - 1){//góra
        printf("\x1b[%dA", 1);
        *y = *y + 1;
    }
    else if (a == 's' && *y != 0){//dół
        printf("\x1b[%dB", 1);
        *y = *y - 1;
    }
    else if (a == 'd' && *x != g->width - 1) {//prawo
        printf("\x1b[%dC", fieldWidth);
        *x = *x + 1;
    }
    else if (a == 'a' && *x != 0){//lewo
        printf("\x1b[%dD", fieldWidth);
        *x = *x - 1;
    }
    printf("\x1b[4%dm", 7);
    displayPlayer(g->board[*x][*y].whose, fieldWidth);
    printf("\x1b[%dD", fieldWidth);
}

//obsługuje ruch użytkownika
static void doRequest(gamma_t *g, char a, uint32_t *player, uint32_t *x, uint32_t *y, uint32_t fieldWidth){
    if (a == 'm' || a == 'g' || a == 'c'){  
        if (a == 'm'){
            if(!gamma_move(g, *player, *x, *y)){
                return;
            }
            printf("\x1b[4%dm", 7);
            displayPlayer(*player, fieldWidth);
            printf("\x1b[%dD", fieldWidth);
        }
        else if (a == 'g'){
            if(!gamma_golden_move(g, *player, *x, *y)){
                return;
            }
            printf("\x1b[4%dm", 7);
            displayPlayer(*player, fieldWidth);
            printf("\x1b[%dD", fieldWidth);
        }
        else if (a == 3){
        }
        *player = nextPlayer(g, *player);
    }
    else
        arrows(g, a, x, y, fieldWidth);
}

//wyświetla informacje o aktualnym graczu
static void display(gamma_t *g, uint32_t player){
    printf("\x1b[4%dm", 0);
    printf("\x1b%d", 7);
    printf("\x1b[%d;%df", g->height + 1, 0);
    if (gamma_golden_possible(g, player))
        printf ("\x1b[3%dmPlayer: %d; Busy Fields: %ld; Free Fields: %ld; G                                 \x1b[0m", (player%5+1), player, gamma_busy_fields(g, player), gamma_free_fields(g, player));
    else
        printf ("\x1b[3%dmPlayer: %d; Busy Fields: %ld; Free Fields: %ld;                                   \x1b[0m", (player%5+1), player, gamma_busy_fields(g, player), gamma_free_fields(g, player));
    printf("\x1b%d", 8);
}

static inline char* initializeBoard(gamma_t *g, uint32_t fieldWidth){
    printf("\x1b[3%dm", 6);
    char *board = gamma_board(g);
    if (board == NULL)
        exit(1);
    printf("\x1b[2J");
    printf("\x1b[1;1f");
    printf("%s", board);
    printf("\x1b[%d;%df", g->height-g->height/2, g->width/2*fieldWidth+1);
    printf("\x1b[4%dm", 7);
    displayPlayer(0, fieldWidth);
    printf("\x1b[%dD", fieldWidth);
    return board;
}

void sumUp(gamma_t *g){
    printf("\x1b[4%dm", 0);
    printf("\x1b[%d;%df", g->height + 1, 0);
    for (uint32_t i = 1; i <= g->players; ++i){
        printf ("\x1b[3%dmPlayer: %d; Busy Fields: %ld                                                  \x1b[0m\n", i%5+1, i, gamma_busy_fields(g, i));
    }
}

void interactiveMode(gamma_t *g, uint64_t line){
    struct termios raw;
    if(tcgetattr(STDIN_FILENO, &raw)==-1)
        exit(1);
    printf("OK %ld\n", line);
    uint32_t player = 1, x = g->width/2, y = g->height/2;
    uint32_t fieldWidth = howManyCharactersInInt(g->players);
    if (fieldWidth != 1)
        fieldWidth++;//na spację
    char *board = initializeBoard(g, fieldWidth);
    if (system("stty -echo") == -1 || system("stty raw") == -1)
        exit(1);
    while(true){
        display(g, player);
        char a = getKey();
        if (a == 'k')
            break;
        if (a != 'q'){//jeśli zapytanie nie jest błędne
            doRequest(g, a, &player, &x, &y, fieldWidth);
        }
        if (player == 0)//nie ma wolnych graczy
            break;
    }
    if (system("stty echo") == -1 || system("stty cooked") == -1)
        exit(1);
    sumUp(g);
    free(board);
}