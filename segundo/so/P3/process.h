#ifndef PROCESS_H
#define PROCESS_H
#include "list.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct SEN{
    char *nombre;
    int senal;
} SEN;

typedef enum PROCESSSTATUS {
    FINISHED, STOPPED, SIGNALED, ACTIVE
} PROCESSSTATUS;

typedef struct process {
    pid_t pid;
    time_t date;
    PROCESSSTATUS state;
    char *commandLine;
    int returnSignal;
    int priority;
} process;

void anadirProceso(pid_t , char *, List *);
void deleteProcessBySignal(List *, int );
void printProcessList(List *);

process *create_process(pid_t , char *, int );
bool getBackground(char **);
int getPriority(char **);
char **removeBackgroundAndPriority(char **);
char *proccessToString(PROCESSSTATUS );
void updateProcessStatus(List *);
void freeProcessList(List *);

#endif
