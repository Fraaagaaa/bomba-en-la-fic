#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include "options.h"
#include "sem.h"

#define CHAIRS 5

sem_t BARBERS;
sem_t CUSTOMERS;
sem_t FREE_CHAIRS;
bool finished;

pthread_mutex_t print_mutex;

struct thread_data
{
    int id;
    struct options *opt;
};

void* barbero(void* arg)
{
    struct thread_data *data = (struct thread_data *)arg;

    while(!finished)
    {
        sem_v(&BARBERS);
        sem_p(&CUSTOMERS);

        pthread_mutex_lock(&print_mutex);
        printf("[B%d]:\t Cortando pelo.\n", data->id);
        pthread_mutex_unlock(&print_mutex);

        usleep(data->opt->cut_time);

        pthread_mutex_lock(&print_mutex);
        printf("[B%d]:\t Terminó el corte.\n", data->id);
        pthread_mutex_unlock(&print_mutex);
    }
    return NULL;
}

void* cliente(void* arg)
{
    struct thread_data *data = (struct thread_data *)arg;

    if(sem_tryp(&FREE_CHAIRS) == 0)
    {
        pthread_mutex_lock(&print_mutex);
        printf("[C%d]:\t Entra a la barbería.\n", data->id);
        pthread_mutex_unlock(&print_mutex);

        sem_v(&CUSTOMERS);
        sem_p(&BARBERS);
        sem_v(&FREE_CHAIRS);

        pthread_mutex_lock(&print_mutex);
        printf("[C%d]:\t Me están cortando el pelo.\n", data->id);
        pthread_mutex_unlock(&print_mutex);
    } 
    else
    {
        pthread_mutex_lock(&print_mutex);
        printf("[C%d]:\t Sala llena.\n", data->id);
        pthread_mutex_unlock(&print_mutex);
    }

    free(data);
    return NULL;
}

int main (int argc, char **argv)
{
    struct options opt;

    opt.barbers = 5;
    opt.customers = 1000;
    opt.cut_time  = 3000;

    read_options(argc, argv, &opt);

    sem_init(&BARBERS, 0);
    sem_init(&CUSTOMERS, 0);
    sem_init(&FREE_CHAIRS, CHAIRS);

    pthread_mutex_init(&print_mutex, NULL);

    pthread_t b_threads[opt.barbers];
    pthread_t c_threads[opt.customers];

    for (int i = 0; i < opt.barbers; i++)
    {
        struct thread_data *b_data = malloc(sizeof(struct thread_data));
        b_data->id = i + 1;
        b_data->opt = &opt;
        pthread_create(&b_threads[i], NULL, barbero, b_data);
    }

    for (int i = 0; i < opt.customers; i++)
    {
        struct thread_data *c_data = malloc(sizeof(struct thread_data));
        c_data->id = i + 1;
        c_data->opt = &opt;
        pthread_create(&c_threads[i], NULL, cliente, c_data);
        usleep(100000); 
    }

    for (int i = 0; i < opt.customers; i++)
        pthread_join(c_threads[i], NULL);

    finished = true;

    for (int i = 0; i < opt.barbers; i++)
        pthread_join(b_threads[i], NULL);


    printf("\nTodos los clientes han sido procesados.\n");
    return 0;
}
