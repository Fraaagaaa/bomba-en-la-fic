// Practica 1 - Ejercico 5
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
    return NULL;
}

void *monitor(void *ptr)
{
    contadores *contador = (contadores*)ptr;
    int i, a, b, suma;
    for(i = 0; i < ITERACIONES; i++)
    {
        pthread_mutex_lock(&contador->mutex_a);
        pthread_mutex_lock(&contador->mutex_b);
        a = contador->a;
        b = contador->b;
        suma =  a + b;
        printf("a = %d \tb = %d\tsuma =%d \n", a, b, suma);
        pthread_mutex_unlock(&contador->mutex_b);
        pthread_mutex_unlock(&contador->mutex_a);
        usleep(ESPERA);
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
    pthread_mutex_init(&contador->mutex_a, NULL);
    pthread_mutex_init(&contador->mutex_b, NULL);
    
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


    printf("a=%d \tb=%d\t suma =%d\n", contador->a, contador->b, contador->a + contador->b);
    pthread_mutex_destroy(&contador->mutex_a);
    pthread_mutex_destroy(&contador->mutex_b);
    free(args_a);
    free(contador);
    return 0;
}
