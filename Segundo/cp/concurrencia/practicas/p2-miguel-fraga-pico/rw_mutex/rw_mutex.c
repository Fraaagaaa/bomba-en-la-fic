#include "rw_mutex.h"

int rw_mutex_init(rw_mutex_t *m) {
    m->active_readers = 0;
    m->someone_writting = false;
    pthread_mutex_init(&m->m, NULL);
    pthread_cond_init(&m->finished_using, NULL);

    return 0;
}

int rw_mutex_destroy(rw_mutex_t *m) {
    pthread_mutex_destroy(&m->m);
    pthread_cond_destroy(&m->finished_using);
    return 0;
}

int rw_mutex_readlock(rw_mutex_t *m) {
    pthread_mutex_lock(&m->m);
    while (m->someone_writting)
        pthread_cond_wait(&m->finished_using, &m->m);

    m->active_readers++;
    pthread_mutex_unlock(&m->m);
    return 0;
}

int rw_mutex_writelock(rw_mutex_t *m) {
    pthread_mutex_lock(&m->m);

    while (m->active_readers > 0 || m->someone_writting)
        pthread_cond_wait(&m->finished_using, &m->m);

    m->someone_writting = true;
    pthread_mutex_unlock(&m->m);
    return 0;
}

int rw_mutex_readunlock(rw_mutex_t *m) {
    pthread_mutex_lock(&m->m);
    m->active_readers--;
    if (m->active_readers == 0)
        pthread_cond_broadcast(&m->finished_using);

    pthread_mutex_unlock(&m->m);
    return 0;
}

int rw_mutex_writeunlock(rw_mutex_t *m) {
    pthread_mutex_lock(&m->m);
    m->someone_writting = false;

    pthread_cond_broadcast(&m->finished_using);

    pthread_mutex_unlock(&m->m);
    return 0;
}
