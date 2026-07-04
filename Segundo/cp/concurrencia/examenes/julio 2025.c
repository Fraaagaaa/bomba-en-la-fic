#include <pthread.h>

struct wait_row{
    int waiting;
    pthread_cond_t *c; // va a ser el siguiente en fila
    pthread_mutex_t *m;
};

void act();
void person(struct wait_row *wr)
{
    pthread_cond_t *cur;
    pthread_cond_t *next;
    pthread_cond_init(next, NULL);
    pthread_mutex_lock(wr->m);
    if(wr->c != NULL) // Hay que esperar
    {
        wr->waiting++;
        cur = wr->c;
        wr->c = next;
        pthread_cond_wait(wr->c, wr->m);
        wr->waiting--;
    }
    pthread_mutex_unlock(wr->m);
    act();
    pthread_mutex_lock(wr->m);
    if(wr->waiting > 0) pthread_cond_signal(next);
    else wr->c = NULL;
    pthread_mutex_unlock(wr->m);
}
