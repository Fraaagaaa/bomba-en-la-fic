#ifndef P0_H
#define P0_H

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

#include "list.h"

void prompt();
int TrocearCadena(char * cadena, char * trozos[]);
void read_input(char *input);
void handle_input(char *input, List *history, List *opened_files);
void remove_endline(char *string);
void cmd_close (char *args[], List *opened_files);
void cmd_dup (char *args[], List *opened_files);
void cmd_authors(char **args);
void cmd_chdir(char **args);
void cmd_getcwd(char **args);
void cmd_date(char **args);
void cmd_hours(char **args);
void cmd_getpid(char **args);
void cmd_unknown(char **args);
void add_command_to_history(char *command, List *history);
void cmd_historic(char **args, List *history);
void cmd_open (char * args[], List *opened_files);
void add_file(int fd, char *filename, List *opened_files, int mode);
void cmd_infosys(char **args);
void cmd_listopen(List *opened_files);
void remove_file(int fd, List *opened_files);
void cmd_help(char **args);
#define MAX_COMMAND_LENGHT 256
#define MAXNAME 100

typedef struct{
    int fd;
    char filename[256];
    int mode;
} FileEntry;

#endif // !P0_H
#define P0_H
