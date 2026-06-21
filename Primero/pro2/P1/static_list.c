/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: MIGUEL FRAGA PICO LOGIN 1: miguel.fraga.pico
 * AUTHOR 2: SANTIAGO NEIRA SEJEAN LOGIN 2: s.neira
 * GROUP: 2.2
 * DATE: 27 / 02 / 24
 */
#include "static_list.h"
#include <string.h>
void createEmptyList(tList *L){
    L-> lastPos=LNULL;//se iguala la ultima posición a LNULL para crear una lista vacia
}

bool isEmptyList(tList L){
    return L.lastPos==LNULL; // si la ultima posición de la lista es igual a LNULL devuelve un 1 indicando q la lista esta vacia o un 0 si no lo esta
}

tPosL first(tList L) {
    return 0;
}//se devuelve el valor en la posición 0 de la lista
tPosL last(tList L){
    return L.lastPos;
}//se devuelve el valor en la ultima posición de la lista
tPosL next(tPosL p, tList L){
    if(p==L.lastPos){//condición que comprueba si el valor indicado es el ultimo de la lista, por tanto no puede devolver un siguiente y devuelve LNULL
        return LNULL;
    }
    else{
        return ++p;//en todos los demas casos devuelve el elemento en la siguiente posición de la lista
    }
}
tPosL previous(tPosL p, tList L){
    if (p == 0) {//misma condición que el anterior, simplemente ahora comprueba si el valor es el primero
        return LNULL;
    } else {
        return --p;//en todos los demas casos devuelve el elemento en la anterior posición de la lista
    }
}
bool insertItem(tItemL d, tPosL p, tList *L){
    if(L->lastPos==MAX_DATA-1){//se comprueba si la lista esta llena, en ese caso no se puede insertar un elemento y se devuelve un 0 o false
        return false;
    }
    else{
        L->lastPos++;//se añade una posición a la lista
        if(p==LNULL){//se comprueba si el dato se esta añadiendo en la ultima posicion
            L->datos[L->lastPos]=d;
        }
        else{
            for(tPosL i=L->lastPos;i>p;i--){//en caso de que la posición p no sea la ultima se usa un bucle for para mover todos los números a partir de esa posición hacia la derecha
                L->datos[i]=L->datos[i-1];
            }
            L->datos[p]=d;//se inserta el dato en la posición indicada
        }
        return true;//en cualquiera de los 2 casos anteriores se devuelve 1 o true ya que se puede insertar un elemento
    }
}
void deleteAtPosition(tPosL p, tList *L) {
    L->lastPos--;//se reduce el tamaño de la lista en 1
    for (p; p <= L->lastPos; p++) {//se elimina el dato en la posición remplazandolo por el siguiente en la lista y se mueven todos los elementos una posición a la izquierda
        L->datos[p] = L->datos[p + 1];
    }
}
tItemL getItem(tPosL p, tList L){
    return L.datos[p];//se devuelve el elemento en la posición p
}
void updateItem(tItemL d, tPosL p, tList *L){
    L->datos[p]=d;//se sustituye el dato en la posición p por el dato d
}
tPosL findItem(tUserName dato, tList L){
    for(int i = 0; i <= L.lastPos; i++) {//se comparan mediante un bucle for los elementos de la lista 1 por 1 y si el nombre de ususario coincide con el indicado devuelve la posicion que ocupa este
        if (strcmp(L.datos[i].userName, dato) == 0) {
            return i;
        }
    }
    return LNULL;//en caso de que no se encuentre el dato en niguna posicion se devuelve LNULL
}