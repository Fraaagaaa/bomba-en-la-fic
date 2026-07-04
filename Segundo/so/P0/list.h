#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node *List;
typedef struct Node *ListPos;

void list_init(List *);
bool list_insert(List *, void *);
void list_remove(List *, ListPos);
ListPos list_first(List);
ListPos list_next(ListPos);
bool list_end(ListPos);
void *list_get(ListPos);
void list_clear(List *);
ListPos list_last(List);
ListPos list_prev(List, ListPos);
int list_length(List);

#endif
