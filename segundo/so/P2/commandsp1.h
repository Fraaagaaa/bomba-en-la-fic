#ifndef COMMANDSP1_H
#define COMMANDSP1_H

#include "commandsp0.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

  
typedef struct DirParams{
  int long_format;  //1=Long || 0=Short
  int follow_links; //1=Link || 0=NoLink 
  int show_hidden;  //1=Hide || 0=NoHide
  int recursion;    //2=recb || 1=reca || 0=norec
}DirParams;


void cmd_dir(char **, struct DirParams *);
void show_file_info(const char *, struct DirParams *);
void list_directory(const char *, struct DirParams *);
void print_short_format(const char *, struct stat *);
void print_long_format(const char *, struct stat *, struct DirParams *);
void list_directory_recursive(const char *, struct DirParams *);
char *ConvierteModo (mode_t, char *);
int isDirectory(char *);
char LetraTF (mode_t);

void init_params(struct DirParams *);
void cmd_create(char **);
void cmd_setdirparams(char **, struct DirParams *);
void cmd_getdirparams(char **, struct DirParams *);
void cmd_erase(char **);
void cmd_delrec(char **);
void cmd_lseek(char **, List *); 
void cmd_writestr(char **, List *);

char *jointStrings(char **, int);
bool searchInList(FileEntry **, int, List *);

#endif // !COMMANDSP1_H
