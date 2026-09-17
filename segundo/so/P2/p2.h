#ifndef P0_H
#define P0_H

#include "list.h"
#include "memoryList.h"
#include "commandsp0.h"
#include "commandsp1.h"
#include "commandsp2.h"
#include "auxiliar.h"

// P0
void prompt();
int TrocearCadena(char *, char **);
void read_input(char *);
void handle_input(char *, List *, List *, struct DirParams *, MemList *);
void remove_endline(char *);
void remove_file(int, List *);



#define MAX_COMMAND_LENGHT 256
#define MAXNAME 100

#endif // !P0_H
