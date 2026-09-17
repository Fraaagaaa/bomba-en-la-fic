#include "prio_mutex.h"

bool es_el_de_mayor_prioridad(prio_mutex_t *m, int prio);

int prio_mutex_init(prio_mutex_t *m, int num_prios)
{
    pthread_mutex_init(&m->m, NULL);
    m->locked = false;
    m->num_prios = num_prios;
    m->c = malloc(sizeof(pthread_cond_t) * num_prios);
    m->waiting = malloc(sizeof(int) * num_prios);

    if(m->c == NULL || m->waiting == NULL)
    {
        free(m->c);
        free(m->waiting);
        pthread_mutex_destroy(&m->m);
        return -1;
    }

    for(int i = 0; i < num_prios; i++)
    {
        pthread_cond_init(&m->c[i], NULL);
        m->waiting[i] = 0;
    }
    
    return 0;
}

int prio_mutex_destroy(prio_mutex_t *m)
{
    pthread_mutex_destroy(&m->m);
    for(int i = 0; i < m->num_prios; i++)
        pthread_cond_destroy(&m->c[i]);

    free(m->c);
    free(m->waiting);
    return 0;
}

int prio_mutex_lock(prio_mutex_t *m, int prio)
{
    // num_prios es constante
    if(prio < 0 || prio >= m->num_prios) // comprueba que no haya esperas de más suponiendo que no se le puede asignar a dos threads la misma prioridad
        return -1;

    pthread_mutex_lock(&m->m);

    m->waiting[prio]++;

    while(m->locked || !es_el_de_mayor_prioridad(m, prio))
        pthread_cond_wait(&m->c[prio], &m->m);

    m->waiting[prio]--;
    m->locked = true;

    pthread_mutex_unlock(&m->m);
    return 0;
}

int prio_mutex_unlock(prio_mutex_t *m)
{
    pthread_mutex_lock(&m->m);
    
    m->locked = false;

    for (int i = m->num_prios - 1; i >= 0; i--)
    {
        if (m->waiting[i] > 0)
        {
            pthread_cond_signal(&m->c[i]);
            break;
        }
    }

    pthread_mutex_unlock(&m->m);
    return 0;
}

int prio_mutex_trylock(prio_mutex_t *m, int prio)
{
    if (prio < 0 || prio >= m->num_prios)
        return -1;

    pthread_mutex_lock(&m->m);
    if(m->locked || !es_el_de_mayor_prioridad(m, prio))
    {
        pthread_mutex_unlock(&m->m);
        return -1;
    }

    m->locked = true;

    pthread_mutex_unlock(&m->m);
    return 0;
}

bool es_el_de_mayor_prioridad(prio_mutex_t *m, int prio)
{
    for(int i = prio + 1; i < m->num_prios; i++)
        if(m->waiting[i] > 0) // Si hay alguien esperando con mayor prioridad
            return false;

    return true;
}
