// Practica 1 - Ejercico 5
// Miguel Fraga Pico

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define ITERACIONES 10000
#define ESPERA 10
#define N_THREADS 2

void *f(void *ptr);

typedef struct contadores{
  volatile int a;
  volatile int b;
  volatile bool activo;
  pthread_mutex_t mutex_a;
  pthread_mutex_t mutex_b;
} contadores;

typedef struct {
    volatile int *sumar;
    volatile int *restar;
    contadores *contador;
} args_thread;

void *f(void *ptr)
{
    args_thread *args = (args_thread*)ptr;
    int i;
    for(i = 0; i < ITERACIONES; i++)
    {
        pthread_mutex_lock(&args->contador->mutex_a);
        pthread_mutex_lock(&args->contador->mutex_b);
        (*args->sumar)++;
        usleep(ESPERA);

        (*args->restar)--;
        usleep(ESPERA);
        pthread_mutex_unlock(&args->contador->mutex_b);
        pthread_mutex_unlock(&args->contador->mutex_a);
    }
    (*args->contador).activo = false;
    return NULL;
}

void *monitor(void *ptr)
{
    contadores *contador = (contadores*)ptr;
    int a, b, suma;
    while(contador->activo)
    {
        pthread_mutex_lock(&contador->mutex_a);
        pthread_mutex_lock(&contador->mutex_b);

        a = contador->a;
        b = contador->b;
        suma =  a + b;

        printf("a = %d\tb = %d\tsuma =%d \n", a, b, suma);

        pthread_mutex_unlock(&contador->mutex_b);
        pthread_mutex_unlock(&contador->mutex_a);
    }
    return NULL;
}

int main()
{
    pthread_t thread_a[N_THREADS];
    pthread_t thread_b[N_THREADS];
    pthread_t thread_monitor;
       

    contadores *contador = malloc(sizeof(contadores));
    contador->a = 0;
    contador->b = 0;
    contador->activo = true;
    pthread_mutex_init(&contador->mutex_a, NULL);
    pthread_mutex_init(&contador->mutex_b, NULL);
    
    args_thread *args_heap = malloc(sizeof(args_thread) * N_THREADS);
    args_thread args_stack[N_THREADS];
    // pthread_create(pthread_t *, NULL, func, args)
    pthread_create(&thread_monitor, NULL, monitor, contador);
    for(int i = 0; i < N_THREADS; i++)
    {
        // Estes threads suman en A y restan en B
        args_heap[i].sumar = &contador->a;
        args_heap[i].restar = &contador->b;
        args_heap[i].contador = contador;
        pthread_create(&thread_a[i], NULL, f, &args_heap[i]);

        // Estes threads suman en B y restan en A
        args_stack[i].sumar = &contador->b;
        args_stack[i].restar = &contador->a;
        args_stack[i].contador = contador;
        pthread_create(&thread_b[i], NULL, f, &args_stack[i]);
    }

    for(int i = 0; i < N_THREADS; i++) pthread_join(thread_a[i], NULL);
    for(int i = 0; i < N_THREADS; i++) pthread_join(thread_b[i], NULL);
    pthread_join(thread_monitor, NULL);


    printf("a=%d \tb=%d\t suma =%d\n", contador->a, contador->b, contador->a + contador->b);
    pthread_mutex_destroy(&contador->mutex_a);
    pthread_mutex_destroy(&contador->mutex_b);
    free(args_heap);
    free(contador);
    return 0;
}
