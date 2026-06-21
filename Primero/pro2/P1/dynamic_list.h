/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL FRAGA PICO LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: SANTIAGO NEIRA SEJEAN  LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: ** / ** / **
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>
#define LNULL NULL

typedef struct tNode* tPosL;

struct tNode
{
    tItemL data;
    tPosL next;
};

typedef tPosL tList;


bool createNode(tPosL *p);
bool isEmptyList(tList L);
bool insertItem(tItemL d, tPosL p, tList *L);
void updateItem(tItemL d, tPosL p, tList *L);
void deleteAtPosition(tPosL p, tList *L);
void createEmptyList(tList *L);

tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL p, tList L);
tPosL previous(tPosL p, tList L);

tItemL getItem(tPosL p, tList L);
tPosL findItem(tUserName d, tList L);

#endif