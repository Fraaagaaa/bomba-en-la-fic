#include "list.h"

struct Node
{
    void *data;
    struct Node *next;
};

void list_init(List *l)
{
    *l = NULL;
}

bool list_insert(List *l, void *data)
{
    if (*l == NULL)
    {
        *l = malloc(sizeof(struct Node));
        if (*l == NULL) return false;
          (*l)->data = data;
        (*l)->next = NULL;
    }
    else
    {
        List current = *l;
        while (current->next != NULL) current = current->next;

        current->next = malloc(sizeof(struct Node));

        if (current->next == NULL) return false;

        current->next->data = data;
        current->next->next = NULL;
    }

    return true;
}

void list_remove(List *l, ListPos pos)
{
    if (l == NULL || *l == NULL || pos == NULL) return;

    if (pos == *l)
    {
        *l = pos->next;
        free(pos);
        return;
    }

    ListPos prev = list_prev(*l, pos);
    if (prev != NULL)
    {
        prev->next = pos->next;
        free(pos);
    }
}

ListPos list_first(List l)
{
    return l;
}

ListPos list_next(ListPos current)
{
    if (current == NULL) return NULL;
    return current->next;
}

bool list_end(ListPos p)
{
    return p == NULL;
}

void *list_get(ListPos p)
{
    if (p == NULL) return NULL;

    return p->data;
}

void list_clear(List *l)
{
    List current = *l;
    List next_node;

    while (current != NULL)
    {
        next_node = current->next;
        free(current->data);
        free(current);
        current = next_node;
    }

    *l = NULL;
}

ListPos list_last(List l)
{
    if (l == NULL) return NULL;

    List current = l;
    while (current->next != NULL) current = current->next;
    return current;
}

ListPos list_prev(List l, ListPos p)
{
    if (l == NULL || p == l) return NULL;

    List current = l;
    while (current->next != NULL && current->next != p)
        current = current->next;

    return current;
}

int list_length(List l)
{
    int len;

    List current = l;

    for(len = 0; current != NULL; current = current->next) len++;

    return len;
}

