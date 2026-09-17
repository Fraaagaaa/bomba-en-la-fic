#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rec_mutex.h"

#define TAM 10
#define THREADS 4
#define ITERACIONES 10000
#define MIN(X, Y) (X) < (Y) ? (X) : (Y)
#define MAX(X, Y) (X) > (Y) ? (X) : (Y)

int array[TAM];
rec_mutex_t mutexes[TAM];

void* intercambio(void* arg)
{
    for (int i = 0; i < ITERACIONES; i++)
    {
        int x = rand() % TAM;
        int y = rand() % TAM;

        // Para evitar que un thread intente bloquear el X e Y
        // y otro thread intente bloquear Y y X
        // y se cree un interbloqueo
        
        int first = MIN(x, y);
        int second = MAX(x, y);

        rec_mutex_lock(&mutexes[first]);
        rec_mutex_lock(&mutexes[second]);

        // Intercambio
        int temp = array[first];
        array[first] = array[second];
        array[second] = temp;

        rec_mutex_unlock(&mutexes[second]);
        rec_mutex_unlock(&mutexes[first]);
    }
    return NULL;
}

int main()
{
    pthread_t threads[THREADS];
    int i;
    srand(time(NULL));

    // Inicializa los arrays con números de 0 en adelante
    for (int i = 0; i < TAM; i++)
    {
        array[i] = i;
        rec_mutex_init(&mutexes[i]);
    }

    printf("Estado inicial:\t");
    for (i = 0; i < TAM; i++)
        printf("%d ", array[i]);

    for (i = 0; i < THREADS; i++)
        pthread_create(&threads[i], NULL, intercambio, NULL);

    // esperar por los threads
    for (i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("\nEstado final:\t");
    int sum = 0;
    for (i = 0; i < TAM; i++)
    {
        printf("%d ", array[i]);
        sum += array[i];
        rec_mutex_destroy(&mutexes[i]);
    }

    printf("\n");
    return 0;
}
