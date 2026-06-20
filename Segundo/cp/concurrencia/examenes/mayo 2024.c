#include <pthread.h>

struct barrier {
    pthread_mutex_t m;
    pthread_cond_t w;
    int reached;
    int n_threads;
};

void barrier_worker(struct barrier *b);
void barrier_main(struct barrier *b);
void barrier_sync(struct barrier *b);

void barrier_worker(struct barrier *b)
{
    pthread_mutex_lock(&b->m);
    if(!b->reached)
        pthread_cond_wait(&b->w, &b->m);
    pthread_mutex_unlock(&b->m);
}

void barrier_main(struct barrier *b)
{
    pthread_mutex_lock(&b->m);
    b->reached = 1;
    pthread_cond_broadcast(&b->w);
    pthread_mutex_unlock(&b->m);
}

void barrier_sync(struct barrier *b)
{
    pthread_mutex_lock(&b->m);
    b->n_threads--;
    if(b->n_threads > 0)
        pthread_cond_wait(&b->w, &b->m);
    else
        pthread_cond_broadcast(&b->w);

    pthread_mutex_unlock(&b->m);
}
