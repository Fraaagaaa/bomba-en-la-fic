
/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL FRAGA PICO LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: SANTIAGO NEIRA SEJEAN LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: 27 / 02 / 24
 */

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
/*
Objetivo: Añadir un usuario nuevo
Entradas:
    - L (lista a la que se va a añadir)
    - usuario (nombre del usuario)
    - categoria (categoria a la que pertenece el usuario)
Salidas:
    - Si se añade el usuario, se informará de ello
    - Si no se añade el usuario, se informará del fallo
Precondiciones:
    - El usuario no puede existir previamente
*/
{
    tItemL usuarioNuevo;        // Empleado para crear el usuario
    tItemL usuarioComprobacion; // Empleado para comprobar que no existe un usuario con ese nombre

    strcpy(usuarioComprobacion.userName , usuario); //Para comprobar si existe el usuario comparamos los nombres

    if(findItem(usuarioComprobacion.userName, *L) == LNULL) //Si el usuario no existe todavía lo añadimos
    {
        usuarioNuevo.userCategory = que_categoria(categoria);   //
        strcpy(usuarioNuevo.userName , usuario);   // Creamos el usuario nuevo con los valores que nos indica el enunciado
        usuarioNuevo.numPlay = 0;                               //

        insertItem(usuarioNuevo, LNULL, L); // Lo añadimos a la lista
        if(usuarioNuevo.userCategory)   // Dependiendo de su categoría imprimimos una u otra
            printf("* New: user %s category pro\n", usuarioNuevo.userName);
        else
            printf("* New: user %s category basic\n", usuarioNuevo.userName);
    }
    else
    {
        printf("+ Error: New not possible\n");  // Si el usuario ya existe no lo añadimos e imprimimos el error
    }
}

void Delete(tList *L, char *usuario)
/*
Objetivo: Eliminar un usuario existente
Entradas:
    - L (lista a de la que se va a eliminar)
    - usuario (nombre del usuario)
Salidas:
    - Si se elimina el usuario, se informará de ello
    - Si no se elimina el usuario, se informará del fallo
Precondiciones:
    - El usuario tiene que existir (esto incluye que la lista no esté vacía)
*/
{
    if(!isEmptyList(*L))    // Si la lista está vacía no se puede eliminar
    {
        tItemL usuario_lista;
        tPosL p = first(*L);    // Empezamos desde el principio de la lista por simplitud

        while(true) // Podría ponerse una condición distinta, pero optamos por usar breaks para verlo más claro
        {
            usuario_lista = getItem(p,*L);
            if(!strcmp(usuario, usuario_lista.userName))    // Comprobamos si estamos en el usuario correcto
            {
                deleteAtPosition(p, L); // Lo borramos
                if(usuario_lista.userCategory)  // Dependiendo de su categoría imprimimos una u otra
                    printf("* Delete: user %s category pro numplays %d\n", usuario_lista.userName, usuario_lista.numPlay);
                if(!usuario_lista.userCategory)
                    printf("* Delete: user %s category basic numplays %d \n", usuario_lista.userName, usuario_lista.numPlay);
                break;
            }
            else
            {
                if(p == last(*L))   // Si no se encuentra el usuario en toda la lista acabamos el ciclo y devolvemos el error
                {
                    printf("+ Error: Delete not possible\n");
                    break;
                }
            }
            p = next(p, *L); // Seguimos recorriendo la lista
        }
    }
    else
        printf("+ Error: Delete not possible\n");   // Si está vacía la lista devolvemos el error
}

void Stats(tList L)
{
/*
Objetivo: Mostrar la lista de usuarios
Entradas:
    - L (lista a de la que se va a mostrar)
Salidas:
    - Una lista con todos los usuarios
    - Una tabla con los usuarios pro, basic y sus respectivas reproducciones y medias
Precondiciones:
    - La lista no puede estar vacía
*/
    print_user_list(L); // Mostramos toda la lista de usuarios
    int basicCounter = 0, proCounter = 0, basicPlays = 0, proPlays = 0;
    float basicAvg, proAvg;
    tItemL usuarioSiguiente;
    tPosL p = first(L);
    if(!isEmptyList(L)) // Comprobamos que la lista no está vacía
    {
        while(p  != LNULL){
            usuarioSiguiente = getItem(p, L);

            if(usuarioSiguiente.userCategory) {proCounter++; proPlays += usuarioSiguiente.numPlay;}         // Contamos los usuarios
            if(!usuarioSiguiente.userCategory) {basicCounter++; basicPlays += usuarioSiguiente.numPlay;}    // y sumamos las reproducciones

            p = next(p, L);
        }

        if(basicPlays!=0)   // Si no se ha reproducido ninguna canción ponemos la media a 0 de forma forzada para evitar dividir entre 0
            basicAvg = basicPlays / basicCounter; // Calculamos la media
        else
            basicAvg=0;

        if(proPlays!=0)   // Si no se ha reproducido ninguna canción ponemos la media a 0 de forma forzada para evitar dividir entre 0
            proAvg = proPlays / proCounter; // Calculamos la media
        else
            proAvg=0;

        printf("Category Users Plays Average\n");                               //
        printf("Basic %5d %6d %8.2f\n", basicCounter, basicPlays, basicAvg);    // Escribimos la tabla
        printf("Pro   %5d %6d %8.2f\n", proCounter, proPlays, proAvg);          //
    }
    else    // Si la lista está vacía devolvemos el error
    {
        printf("+ Error: Stats not possible\n");
    }
}

