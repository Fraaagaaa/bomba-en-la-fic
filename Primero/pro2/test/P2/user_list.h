/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Fraga Pico LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: Santiago Neira Sejean LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: 08 / 04 / 24
 */

#ifndef USER_LIST_H
#define USER_LIST_H

#include "types.h"
#include "song_list.h"
#include <stdbool.h>

typedef struct tNode* tPosU;
typedef tPosU tListU;

#define NULLU NULL

typedef struct{
    tUserName userName;
    tUserCategory userCategory;
    tListS songList;
    tPlayTime totalPlayTime;
}tItemU;


struct tNode
{
    tItemU data;
    tPosU next;
};

void    createEmptyListU(tListU *L);
bool    createNodeU(tPosU *p);
void    deleteAtPositionU (tPosU PosicionABorrar, tListU *L);
tPosU   findPositionU(tItemU user, tListU L);
tPosU   findItemU (tUserName userName, tListU L);
tPosU   firstU(tListU L);
tItemU  getItemU(tPosU poisicion, tListU L);
bool    insertItemU (tItemU User, tListU *L);
bool    isEmptyListU(tListU L);
tPosU   lastU(tListU L);
tPosU   nextU(tPosU PosicionActual, tListU L);
tPosU   previousU(tPosU PosicionActual, tListU L);
void    updateItemU(tItemU user, tPosU posicionAActualizar, tListU *L);

#endif
