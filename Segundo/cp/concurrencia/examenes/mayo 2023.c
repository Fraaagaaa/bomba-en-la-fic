#include <pthread.h>
#include <unistd.h>

typedef struct {
    int n;
    int n_threads;
    pthread_mutex_t m;
    pthread_cond_t c;
} barrier_t;

void barrier(barrier_t *b)
{
    pthread_mutex_lock(&b->m);
    b->n_threads++;
    if(b->n == b->n_threads)
    {
        b->n_threads = 0;
        pthread_cond_broadcast(&b->c);
    }
    else
        pthread_cond_wait(&b->c,  &b->m);

    pthread_mutex_unlock(&b->m);
}

/// Ejercicio 2
#define CARS 0
#define PEDESTRIANS 1
#define SEMAPHORE_TIME 10

void do_cross();

struct crossing{
    int first_car;
    int last_car;
    int green;
    pthread_mutex_t m;
    pthread_cond_t cars_wait, peds_wait;
    int pedestrians;
    int cars;
};
int semaphore(void *ptr)
{
    struct crossing *cross = ptr;
    while (1)
    {
        pthread_mutex_lock(&cross->m);
        cross->green = (cross->green + 1) % 2;
        if(cross->green == CARS) pthread_cond_broadcast(&cross->cars_wait);
        else pthread_cond_broadcast(&cross->peds_wait);
        pthread_mutex_unlock(&cross->m);
        sleep(SEMAPHORE_TIME);
    }
}

int pedestrian(void *ptr)
{
    struct crossing *cross = ptr;
    pthread_mutex_lock(&cross->m);
    if(cross->green != PEDESTRIANS)
        pthread_cond_wait(&cross->peds_wait, &cross->m);

    // Pedestrian enter

    do_cross();


    // Pedestrian exit

    return 0;
}

int car(void *ptr)
{
    struct crossing *cross = ptr;
    pthread_mutex_lock(&cross->m);
    // car enters
    cross->last_car++;
    pthread_mutex_unlock(&cross->m);

    pthread_mutex_lock(&cross->m);
    do_cross();
    // car exits
    cross->first_car++;

    return 0;
}
