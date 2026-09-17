#ifndef P0_H
#define P0_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>   

#include "list.h"
#include "commandsp1.h"
// P0
void prompt();
int TrocearCadena(char *, char **);
void read_input(char *);
void handle_input(char *, List *, List *, struct DirParams *);
void remove_endline(char *);
void remove_file(int, List *);



#define MAX_COMMAND_LENGHT 256
#define MAXNAME 100

#endif // !P0_H