void Upgrade(tList *L, char *nombre)
{
/*
Objetivo: Cambiar la categoría del usuario de basic a pro
Entradas:
    - L (lista a de la que se va a mostrar)
    - nombre (nombre del usuario)
Salidas:
    - Si se realiza el cambio se informa de ello
    - Si no se encuentra el usuario o el usuario ya es pro se devuelve un error informando de ello
Precondiciones:
    - El usuario existe
    - El usuario no es pro
*/
    tItemL referencia, usuario;
    tPosL p;

    strcpy(referencia.userName, nombre);    // Usamos el nombre del usuario para encontrar al usuario
    p = findItem(referencia.userName, *L);  // Encontramos la posición del usuario
    usuario = getItem(p, *L);   // Cogemos los datos del usuario

    if(!es_pro(usuario))    //Comprobamos si es basic
    {
        usuario.userCategory = pro; // Actualizamos a pro
        printf("* Upgrade: user %s category pro\n", usuario.userName);  // Informamos del cambio
        updateItem(usuario,p,L);    // Actualizamos el usuario
    }
    else
        printf("+ Error: Upgrade not possible\n");  // Si ya es pro, devolvemos el error
}

void Play(tList *L, char *usuario, char *nombrecancion)
{
/*
Objetivo: Aumentar la cantidad de reproducciones
Entradas:
    - L (lista a de la que se va a mostrar)
    - nombre (nombre del usuario)
    - nombrecancion (nombre de la canción)
Salidas:
    - Si el usuario existe se aumenta sus reproducciones y se informa de ello
    - Si no se encuentra el usuario se informa del error
Precondiciones:
    - El usuario existe
*/
    tItemL oyente;
    tSong cancion;
    tPosL p;

    strcpy(cancion.songTitle, nombrecancion);
    strcpy(oyente.userName, usuario);

    if(findItem(oyente.userName, *L) != LNULL)  //Si el usuario existe, continuamos
    {
        p = findItem(usuario, *L);  // Nos posicionamos en la posición de la lista en la que se encuentra el usuario
        oyente = getItem(p, *L);
        oyente.numPlay++;   // Le añadimos la reproducción
        printf("* Play: user %s plays song %s numplays %d\n", oyente.userName , cancion.songTitle, oyente.numPlay); // Informamos de que la ha reproducido
        updateItem(oyente,p,L); // Actualizamos las estadísticas del oyente
    }
    else    // Si el usuario no existe, devolvemos el error
        printf("+ Error: Play not possible\n");
}

tUserCategory que_categoria(char *categoria)    // Usamos esta función para saber qué categoría le corresponde al usuario
{
    if (!strcmp(categoria, "pro"))  // Si la categoría es pro, devolvemos 1, sino devolvemos 0
        return 1;

    return 0;
}

void print_user_list(tList L)   // Usamos esta función por simplitud
{
    if(!isEmptyList(L)) // Imprimimos la lista siempre que no esté vacía
    {
        tItemL usuarioSiguiente;
        for(tPosL i = first(L); i != LNULL; i = next(i, L)) // Recorremos la lista en orden
        {
            usuarioSiguiente = getItem(i, L);   // Cambiamos de usuario en cada ciclo

            // Dependiendo de la categoría imprimimos una u otra
            if(!usuarioSiguiente.userCategory) {printf("User %s category basic numplays %d\n", usuarioSiguiente.userName, usuarioSiguiente.numPlay);}
            if(usuarioSiguiente.userCategory) {printf("User %s category pro numplays %d\n", usuarioSiguiente.userName, usuarioSiguiente.numPlay);}
        }
    }
}

bool es_pro(tItemL usuario) // Función para comprobar si es pro o basic
{
    return usuario.userCategory == pro; //Si es pro devolvemos 1, sino devolvemos 0
}