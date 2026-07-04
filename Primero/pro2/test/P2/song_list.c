/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Fraga Pico LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: Santiago Neira Sejean LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: 08 / 04 / 24
 */


#include "song_list.h"
#include <string.h>

void createEmptyListS(tListS *L)
{
    L->lastPos=NULLS;
}

bool isEmptyListS(tListS L)
{
    return L.lastPos==NULLS;
}

tPosS firstS(tListS L)
{
    return 0;
}

tPosS lastS(tListS L)
{
    return L.lastPos;
}

tPosS nextS(tPosS posicionActual, tListS L)
{
    if(posicionActual==L.lastPos)
        return NULLS;
    else
        return ++posicionActual;
}
tPosS previousS(tPosS posicionActual, tListS L)
{
    if (posicionActual == 0)
        return NULLS;
    else
        return --posicionActual;
}
bool insertItemS(tItemS songItem, tPosS posicionAInsertar, tListS *L)
{
    if(L->lastPos==MAX_DATA-1)
        return false;
    else
    {
        L->lastPos++;
        if(posicionAInsertar==NULLS)
            L->songItem[L->lastPos]=songItem;
        else
        {
            for(tPosS i=L->lastPos;i>posicionAInsertar;i--)
                L->songItem[i]=L->songItem[i-1];
            L->songItem[posicionAInsertar] = songItem;
        }
        return true;
    }
}

void deleteAtPositionS(tPosS posicionABorrar, tListS *L)
{
    L->lastPos--;

    for (posicionABorrar; posicionABorrar <= L->lastPos; posicionABorrar++)
        L->songItem[posicionABorrar] = L->songItem[posicionABorrar + 1];
}

tItemS getItemS(tPosS posicionAEncontrar, tListS L)
{
    return L.songItem[posicionAEncontrar];
}

void updateItemS(tItemS songItem, tPosS posicionAEditar, tListS *L)
{
    L->songItem[posicionAEditar]=songItem;
}

tPosS findItemS(tUserName songName, tListS L)
{
    for(int i = 0; i <= L.lastPos; i++)
        if (strcmp(L.songItem[i].songTitle, songName) == 0)
            return i;
    return NULLS;
}