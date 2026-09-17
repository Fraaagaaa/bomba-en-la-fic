#ifndef __RW_MUTEX_H__
#define __RW_MUTEX_H__

#include <pthread.h>
#include <stdbool.h>

typedef struct rw_mutex_t {
    pthread_mutex_t m;
    pthread_cond_t finished_using;
    int active_readers;
    bool someone_writting;
} rw_mutex_t;

int rw_mutex_init(rw_mutex_t *m);
int rw_mutex_destroy(rw_mutex_t *m);

int rw_mutex_readlock(rw_mutex_t *m);
int rw_mutex_writelock(rw_mutex_t *m);
int rw_mutex_readunlock(rw_mutex_t *m);
int rw_mutex_writeunlock(rw_mutex_t *m);

#endif
