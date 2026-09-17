#include <pthread.h>

typedef struct{
} queue;

struct customer{
    pthread_cond_t c;
};

struct super{
    queue *q;
    pthread_mutex_t *m;
    pthread_cond_t *cajeros;
};
