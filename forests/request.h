#ifndef REQUEST_H
#define REQUEST_H
#include <stdbool.h>

extern void processRequest(char *request);
extern bool ignore (char *request);
extern bool isWhiteCharacter(char a);

#endif /* REQUEST_H */