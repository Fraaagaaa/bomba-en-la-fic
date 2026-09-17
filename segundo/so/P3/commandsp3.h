#ifndef COMMANDSP3_H
#define COMMANDSP3_H

#include "commandsp0.h"
#include "auxiliar.h"
#include "process.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/resource.h>



void cmd_uid(char **);
void cmd_envvar(char **, char **);
void cmd_showenv(char **, char **);
void cmd_fork(char **);
void cmd_exec(char **);
void cmd_jobs(List *);
void cmd_deljobs(char **, List *);
void cmd_execute_external(char **, List *);

void getUid(char **);
void setUid(char **);
void setUidLogIn(char **);
#endif // !COMMANDSP3
