#include "rec_mutex.h"

int rec_mutex_init(rec_mutex_t *m)
{
    pthread_mutex_init(&m->m, NULL);
    pthread_cond_init(&m->c, NULL);

    m->count = 0;
    m->owner = -1;

    return 0;
}

int rec_mutex_destroy(rec_mutex_t *m)
{
    pthread_mutex_destroy(&m->m);
    pthread_cond_destroy(&m->c);

    return 0;
}

int rec_mutex_lock(rec_mutex_t *m)
{
    pthread_t self = pthread_self();

    pthread_mutex_lock(&m->m);

    if(m->locked && pthread_equal(m->owner, self))
    {
        m->count++;
        pthread_mutex_unlock(&m->m);
        return 0;
    }

    // Aquí ya sé que no soy el owner
    while(m->locked)
    {
        pthread_cond_wait(&m->c, &m->m);
    }

    m->locked = 1;
    m->owner = self;
    m->count = 1;

    pthread_mutex_unlock(&m->m);
    return 0;
}

int rec_mutex_unlock(rec_mutex_t *m)
{
    pthread_t self = pthread_self();

    pthread_mutex_lock(&m->m);

    if(!m->locked || !pthread_equal(m->owner, self))
    {
        pthread_mutex_unlock(&m->m);
        return -1;
    }

    m->count--;

    if(m->count == 0)
    {
        m->locked = 0;
        pthread_cond_signal(&m->c);
    }

    pthread_mutex_unlock(&m->m);
    return 0;
}

int rec_mutex_trylock(rec_mutex_t *m)
{
    pthread_t self = pthread_self();

    pthread_mutex_lock(&m->m);

    if(m->locked)
    {
        if(pthread_equal(m->owner, self))
        {
            m->count++;
            pthread_mutex_unlock(&m->m);
            return 0;
        }
        else
        {
            pthread_mutex_unlock(&m->m);
            return -1;
        }
    }

    m->locked = 1;
    m->owner = self;
    m->count = 1;

    pthread_mutex_unlock(&m->m);
    return 0;
}
