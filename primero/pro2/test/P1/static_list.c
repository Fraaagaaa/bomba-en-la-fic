#include "static_list.h"
#include <string.h>
void createEmptyList(tList *L)
{
    L-> lastPos=LNULL;
}

bool isEmptyList(tList L)
{
    return L.lastPos==LNULL;
}

tPosL first(tList L)
{
    return 0;
}
tPosL last(tList L)
{
    return L.lastPos;
}
tPosL next(tPosL posicion, tList L)
{
    if(p==L.lastPos)
        return LNULL;
    return ++posicion;
}
tPosL previous(tPosL posicion, tList L)
{
    if (p == 0)
        return LNULL;
    return --posicion;
}
bool insertItem(tItemL item, tPosL posicion, tList *L){
    if(L->lastPos==MAX_DATA-1)
        return false;

    L->lastPos++;
    if(posicion==LNULL)
        L->datos[L->lastPos]=item;
    else
    {
        for(tPosL posicionAuxiliar = L->lastPos; posicionAuxiliar > posicion; posicionAuxiliar--)
            L->datos[posicionAuxiliar]=L->datos[posicionAuxiliar-1];
        L->datos[posicion]=item;
    }
    return true;
}
void deleteAtPosition(tPosL posicion, tList *L)
{
    L->lastPos--;
    for (; posicion <= L->lastPos; posicion++)
        L->datos[posicion] = L->datos[posicion + 1];
}
tItemL getItem(tPosL posicion, tList L)
{
    return L.datos[posicion];
}
void updateItem(tItemL item, tPosL posicion, tList *L)
{
    L->datos[posicion]=item;
}
tPosL findItem(tUserName usuario, tList L)
{
    for(int PosicionAuxiliar = 0; PosicionAuxiliar <= L.lastPos; PosicionAuxiliar++)
        if (strcmp(L.datos[PosicionAuxiliar].userName, usuario) == 0)
            return PosicionAuxiliar;
    return LNULL;
}