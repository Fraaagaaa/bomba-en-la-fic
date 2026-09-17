#ifndef __PRIO_MUTEX_H__
#define __PRIO_MUTEX_H__

#include <pthread.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct prio_mutex_t {
    pthread_mutex_t m;
    pthread_cond_t *c;
    int *waiting;
    int num_prios;
    bool locked;
} prio_mutex_t;

int prio_mutex_init(prio_mutex_t *m, int num_prios);
int prio_mutex_destroy(prio_mutex_t *m);

int prio_mutex_lock(prio_mutex_t *m, int prio);
int prio_mutex_unlock(prio_mutex_t *m);
int prio_mutex_trylock(prio_mutex_t *m, int prio); // 0 if sucessful, -1 if already locked

#endif
