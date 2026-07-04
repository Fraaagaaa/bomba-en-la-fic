#ifndef COMMANDSP0_H
#define COMMANDSP0_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <unistd.h>


#include "list.h"
#include "file.h"
#include "auxiliar.h"

void cmd_close (char **, List *);
void cmd_dup (char **, List *);
void cmd_authors(char **);
void cmd_chdir(char **);
void cmd_getcwd(char **);
void cmd_date(char **);
void cmd_hour(char **);
void cmd_getpid(char **);
void cmd_unknown(char **);
void cmd_historic(char **, List *);
void cmd_open(char **, List *);
void cmd_infosys(char **);
void cmd_listopen(List *);
void cmd_help(char **);
void add_command_to_history(char *, List *);
void init_standard_fds(List *);
char* modetostring(int);


void remove_file(int , List *);


#endif // !COMMANDS_H
