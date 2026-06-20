#include "sem.h"

int sem_init(sem_t *s, int value)
{
    s->count = value;

    pthread_mutex_init(&s->m, NULL);
    pthread_cond_init(&s->cond, NULL);

    return 0;
}

int sem_destroy(sem_t *s)
{
    pthread_mutex_destroy(&s->m);
    pthread_cond_destroy(&s->cond);

    return 0;
}

int sem_p(sem_t *s)
{
    pthread_mutex_lock(&s->m);
    while(s->count <= 0)
        pthread_cond_wait(&s->cond, &s->m);

    s->count--;
    pthread_mutex_unlock(&s->m);

    return 0;
}

int sem_v(sem_t *s)
{
    pthread_mutex_lock(&s->m);
    s->count++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->m);

    return 0;
}

int sem_tryp(sem_t *s) { // 0 on sucess, -1 if already locked
    pthread_mutex_lock(&s->m);

    if(s->count > 0)
    {
        s->count--;
        pthread_mutex_unlock(&s->m);
        return 0;
    }

    pthread_mutex_unlock(&s->m);
    return -1;
}
