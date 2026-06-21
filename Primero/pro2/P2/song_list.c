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
    // Creamos una lista vacía
    L->lastPos=NULLS;
}

bool isEmptyListS(tListS L)
{
    // Si no hay última posición la lista está vacía
    return L.lastPos==NULLS;
}

tPosS firstS(tListS L)
{
    // 0 se corresponde con el primer elemento
    return 0;
}

tPosS lastS(tListS L)
{
    return L.lastPos;
}

tPosS nextS(tPosS posicionActual, tListS L)
{
    // Si es la última posición devolvemos nulo
    if(posicionActual==L.lastPos)
        return NULLS;
    else
        return ++posicionActual;
}
tPosS previousS(tPosS posicionActual, tListS L)
{
    // Si no tiene anterior devolvemos nulo
    if (posicionActual == 0)
        return NULLS;
    else
        return --posicionActual;
}
bool insertItemS(tItemS songItem, tPosS posicionAInsertar, tListS *L)
{
    // Si no queda espacio en la lista no podemos insertar el Item
    if(L->lastPos==MAX_DATA-1)
        return false;
    else
    {
        // Si se puede añadir cambiamos la última posición de la lista
        L->lastPos++;
        if(posicionAInsertar==NULLS)
            // Lo insertamos en la última posición
            L->songItem[L->lastPos]=songItem;
        else
        {
            // Movemos los elementos posteriores a la posición en la que vamos a insertar el Item
            for(tPosS i=L->lastPos;i>posicionAInsertar;i--)
                L->songItem[i]=L->songItem[i-1];
            L->songItem[posicionAInsertar] = songItem;
        }
        return true;
    }
}

void deleteAtPositionS(tPosS posicionABorrar, tListS *L)
{
    L->lastPos--;   // Reducimos la última posición en 1

    // Copiamos los Items
    for (posicionABorrar; posicionABorrar <= L->lastPos; posicionABorrar++)
        L->songItem[posicionABorrar] = L->songItem[posicionABorrar + 1];
}

tItemS getItemS(tPosS posicionAEncontrar, tListS L)
{
    // Cogemos el Item de la posición mandada
    return L.songItem[posicionAEncontrar];
}

void updateItemS(tItemS songItem, tPosS posicionAEditar, tListS *L)
{
    // Copiamos los datos que nos mandaron en el Item correspondiente
    L->songItem[posicionAEditar]=songItem;
}

tPosS findItemS(tUserName songName, tListS L)
{
    // Recorremos la lista hasta encontrar una canción cuyo nombre coincida con el indicado
    for(int i = 0; i <= L.lastPos; i++)
        if (strcmp(L.songItem[i].songTitle, songName) == 0)
            return i;
    return NULLS;
}