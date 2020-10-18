/** @file
 * Interfejs udostępniający tryb wsadowy.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "request.h"
#include "gamma.h"
#include "struct.h"


static void doRequest(gamma_t *g, requesttype *request, uint64_t line){
  if (request->command == 'B' || (request->command == 'I'))
    fprintf(stderr, "ERROR %ld\n", line);
  else if (request->command == 'b')
    printf("%ld\n", gamma_busy_fields(g, request->arguments[0]));
  else if (request->command == 'f')
    printf("%ld\n", gamma_free_fields(g, request->arguments[0]));
  else if (request->command == 'p')
  {
    char *board = gamma_board(g);
    if (board == NULL)
      fprintf(stderr, "ERROR %ld\n", line);
    else{
      printf("%s", board);
      free(board);
    }
  }
  else{
    bool result;
    if (request->command == 'm')
      result = gamma_move(g, request->arguments[0], request->arguments[1], request->arguments[2]);
    else if (request->command == 'g')
      result = gamma_golden_move(g, request->arguments[0], request->arguments[1],request->arguments[2]);
    else
      result = gamma_golden_possible(g, request->arguments[0]);
    if (result)
      printf("%d\n", 1);
    else 
      printf("%d\n", 0);
  }
}

void batchMode(gamma_t *g, uint64_t line, requesttype *request){
  printf("OK %ld\n", line);
  size_t n=0;
  char *str = NULL;
  line++;
  while(getline(&str, &n, stdin) != -1){
      if (!(*str == '\n' || *str == '#')){
        if (prossesRequest(str, request))
          doRequest(g, request, line);
        else
          fprintf(stderr, "ERROR %ld\n", line);
      }
      line++;
  }
  free(str);
}