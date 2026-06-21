/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "user_list.h"

#define MAX_BUFFER 255

void New(tUserName nombre, char *categoria, tListU *LU);
void Delete(tUserName nombre, tListU *LU);
void Upgrade(tUserName nombre, tListU *LU);
void Add(tUserName nombre, tSongTitle titulo, tListU LU);
void Stats(tListU LU);
bool categoriaString(char *string);
void Remove(int maxtime, tListU *LU);
void Play(tUserName nombre, tSongTitle titulo, tPlayTime playtime, tListU *LU);

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListU *LU) {

    printf("********************\n");
    switch (command) {
        case 'N':
            printf("%s %c: user %s category %s\n", commandNumber, command, param1, param2);
            New(param1, param2, LU);
            break;
        case 'D':
            printf("%s %c: user %s\n", commandNumber, command, param1);
            Delete(param1, LU);
            break;
        case 'A':
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2);
            Add(param1, param2, *LU);
            break;
        case 'U':
            printf("%s %c: user %s\n", commandNumber, command, param1);
            Upgrade(param1, LU);
            break;
        case 'P':
            printf("%s %c: user %s song %s minutes %s\n", commandNumber, command, param1, param2, param3);
            Play(param1, param2, atoi(param3), LU);
            break;
        case 'S':
            printf("%s %c:\n", commandNumber, command);
            Stats(*LU);
            break;
        case 'R':
            printf("%s %c: maxtime %s\n", commandNumber, command, param1);
            Remove(atoi(param1), LU);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    tListU LU;
    createEmptyListU(&LU);

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, &LU);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

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

void New(tUserName nombre, char *categoria, tListU *LU)
{
    if(findItemU(nombre, *LU) == NULLU)
    {
    tItemU usuario;
    strcpy(usuario.userName, nombre);
    usuario.totalPlayTime = 0;
    usuario.userCategory = categoriaString( categoria);
    tListS listaDelUsuario;
    createEmptyListS(&listaDelUsuario);
    usuario.songList = listaDelUsuario;

    insertItemU(usuario, LU);

    if(!usuario.userCategory)
        printf("* New: user %s category basic\n", nombre);
    else
        printf("* New: user %s category pro\n", nombre);
    }
    else
        printf("+ Error: New not possible\n");
}

void Delete(tUserName nombre, tListU *LU)
{
    if(findItemU(nombre, *LU) != NULLU)
    {
        tItemU usuario;
        usuario = getItemU(findItemU(nombre, *LU), *LU);
        while(!isEmptyListS(usuario.songList))
            deleteAtPositionS(firstS(usuario.songList), &usuario.songList);


        if(!usuario.userCategory)
            printf("* Delete: user %s category basic totalplaytime %d\n", nombre, usuario.totalPlayTime );
        else
            printf("* Delete: user %s category pro totalplaytime %d\n", nombre, usuario.totalPlayTime );
        deleteAtPositionU(findItemU(nombre, *LU), LU);
    }
    else
        printf("+ Error: Delete not possible\n");
}

void Upgrade(tUserName nombre, tListU *LU)
{
    if(findItemU(nombre, *LU) != NULLU)
    {
        tItemU usuario = getItemU(findItemU(nombre, *LU), *LU);
        if(usuario.userCategory)
            printf("+ Error: Upgrade not possible\n");
        else
        {
            usuario.userCategory = 1;
            updateItemU(usuario, findItemU(nombre, *LU), LU);
            printf("* Upgrade: user %s category pro\n", nombre);
        }
    }
    else
        printf("+ Error: Upgrade not possible\n");
}

void Add(tUserName nombre, tSongTitle titulo, tListU LU)
{
    if(isEmptyListU(LU))
    {
        printf("+ Error: Add not possible\n");
        return;
    }
    if(findItemU(nombre, LU) != NULLU)
    {
        tItemU usuario = getItemU(findItemU(nombre, LU), LU);
        tItemS cancion;
        strcpy(cancion.songTitle, titulo);
        cancion.playTime = 0;
        if(findItemS(titulo, usuario.songList) == NULLS)
        {
            insertItemS(cancion, NULLS, &usuario.songList);
            updateItemU(usuario, findItemU(nombre, LU), &LU);
            printf("* Add: user %s adds song %s\n", nombre, titulo);
        }
        else
            printf("+ Error: Add not possible\n");
    }
    else
        printf("+ Error: Add not possible\n");
}

