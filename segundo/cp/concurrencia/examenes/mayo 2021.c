#include <pthread.h>

typedef struct
{
}queue;

struct request{
    queue requests;
    pthread_mutex_t *m;
    pthread_cond_t *c;
};
int elements(queue *q);
request *remove(queue *q);

