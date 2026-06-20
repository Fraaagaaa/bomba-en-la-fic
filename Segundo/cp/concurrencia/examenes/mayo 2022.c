#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
typedef int request_info;

struct request{
    pthread_mutex_t *m;
    pthread_cond_t *c;
    request_info inf;
    int done;
};

// Funciones ya implementadas en otros módulos del sistema
struct request *remove_request();
void insert_request(struct request *r);
void do_io(request_info r);

void submit_request(struct request *r)
{
    r->done = 0;
    pthread_mutex_init(r->m, NULL);
    pthread_cond_init(r->c, NULL);
    insert_request(r);
}

void wait_till_done(struct request *r)
{
    pthread_mutex_lock(r->m);
    while(!r->done)
        pthread_cond_wait(r->c, r->m);
    pthread_mutex_unlock(r->m);
}

void *io_thread(struct request *ptr)
{
    while(1)
    {
        struct request *r;
        r = remove_request();
        do_io(r->inf);
        pthread_mutex_lock(r->m);
        r->done = 1;
        pthread_cond_broadcast(r->c);
        pthread_mutex_unlock(r->m);
    }
}






#define N 1000

void run_100_meters();
int secconds_since_start(void);
struct global{
    pthread_cond_t *start;
    pthread_mutex_t *m;
    bool valid_start;
    int position;
};

struct team{
    int num_runners_team;
    char *team_name;
    pthread_cond_t *wait_token[N];
    pthread_mutex_t *m;
    int next;
};

void runner(struct global *g, struct team *t, int id_runner)
{
    printf("Runner %d ready at: %d", id_runner, secconds_since_start());
    if(id_runner == 1)
    {
        pthread_mutex_lock(g->m);
        while(!g->valid_start)
            pthread_cond_wait(g->start, g->m);
        pthread_mutex_unlock(g->m);
        pthread_mutex_lock(t->m);
        t->next = 2;
    }
    else
    {
        pthread_mutex_lock(t->m);
        while(t->next != id_runner)
            pthread_cond_wait(t->wait_token[id_runner - 2], t->m);

        t->next++;
        pthread_mutex_unlock(t->m);
    }

    if(id_runner != t->num_runners_team)
    {
        pthread_cond_broadcast(t->wait_token[id_runner - 1]);
    }
    else
    {
        pthread_mutex_lock(g->m);
        int pos = g->position;
        pthread_mutex_unlock(g->m);
        printf("Team %s finished at: %d", t->team_name, secconds_since_start());
    }

    printf("Runner %d starts at: %d", id_runner, secconds_since_start());
    run_100_meters();
    printf("Runner %d finished at: %d", id_runner, secconds_since_start());
}

