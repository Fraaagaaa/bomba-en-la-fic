// Practica 1 - Ejercico 4
// Miguel Fraga Pico

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define ITERACIONES 1000
#define ESPERA 10
#define N_THREADS 20

void *f(void *ptr);

typedef struct contadores{
  volatile int a;
  volatile int b;
  pthread_mutex_t mutex_global;
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
        pthread_mutex_lock(&args->contador->mutex_global);
        (*args->sumar)++;
        usleep(ESPERA);

        usleep(ESPERA);
        (*args->restar)--;
        pthread_mutex_unlock(&args->contador->mutex_global);
    }
    return NULL;
}

void *monitor(void *ptr)
{
    contadores *contador = (contadores*)ptr;
    int i, suma;
    for(i = 0; i < ITERACIONES; i++)
    {
        pthread_mutex_lock(&contador->mutex_global);
        suma =  contador->a + contador->b;
        printf("a = %d \tb = %d\tsuma =%d \n", contador->a, contador->b, suma);
        usleep(ESPERA);
        pthread_mutex_unlock(&contador->mutex_global);
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
    pthread_mutex_init(&contador->mutex_global, NULL);
    

    args_thread *args_a = malloc(sizeof(args_thread) * N_THREADS);
    args_thread args_b[N_THREADS];
    pthread_create(&thread_monitor, NULL, monitor, contador);
    for(int i = 0; i < N_THREADS; i++)
    {
        args_a[i].sumar = &contador->a;
        args_a[i].restar = &contador->b;
        args_a[i].contador = contador;
        pthread_create(&thread_a[i], NULL, f, &args_a[i]);

        args_b[i].sumar = &contador->b;
        args_b[i].restar = &contador->a;
        args_b[i].contador = contador;
        pthread_create(&thread_b[i], NULL, f, &args_b[i]);
    }

    for(int i = 0; i < N_THREADS; i++) pthread_join(thread_a[i], NULL);
    for(int i = 0; i < N_THREADS; i++) pthread_join(thread_b[i], NULL);
    pthread_join(thread_monitor, NULL);


    printf("a=%d b=%d\n", contador->a, contador->b);
    pthread_mutex_destroy(&contador->mutex_global);
    free(args_a);
    free(contador);
    return 0;
}
