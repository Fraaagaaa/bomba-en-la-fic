#ifndef AUXILIAR_H
#define AUXILIAR_H

#include "list.h"
#include "memoryList.h"
#include "file.h"
#include "process.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXVAR 1024

extern int var_glob;
extern int var_glob_2;
extern int var_glob_3;

void Recursiva (int);
void LlenarMemoria (void *, size_t , unsigned char );
void * ObtenerMemoriaShmget (MemList *, key_t , size_t );
void do_SharedCreate (char **, MemList *);
void do_Shared (MemList, char **);
void doSharedFree (MemList *, key_t );
void * MapearFichero (MemList *, List , char * , int );
void do_Mmap(MemList *, List , char **);
void do_SharedDelkey (char **);
void * CadenatoPointer (char *);
ssize_t LeerFichero (char *, void *, size_t );
void Cmd_ReadFile (char **);
void Do_pmap (void);
char * ConvierteModo (mode_t , char *);
char LetraTF (mode_t );
int isDirectory(char * );
void remove_endline(char *);
void Cmd_ReadFile (char **);
void Cmd_fork (char **);
int BuscarVariable (char * , char **);
int CambiarVariable(char * , char *, char **);
int ValorSenal(char * );
char *NombreSenal(int );
ssize_t EscribirFichero (char *, void *, size_t);
#endif 


