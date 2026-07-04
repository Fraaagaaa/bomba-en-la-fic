#include "dynamic_list.h"
#include <string.h>

void createEmptyList(tList *L)
{
    *L = LNULL;
}

bool isEmptyList(tList L)
{
    return L == LNULL;
}

tPosL first(tList L)
{
    return L;
}

tPosL last(tList L)
{
    tPosL posicion;
    for(posicion=L; posicion->next != LNULL; posicion = posicion->next)
        ;
    return posicion;
}

tPosL next(tPosL poisicion, tList L)
{
    return posicion->next;
}

tPosL previous(tPosL poisicion, tList L)
{
    tPosL posicionauxiliar;
    if(poisicion == L)
        return LNULL;
    for(posicionauxiliar = L; posicionauxiliar->next != poisicion; posicionauxiliar = posicionauxiliar->next);
    return posicionauxiliar;
}

bool createNode(tPosL *poisicion)
{
    *poisicion = malloc(sizeof(struct tNode));
    return *poisicion != LNULL;
}

bool insertItem (tItemL item, tPosL poisicion, tList *L)
{
    tPosL posicionAInsertar, posicionAuxiliar;
    if(!createNode(&posicionAInsertar))
        return false;
    else
    {
        posicionAInsertar->data = item;
        posicionAInsertar->next = LNULL;
        if(*L == LNULL)
            *L = posicionAInsertar;
        else
        {
            if(poisicion == LNULL)
            {
                for(posicionAuxiliar = *L; posicionAuxiliar->next != LNULL; posicionAuxiliar = posicionAuxiliar->next);
                posicionAuxiliar->next = posicionAInsertar;
            }
            else
            {
                if(poisicion == *L)
                {
                    posicionAInsertar->next = poisicion;
                    *L = posicionAInsertar;
                }
                else
                {
                    posicionAInsertar->data=poisicion->data;
                    poisicion->data=item;
                    posicionAInsertar->next=poisicion->next;
                    poisicion->next=posicionAInsertar;
                }
            }
            return true;
        }
    }
}

void updateItem(tItemL usuario, tPosL posicion, tList *L)
{
    posicion->data = usuario;
}

void deleteAtPosition(tPosL posicion, tList *L)
{
    tPosL posicionAuxiliar;
    if (posicion == *L)
        *L = posicion->next;
    else
    {
        if(posicion->next == LNULL)
        {
            for(posicionAuxiliar = *L; posicionAuxiliar->next != posicion; posicionAuxiliar = posicionAuxiliar->next);
            posicionAuxiliar->next = LNULL;
        }
        else
        {
            posicionAuxiliar = posicion->next;
            posicion->data = posicionAuxiliar->data;
            posicion->next = posicionAuxiliar->next;
            posicion = posicionAuxiliar;
        }
    }

    free(p);
}

tPosL findItem( tUserName nombre, tList L)
{
    tPosL posicion;

    if (isEmptyList(L))
        return LNULL;

    for (posicion = L; (posicion != LNULL); posicion = posicion->next)
        if (!(strcmp(nombre, posicion->data.userName)))
            return posicion;

    return LNULL;
}
tItemL getItem(tPosL posicion,tList L)
{
    return posicion->data;
}