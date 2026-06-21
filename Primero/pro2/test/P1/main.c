#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif
bool es_pro(tItemL usuario);
void print_user_list(tList L);
void Stats(tList L);
void Delete(tList *L, char *usuario);
void New(tList *L, char *usuario, char *categoria);
void Upgrade(tList *L, char *nombre);
void Play(tList *L, char *usuario, char *nombrecancion);
tUserCategory que_categoria(char *categoria);

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList*L)
{
    printf("********************\n");
    switch (command)
    {
        case 'N':
            printf("%s %c: ", commandNumber, command);
            printf("user %s category %s\n", param1, param2);
            New(L,param1,param2);
            break;
        case 'D':
            printf("%s %c: user %s\n", commandNumber, command, param1);
            Delete(L,param1);
            break;
        case 'U':
            printf("%s %c: user %s\n", commandNumber, command, param1);
            Upgrade(L,param1);
            break;
        case 'P':
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2);
            Play(L,param1, param2);
            break;
        case 'S':
            printf("%s %c: \n", commandNumber, command);
            Stats(*L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename)
{
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");
    tList L;
    createEmptyList(&L);
    if (f != NULL)
    {

        while (fgets(buffer, MAX_BUFFER, f))
        {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, &L);
        }

        fclose(f);

    }
    else
    {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args)
{

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}


void New(tList *L, char *usuario, char *categoria)
{
    tItemL usuarioNuevo;
    tItemL usuarioComprobacion;

    strcpy(usuarioComprobacion.userName , usuario);

    if(findItem(usuarioComprobacion.userName, *L) == LNULL)
    {
        usuarioNuevo.userCategory = que_categoria(categoria);
        strcpy(usuarioNuevo.userName , usuario);
        usuarioNuevo.numPlay = 0;

        insertItem(usuarioNuevo, LNULL, L);
        if(usuarioNuevo.userCategory)
            printf("* New: user %s category pro\n", usuarioNuevo.userName);
        else
            printf("* New: user %s category basic\n", usuarioNuevo.userName);
    }
    else
    {
        printf("+ Error: New not possible\n");
    }
}

void Delete(tList *L, char *usuario)
{
    if(!isEmptyList(*L))
    {
        tItemL usuario_lista;
        tPosL p = first(*L);

        while(true)
        {
            usuario_lista = getItem(p,*L);
            if(!strcmp(usuario, usuario_lista.userName))
            {
                deleteAtPosition(p, L);
                if(usuario_lista.userCategory)
                    printf("* Delete: user %s category pro numplays %d\n", usuario_lista.userName, usuario_lista.numPlay);
                if(!usuario_lista.userCategory)
                    printf("* Delete: user %s category basic numplays %d \n", usuario_lista.userName, usuario_lista.numPlay);
                break;
            }
            else
            {
                if(p == last(*L))
                {
                    printf("+ Error: Delete not possible\n");
                    break;
                }
            }
            p = next(p, *L);
        }
    }
    else
        printf("+ Error: Delete not possible\n");
}

void Stats(tList L)
{
    print_user_list(L);
    int basicCounter = 0, proCounter = 0, basicPlays = 0, proPlays = 0;
    float basicAvg, proAvg;
    tItemL usuarioSiguiente;
    tPosL p = first(L);
    if(!isEmptyList(L))
    {
        while(p  != LNULL){
            usuarioSiguiente = getItem(p, L);

            if(usuarioSiguiente.userCategory) {proCounter++; proPlays += usuarioSiguiente.numPlay;}
            if(!usuarioSiguiente.userCategory) {basicCounter++; basicPlays += usuarioSiguiente.numPlay;}

            p = next(p, L);
        }

        if(basicPlays!=0)
            basicAvg = basicPlays / basicCounter;
        else
            basicAvg=0;

        if(proPlays!=0)
            proAvg = proPlays / proCounter;
        else
            proAvg=0;

        printf("Category Users Plays Average\n");
        printf("Basic %5d %6d %8.2f\n", basicCounter, basicPlays, basicAvg);
        printf("Pro   %5d %6d %8.2f\n", proCounter, proPlays, proAvg);
    }
    else
    {
        printf("+ Error: Stats not possible\n");
    }
}

void Upgrade(tList *L, char *nombre)
{
    tItemL referencia, usuario;
    tPosL p;

    strcpy(referencia.userName, nombre);
    p = findItem(referencia.userName, *L);
    usuario = getItem(p, *L);

    if(!es_pro(usuario))
    {
        usuario.userCategory = pro;
        printf("* Upgrade: user %s category pro\n", usuario.userName);
        updateItem(usuario,p,L);
    }
    else
        printf("+ Error: Upgrade not possible\n");
}

void Play(tList *L, char *usuario, char *nombrecancion)
{
    tItemL oyente;
    tSong cancion;
    tPosL p;

    strcpy(cancion.songTitle, nombrecancion);
    strcpy(oyente.userName, usuario);

    if(findItem(oyente.userName, *L) != LNULL)
    {
        p = findItem(usuario, *L);
        oyente = getItem(p, *L);
        oyente.numPlay++;
        printf("* Play: user %s plays song %s numplays %d\n", oyente.userName , cancion.songTitle, oyente.numPlay);
        updateItem(oyente,p,L);
    }
    else
        printf("+ Error: Play not possible\n");
}

tUserCategory que_categoria(char *categoria)
{
    if (!strcmp(categoria, "pro"))
        return pro;

    return basic;
}

void print_user_list(tList L)
{
    if(!isEmptyList(L))
    {
        tItemL usuarioSiguiente;
        for(tPosL i = first(L); i != LNULL; i = next(i, L))
        {
            usuarioSiguiente = getItem(i, L);

            if(!usuarioSiguiente.userCategory) {printf("User %s category basic numplays %d\n", usuarioSiguiente.userName, usuarioSiguiente.numPlay);}
            if(usuarioSiguiente.userCategory) {printf("User %s category pro numplays %d\n", usuarioSiguiente.userName, usuarioSiguiente.numPlay);}
        }
    }
}

bool es_pro(tItemL usuario)
{
    return usuario.userCategory == pro;
}