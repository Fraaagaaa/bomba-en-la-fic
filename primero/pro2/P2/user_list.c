/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Fraga Pico LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: Santiago Neira Sejean LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: 08 / 04 / 24
 */


#include "song_list.h"
#include "user_list.h"
#include <string.h>
#include <stdlib.h>

bool insertItemU (tItemU user, tListU *L)
{
    tPosU posicionAComprobar;   //  Posición para comprobar
    tPosU posicionCorrespondiente;  // Posición en la que se va a insertar el Item
    if(!createNodeU(&posicionAComprobar))
        return false;
    else
    {
        posicionAComprobar->data = user;     // Copiamos los datos que nos mandan
        posicionAComprobar->next = NULLU;
        if(isEmptyListU(*L))
        {
            *L = posicionAComprobar;    //Si la lista está vacía se pone en la primera posición
        }
        else if(strcmp(user.userName, (*L)->data.userName) < 0)
        {   // Buscamos su sitio correspondiente en orden alfabético
            posicionAComprobar->next = *L;
            *L = posicionAComprobar;
        }
        else
        {
            posicionCorrespondiente = findPositionU(user, *L);
            posicionAComprobar->next = posicionCorrespondiente->next;
            posicionCorrespondiente->next = posicionAComprobar;
        }
        return true;
    }
}

void deleteAtPositionU (tPosU PosicionABorrar, tListU *L)
{
    if (PosicionABorrar == *L)
    {
        *L = PosicionABorrar->next;   //Si el elemento a borrar es el primero, se pone al elemento 2 de la lista como primero
    }
    else
    {
        tPosU PosicionAuxiliar;
        if(PosicionABorrar->next == NULLU)
        {
            // Este es el caso de que borremos el último Item,
            // Recorremos la lista hasta el final para corregir el puntero al último Item
            for(PosicionAuxiliar=*L; PosicionAuxiliar->next != PosicionABorrar; PosicionAuxiliar = PosicionAuxiliar->next);
            PosicionAuxiliar->next = NULLU;
        }
        else
        {
            PosicionAuxiliar = PosicionABorrar->next;
            PosicionABorrar->data = PosicionAuxiliar->data;
            PosicionABorrar->next = PosicionAuxiliar->next;
            PosicionABorrar = PosicionAuxiliar;
        }
    }
    free(PosicionABorrar); // Borra toda la memoria reservada
}

tPosU findPositionU(tItemU user, tListU L)
{
    tPosU posicionDelItem;
    posicionDelItem = L;
    while((posicionDelItem ->next != NULLU) && (strcmp(posicionDelItem->next->data.userName, user.userName) < 0))
    {   // Recorremos la lista hasta encontrar al nombre del usuario
        posicionDelItem = posicionDelItem-> next;
    }
    return posicionDelItem;
}
tPosU findItemU (tUserName userName, tListU L)
{
    tPosU PosicionAuxiliar;

    if (isEmptyListU(L))    //Si la lista está vacía no lo vamos a encontrar
        return NULLU;

    for (PosicionAuxiliar = L; (PosicionAuxiliar != NULLU); PosicionAuxiliar = PosicionAuxiliar->next)  // Recorremos la lista hasta que coincidan los datos
    {
        if (!(strcmp (userName, PosicionAuxiliar -> data.userName))) // Comprobamos si coinciden los datos
            return PosicionAuxiliar;
    }
    return NULLU;   // Si no coinciden devolvemos LNULL
}


bool createNodeU(tPosU *p)
{
    *p = malloc(sizeof(struct tNode));  //Reservamos memoria para el nodo
    return *p != NULLU;
}

bool isEmptyListU(tListU L)
{
    return L == NULLU;  // Si la lista es igual a una nueva, está vacía
}

tItemU getItemU(tPosU poisicion, tListU L)
{
    return poisicion->data; //Devolvemos el item de la posición introducida
}

void updateItemU(tItemU user, tPosU posicionAActualizar, tListU *L)
{
    posicionAActualizar->data = user;    // Igualamos la información del Item a la recibida
}

void createEmptyListU(tListU *L)
{
    *L = NULLU; // Creamos una lista nueva
}

tPosU firstU(tListU L)
{
    return L;   // El primero
}

tPosU lastU(tListU L)
{
    tPosU posicion; //usada para recorrer la lista
    for(posicion=L; posicion->next != NULLU; posicion = posicion->next);    // Comprobamos el siguiente hasta que no exista, de esta forma nos aseguramos de estar en el último
    return posicion;
}

tPosU nextU(tPosU PosicionActual, tListU L)
{   //  Aprovechamos el puntero
    return PosicionActual->next;
}
tPosU previousU(tPosU PosicionActual, tListU L)
{
    tPosU PosicionAuxiliar;
    if(PosicionActual==L) // Caso de que sea la primera posición
    {
        return NULLU;
    }
    else
    {   // Recorremos la lista hasta encontrar la posición correspondiente
        for(PosicionAuxiliar=L;PosicionAuxiliar->next!=PosicionActual;PosicionAuxiliar=PosicionAuxiliar->next); // Pasamos al siguiente elemento de la lista, desde el principio, hasta que el siguiente sea el valor introducido, devolviendo así el valor anterior
        return PosicionAuxiliar;
    }
}