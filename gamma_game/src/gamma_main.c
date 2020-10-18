/** @file
 * Funkcja główna gry gamma.
 *
 * @author Krystian Markowski <km418413@mimuw.edu.pl>
 */
#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "batch_mode.h"
#include "interactive_mode.h"
#include "request.h"

static bool prossesString(char *str, uint64_t line, requesttype *request){
  if (!(*str == '\n' || *str == '#')){
    if (prossesRequest(str, request) && (request->command == 'B' || request->command == 'I')){
      gamma_t *g = gamma_new(request->arguments[0], request->arguments[1], request->arguments[2], request->arguments[3]);
      if (g != NULL){
        if(request->command == 'B')
          batchMode(g, line, request);
        else if (request->command == 'I')
          interactiveMode(g, line);
        gamma_delete(g);
        return true;
      }
    }
    fprintf(stderr, "ERROR %ld\n", line);
  }
  return false;
} 

int main(){
  size_t n=0;
  char *str = NULL;
  uint64_t line = 1;
  requesttype *request = calloc(1, sizeof(requesttype));
  if (request == NULL)
    exit(1);
  
  while(getline(&str, &n, stdin) != -1)
  {
    if (prossesString(str, line, request))
      break;
    line++;
  }
  free(str);
  free(request);

  return 0;

}



    