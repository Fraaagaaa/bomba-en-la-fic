/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Fraga Pico LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: Santiago Neira Sejean LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: 08 / 04 / 24
 */

#ifndef SONG_LIST_H
#define SONG_LIST_H

#include "types.h"

/* Write your code here... */
#define NULLS -1
#define MAX_DATA 25

typedef int tPosS;
typedef tSong tItemS;
typedef struct
{
    tItemS songItem[MAX_DATA];
    tPosS lastPos;
}tListS;

void createEmptyListS(tListS *L);
bool isEmptyListS(tListS L);
tPosS firstS(tListS L);
tPosS lastS(tListS L);
tPosS nextS(tPosS posicionActual, tListS L);
tPosS previousS(tPosS posicionActual, tListS L);
bool insertItemS(tItemS songItem, tPosS posicionAInsertar, tListS *L);
void deleteAtPositionS(tPosS posicionABorrar, tListS *L);
tItemS getItemS(tPosS posicionAEncontrar, tListS L);
void updateItemS(tItemS songItem, tPosS posicionAEditar, tListS *L);
tPosS findItemS(tUserName songName, tListS L);

#endif