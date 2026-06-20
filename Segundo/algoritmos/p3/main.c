/*
 *  Feito por:
 *  Miguel Fraga Pico (miguel.fraga.pico@udc.es)
 *  Xian Cotelo Varela (x.cotelo@udc.es)
 *
 *  Grupo 3.3
 */


// CAMBIAR TEMPOS E RETURN -1 EN BUSCAR
// CAMBIAR RESOLUCION DOBLE




#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


#define TAMANO 38197
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define TAMANO2 19062

// typedef int pos;
// typedef struct entrada_ {
//     int ocupada;
//     char clave [LONGITUD_CLAVE];
//     char sinonimos [LONGITUD_SINONIMOS];
// } entrada;
//
// typedef struct
// {
//     char clave [LONGITUD_CLAVE];
//     char sinonimos [LONGITUD_SINONIMOS];
// } item;
//
// typedef entrada *tabla_cerrada;

#define N 10

typedef struct Nodo
{
    char elemento[100];
    struct Nodo* siguiente;
} Nodo;


typedef Nodo* Lista;          // Una lista es un puntero a Nodo
typedef Lista TablaDispersión[10];  // La tabla es un arreglo de listas

int dispersión(const char* elemento)
{
    int hash = 0;
    while (*elemento)
    {
        hash = (hash + *elemento) % N;
        elemento++;
    }
    return hash;
}
void inicializarTabla(TablaDispersión tabla)
{
    for (int i = 0; i < N; i++)
        tabla[i] = NULL;
}

Nodo* buscarLista(const char* elemento, Lista lista)
{
    Nodo* actual = lista;
    while (actual != NULL) {
        if (strcmp(actual->elemento, elemento) == 0)
            return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

Nodo* buscar(const char* elemento, TablaDispersión tabla)
{
    int i = dispersión(elemento);
    return buscarLista(elemento, tabla[i]);
}

void insertarLista(const char* elemento, Lista* lista)
{
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo)
    {
        printf("Error al asignar memoria.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nuevo->elemento, elemento);
    nuevo->siguiente = *lista;
    *lista = nuevo;
}

void insertar(const char* elemento, TablaDispersión tabla)
{
    int i;
    if (buscar(elemento, tabla) == NULL)
    {
        i = dispersión(elemento);
        insertarLista(elemento, &tabla[i]);
    }
}

void liberarTabla(TablaDispersión tabla)
{
    for (int i = 0; i < N; i++)
    {
        Nodo* actual = tabla[i];
        while (actual != NULL)
        {
            Nodo* temp = actual;
            actual = actual->siguiente;
            free(temp);
        }
        tabla[i] = NULL;
    }
}

void imprimirTabla(TablaDispersión tabla)
{
    int i;
    Nodo* actual;
    for (i = 0; i < N; i++)
    {
        printf("%d: ", i);
        actual = tabla[i];
        while (actual != NULL)
        {
            printf("%s; ", actual->elemento);
            actual = actual->siguiente;
        }
        printf("\n");
    }
}

int main()
{
    TablaDispersión tabla;

    // Inicializar tabla
    inicializarTabla(tabla);

    // Insertar elementos
    insertar("a", tabla);
    insertar("b", tabla);
    insertar("c", tabla);
    insertar("abc", tabla);
    insertar("bca", tabla);

    // Imprimir la tabla
    imprimirTabla(tabla);

    // Buscar elementos
    if (buscar("a", tabla)) {
        printf("Elemento 'a' encontrado.\n");
    } else {
        printf("Elemento 'a' no encontrado.\n");
    }

    if (buscar("z", tabla)) {
        printf("Elemento 'z' encontrado.\n");
    } else {
        printf("Elemento 'z' no encontrado.\n");
    }

    // Liberar memoria
    liberarTabla(tabla);

    return 0;
}

// FUNCIONES GLOBALES

void inicializar_semilla()
{
    srand(time(NULL));
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