void Play(tUserName nombre, tSongTitle titulo, tPlayTime playtime, tListU *LU)
{
    if (isEmptyListU(*LU) || playtime <= 0)
    {
        printf("+ Error: Play not possible\n");
        return;
    }
    if (findItemU(nombre, *LU) != NULLU)
    {
        tItemU usuario = getItemU(findItemU(nombre, *LU), *LU);

        if(isEmptyListS(usuario.songList))
        {
            printf("+ Error: Play not possible\n");
            return;
        }
        usuario.totalPlayTime += playtime;

        tItemS cancion = getItemS(findItemS(titulo, usuario.songList), usuario.songList);
        cancion.playTime += playtime;

        // Bastante seguro de que primero se debe cambiar la canción, puede que de igual.
        updateItemS(cancion, findItemS(titulo, usuario.songList), &usuario.songList);
        updateItemU(usuario, findItemU(nombre, *LU), LU);
        printf("* Play: user %s plays song %s playtime %d totalplaytime %d\n", nombre, titulo, playtime,
               usuario.totalPlayTime);
    }
    else
    {
        printf("+ Error: Play not possible\n");
        return;
    }
}

void Stats(tListU LU)
{
    if(isEmptyListU(LU))
    {
        printf("+ Error: Stats not possible\n");
        return;
    }

    int usuariosBasic = 0;
    int usuariosPro = 0;
    float mediaBasic;
    float mediaPro;
    int playTimeBasic = 0;
    int playTimePro = 0;

    tItemU usuario;

    for(tPosU posicionUsuario = firstU(LU); posicionUsuario != NULLU; posicionUsuario = posicionUsuario->next)
    {
        usuario = getItemU(posicionUsuario, LU);
        if(usuario.userCategory)
        {
            usuariosPro++;
            playTimePro += usuario.totalPlayTime;
            printf("User %s category pro totalplaytime %d\n", usuario.userName, usuario.totalPlayTime);
        }
        else
        {
            usuariosBasic++;
            playTimeBasic += usuario.totalPlayTime;
            printf("User %s category basic totalplaytime %d\n", usuario.userName, usuario.totalPlayTime);
        }

        if(!isEmptyListS(usuario.songList))
        {
            for(tPosS posicionCancion = firstS(usuario.songList); posicionCancion != NULLS; posicionCancion = nextS(posicionCancion, usuario.songList))
            {
                tItemS cancion;
                cancion = getItemS(posicionCancion, usuario.songList);
                printf("Song %s playtime %d\n", cancion.songTitle, cancion.playTime);
            }
        }
        else
            printf("No songs\n");
        printf("\n");
    }
    if(usuariosBasic)
        mediaBasic = (float)playTimeBasic / usuariosBasic;
    else
        mediaBasic = 0;
    if(usuariosPro)
        mediaPro = (float)playTimePro / usuariosPro;
    else
        mediaPro = 0;


    printf("Category  Users  TimePlay  Average\n");
    printf("Basic     %5d %9d %8.2f\n", usuariosBasic, playTimeBasic, mediaBasic);
    printf("Pro       %5d %9d %8.2f\n", usuariosPro, playTimePro, mediaPro);
}

void Remove(int maxtime, tListU *LU)
{
    if(isEmptyListU(*LU) || maxtime < 0)
    {
        printf("+ Error: Remove not possible\n");
        return;
    }
    int usuariosEliminados = 0;
    for(tPosU posicion = firstU(*LU); posicion != NULLU; posicion = posicion->next)
    {
        tItemU usuario = getItemU(posicion, *LU);
        if(!usuario.userCategory && usuario.totalPlayTime >= maxtime)
        {
            usuariosEliminados++;
            printf("Removing user %s totalplaytime %d\n", usuario.userName, usuario.totalPlayTime);
            deleteAtPositionU(posicion, LU);
        }
    }
    if(!usuariosEliminados)
        printf("+ Error: Remove not possible\n");
}

bool categoriaString(char *string)
{
    return !strcmp(string, "pro");
}