#include "song_list.h"
#include "user_list.h"
#include <string.h>
#include <stdlib.h>

bool insertItemU (tItemU user, tListU *L)
{
    tPosU posicionAComprobar;
    tPosU posicionCorrespondiente;
    if(!createNodeU(&posicionAComprobar))
        return false;
    else
    {
        posicionAComprobar->data = user;
        posicionAComprobar->next = NULLU;
        if(isEmptyListU(*L))
        {
            *L = posicionAComprobar;
        }
        else if(strcmp(user.userName, (*L)->data.userName) < 0)
        {
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
        *L = PosicionABorrar->next;
    }
    else
    {
        tPosU PosicionAuxiliar;
        if(PosicionABorrar->next == NULLU)
        {
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
    free(PosicionABorrar);
}

tPosU findPositionU(tItemU user, tListU L)
{
    tPosU posicionDelItem;
    posicionDelItem = L;
    while((posicionDelItem ->next != NULLU) && (strcmp(posicionDelItem->next->data.userName, user.userName) < 0))
    {
        posicionDelItem = posicionDelItem-> next;
    }
    return posicionDelItem;
}
tPosU findItemU (tUserName userName, tListU L)
{
    tPosU PosicionAuxiliar;

    if (isEmptyListU(L))
        return NULLU;

    for (PosicionAuxiliar = L; (PosicionAuxiliar != NULLU); PosicionAuxiliar = PosicionAuxiliar->next)
    {
        if (!(strcmp (userName, PosicionAuxiliar -> data.userName)))
            return PosicionAuxiliar;
    }
    return NULLU;
}


bool createNodeU(tPosU *p)
{
    *p = malloc(sizeof(struct tNode));
    return *p != NULLU;
}

bool isEmptyListU(tListU L)
{
    return L == NULLU;
}

tItemU getItemU(tPosU poisicion, tListU L)
{
    return poisicion->data;
}

void updateItemU(tItemU user, tPosU posicionAActualizar, tListU *L)
{
    posicionAActualizar->data = user;
}

void createEmptyListU(tListU *L)
{
    *L = NULLU;
}

tPosU firstU(tListU L)
{
    return L;
}

tPosU lastU(tListU L)
{
    tPosU posicion;
    for(posicion=L; posicion->next != NULLU; posicion = posicion->next);
    return posicion;
}

tPosU nextU(tPosU PosicionActual, tListU L)
{
    return PosicionActual->next;
}
tPosU previousU(tPosU PosicionActual, tListU L)
{
    if(PosicionActual==L)
        return NULLU;

    tPosU PosicionAuxiliar;
    for(PosicionAuxiliar=L;PosicionAuxiliar->next!=PosicionActual;PosicionAuxiliar=PosicionAuxiliar->next);
    return PosicionAuxiliar;
}