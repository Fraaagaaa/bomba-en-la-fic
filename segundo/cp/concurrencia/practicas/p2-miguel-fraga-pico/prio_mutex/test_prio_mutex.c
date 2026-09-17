#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "prio_mutex.h"

#define NUM_PRIOS 5
#define NUM_THREADS_PER_PRIO 2
#define THREADS_PER_PRIO 1

prio_mutex_t pm;

void* test(void* arg)
{
    int prio = *(int*)arg;
    
    printf("Hilo con prioridad %d intentando bloquear el mutex\n", prio);
    prio_mutex_lock(&pm, prio);
    
    printf("Hilo con prioridad %d tiene el mutex\n", prio);
    usleep(100000);
    
    printf("Hilo con prioridad %d ha soltado el mutex\n", prio);
    prio_mutex_unlock(&pm);
    
    free(arg);
    return NULL;
}

int main()
{
    pthread_t threads[NUM_PRIOS];

    if (prio_mutex_init(&pm, NUM_PRIOS) != 0)
    {
        printf("Error inicializando prio_mutex\n");
        return 0;
    }

    // Bloqueamos el mutex para que todos los threads estén esperando a la vez
    prio_mutex_lock(&pm, 0); 

    // Lanzamos todos los threads
    for(int j = 0; j < NUM_THREADS_PER_PRIO; j++)
        for (int i = 1; i < NUM_PRIOS; i++) // Las prioridades empiezan en 1
        {
            int* p = malloc(sizeof(int));
            *p = i;
            pthread_create(&threads[i], NULL, test, p);
            usleep(10000); // Pequeña espera para asegurar el orden de llegada a la cola
        }

    printf("Todos los threads lanzados\n");

    // Dejamos que los threads empiezen a usar el mutex
    prio_mutex_unlock(&pm);

    for (int i = 1; i < NUM_PRIOS; i++)
        pthread_join(threads[i], NULL);

    prio_mutex_destroy(&pm);

    return 0;
}
