/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL FRAGA PICO LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: SANTIAGO NEIRA SEJEAN LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: 27 / 02 / 24
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#define LNULL -1
#define MAX_DATA 25

typedef int tPosL;
typedef struct
{
    tItemL datos[MAX_DATA];
    tPosL lastPos;
} tList;
void createEmptyList(tList *L);
bool isEmptyList(tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL p, tList L);
tPosL previous(tPosL p, tList L);
bool insertItem(tItemL d, tPosL p, tList *L);
void deleteAtPosition(tPosL p, tList *L);
tItemL getItem(tPosL p, tList L);
void updateItem(tItemL d, tPosL p, tList *L);
tPosL findItem(tUserName d, tList L);
#endif
