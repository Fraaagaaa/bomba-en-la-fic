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
} contadores;

typedef struct {
    volatile int *sumar;
    volatile int *restar;
} args_thread;

void *f(void *ptr)
{
    args_thread *args = (args_thread*)ptr;
    int i;
    for(i = 0; i < ITERACIONES; i++)
    {
        (*args->sumar)++;
        usleep(ESPERA);

        (*args->restar)--;
        usleep(ESPERA);
    }
    return NULL;
}

int main()
{
    pthread_t thread_a[N_THREADS];
    pthread_t thread_b[N_THREADS];
       

    contadores *contador = malloc(sizeof(contadores));
    contador->a = 0;
    contador->b = 0;
    


    args_thread *args_a = malloc(sizeof(args_thread) * N_THREADS);
    for(int i = 0; i < N_THREADS; i++)
    {
        args_a[i].sumar = &contador->a;
        args_a[i].restar = &contador->b;
        pthread_create(&thread_a[i], NULL, f, &args_a[i]);
    }

    for(int i = 0; i < N_THREADS; i++) pthread_join(thread_a[i], NULL);

    printf("a=%d", contador->a);
    free(args_a);
    free(contador);
    return 0;
}
