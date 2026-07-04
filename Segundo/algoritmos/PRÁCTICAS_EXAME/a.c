#include <stdio.h>
#include <stdlib.h>

#define N 100 // Define N como el tamaño de la tabla de dispersión, cámbialo según sea necesario

typedef struct Nodo {
    int elemento; // Cambia el tipo de dato si el tipo de elemento es diferente
    struct Nodo* siguiente;
} Nodo;

typedef Nodo* Posicion;
typedef Posicion Lista;

typedef Lista TablaDispersión[N];

// Función para crear una lista vacía
void CrearLista(Lista* lista) {
    *lista = NULL;
}

// Función de dispersión (hash function)
int Dispersión(int elemento) {
    return elemento % N; // Ejemplo: operación módulo para la dispersión
}

// Función para buscar un elemento en una lista
Posicion BuscarLista(int elemento, Lista lista) {
    Posicion actual = lista;
    while (actual != NULL) {
        if (actual->elemento == elemento) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// Procedimiento para insertar un elemento en una lista
void InsertarLista(int elemento, Lista* lista) {
    Posicion nuevoNodo = (Posicion)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        exit(1);
    }
    nuevoNodo->elemento = elemento;
    nuevoNodo->siguiente = *lista;
    *lista = nuevoNodo;
}

// Función para buscar un elemento en la tabla de dispersión
Posicion Buscar(int elemento, TablaDispersión T) {
    int i = Dispersión(elemento);
    return BuscarLista(elemento, T[i]);
}

// Procedimiento para inicializar la tabla de dispersión
void InicializarTabla(TablaDispersión T) {
    for (int i = 0; i < N; i++) {
        CrearLista(&T[i]);
    }
}

// Procedimiento para insertar un elemento en la tabla de dispersión
void Insertar(int elemento, TablaDispersión T) {
    Posicion pos = Buscar(elemento, T); // No inserta repetidos
    if (pos == NULL) {
        int i = Dispersión(elemento);
        InsertarLista(elemento, &T[i]);
    }
}

int main() {
    TablaDispersión T;
    InicializarTabla(T);

    Insertar(10, T);
    Insertar(20, T);
    Insertar(10, T); // Este no se insertará porque ya existe

    if (Buscar(10, T) != NULL) {
        printf("Elemento 10 encontrado en la tabla.\n");
    } else {
        printf("Elemento 10 no encontrado en la tabla.\n");
    }

    if (Buscar(30, T) != NULL) {
        printf("Elemento 30 encontrado en la tabla.\n");
    } else {
        printf("Elemento 30 no encontrado en la tabla.\n");
    }

    return 0;
}
