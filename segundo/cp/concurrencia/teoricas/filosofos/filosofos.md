``` c
#define  N ...
#define RIGHT_FORK(I) (I)
#define LEFT_FORK(I) ((I) + 1 % N)
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
MUTEX_T FORK[N];

void filosofo(int i)
{
    while(true)
    {
        THINK();
        pick_up(I);
        EAT();
        put_down(I);
    }
}

void pick_up_con_orden(int i)
{
    int left = LEFT_FORK(I);
    int right = RIGHT_FORK(I);

    Lock(FORK[MIN(left, right]);
    Lock(FORK[MAX(left, right]);
    // Así el último no coge el tenedor de la derecha,
    // el problema de que todos cojan el de la derecha es que se puede dar un interbloqueo pq nadie es capaz de coger 2 tenedores,
    // si nos aseguramos que uno lo coge el del otro lado siempre se va a poder comer (pensar en una mesa redonda)
}


void put_down(int i)
{
    int left = LEFT_FORK(i);
    int right = RIGHT_FORK(i);

    Unlock(FORK[left]);
    Unlock(FORK[right]);
}


void pick_up_con_trylock(int i)
{
    int left = LEFT_FORK(I);
    int right = RIGHT_FORK(I);
    while(true)
    {
        Lock(FORK[right]);
        if(TRYLOCK(FORK[left] == 0)
            break;

        Unlock(FORK[right]);
        Usleep(rand()%10);      // Así cada uno espera un tiempo distinto, nos aseguramos de que cambien los timepos
    }
}
```

El problema de order en este ejrecicio es que sólo hay un filosofo que cambie de comportamiente con respecto al resto
