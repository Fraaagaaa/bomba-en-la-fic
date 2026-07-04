/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1:MIGUEL FRAGA PICO LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: SANTIAGO NEIRA SEJEAN LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: 11 / 03/ 24
 */

#include "dynamic_list.h"
#include <string.h>

void createEmptyList(tList *L)
{
    *L = LNULL; // Creamos una lista nueva
}

bool isEmptyList(tList L)
{
    return L == LNULL;  // Si la lista es igual a una nueva, está vacía
}

tPosL first(tList L)
{
    return L;   // El primero
}

tPosL last(tList L)
{
    tPosL p;
    for(p=L; p->next != LNULL; p = p->next);    // Comprobamos el siguiente hasta que no exista, de esta forma nos aseguramos de estar en el último
    return p;
}

tPosL next(tPosL p, tList L)
{
    return p->next; // Usamos el puntero que apunta a la siguiente posición
}

tPosL previous(tPosL p, tList L)
{
    tPosL q;
    if(p==L) // Caso de que sea la primera posición
    {
        return LNULL;
    }
    else{
        for(q=L;q->next!=p;q=q->next); // Pasamos al siguiente elemento de la lista, desde el principio, hasta que el siguiente sea el valor introducido, devolviendo así el valor anterior
        return q;
    }
}

bool createNode(tPosL *p)
{
    *p = malloc(sizeof(struct tNode));  //Reservamos memoria para el nodo
    return *p != LNULL;
}

bool insertItem (tItemL d, tPosL p, tList *L)
{
    tPosL q, r;
    if(!createNode(&q))
        return false;   // Si no se reserva memoria no podemos insertar el item
    else
    {
        q->data = d;
        q->next = LNULL;
        if(*L == LNULL) // Caso que sea el primero
        {
            *L = q;
        }
        else
        {
            if(p == LNULL)  // Si no es el primero encontramos la posición anterior al último
            {
                for(r = *L; r->next != LNULL; r = r->next);
                r->next = q;
            }
            else
            {
                if(p == *L)
                {
                    q->next = p;
                    *L = q;
                }
                else
                {
                    q->data=p->data;
                    p->data=d;
                    q->next=p->next;
                    p->next=q;
                }
            }
            return true;
        }
    }
}

void updateItem(tItemL d, tPosL p, tList *L)
{
    p->data = d;    // Igualamos la información del Item a la recibida
}

void deleteAtPosition(tPosL p, tList *L)
{
    tPosL q;
    if (p == *L)
    {
        *L = p->next;   //Si el elemento a borrar es el primero, se pone al elemento 2 de la lista como primero
    }
    else
    {
        if(p->next == LNULL)
        {
            for(q=*L; q->next != p; q = q->next);
            q->next = LNULL;
        }
        else
        {
            q = p->next;
            p->data = q->data;
            p->next = q->next;
            p = q;
        }
    }

    free(p); // Borra toda la memoria reservada
}

tPosL findItem( tUserName pName, tList L)
{
    tPosL p;

    if (isEmptyList(L))
        return LNULL;

    for (p = L; (p != LNULL); p = p->next)  // Recorremos la lista hasta que coincidan los datos
    {
        if (!(strcmp (pName, p -> data.userName))) // Comprobamos si coinciden los datos

            return p;
    }
    return LNULL;   // Si no coinciden devolvemos LNULL
}
tItemL getItem(tPosL p,tList L)
{
    return p->data; //Devolvemos el item de la posición introducida
}