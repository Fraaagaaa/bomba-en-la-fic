N filósofos en una mesa circular para cenar. Entre cada dos filósofos hay un cubierto, N cubiertos en total. Un filósofo puede estar pensando o comiendo, para comer necesita usar los dos cubiertos que tiene a la izquierda y derecha. La solución debe evitar que ningún filósofo sufra inanición.


## Solución con un mutex por tenedor usando order
``` c
#define  N 10
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
        Usleep(rand()%10);      // Así cada uno espera un tiempo distinto,
                                // nos aseguramos de que cambien los timepos
    }
}
```

El problema de order en esta solución es que sólo hay un filosofo que cambie de comportamiento con respecto al resto

## Solución con signal

``` c
#define N 10
int phil[N]
#define THINKING 0
#define EATING 1
#define RIGHT_PHIL(I) ((I) - 1 % N)
#define LEFT_PHIL(I)  ((I) + 1 % N)
mutex_t M;
cond_t NO_FORKS[N];     // Una condición por filósofo

void pick_up(int i)
{
    int left = LEFT_PHIL(I);
    int right = RIGHT_PHIL(I);

    Lock(M);
    while(PHIL[left]== EATING || PHILL[RIGHT] == EATING)
    {
        wait(NO_FORKS[i], M);  // Unlock de M mientras esperamos
    }
    
    phil[i] = EATING;
    Unlock(M);
}

void put_down(int i)
{
    int left = LEFT_PHIL(I);
    int right = RIGHT_PHIL(I);

    Lock(M);
    phil[i] = THINKING;
    
    singal(NO_FROKS[left]);     // Despertamos a los dos que están al lado
    singal(NO_FROKS[right]);    // Son los que realmente afectan
    unlock(M);
}
```

El problema de esta solución es que cabe la posibilidad de que un filósofo nunca coma si los filósofos que están a su lado cogen los tenedores siempre antes que él.

``` c
#define N 10
int phil[N]
#define THINKING 0
#define EATING 1
#define HUNGRY 2
#define RIGHT_PHIL(I) ((I) - 1 % N)
#define LEFT_PHIL(I)  ((I) + 1 % N)
mutex_t M;
cond_t NO_FORKS[N];     // Una condición por filósofo
TIME_T WAIT_START[N];     // Para que los filosofoso de los lados no cojan los tenedores todo el rato y que el de el medio no los pille nunca
#define MAX_TIME_WITHOUT_EATING 100

void pick_up(int i)
{
    int left = LEFT_PHIL(I);
    int right = RIGHT_PHIL(I);

    Lock(M);
    WAIT_START[i] = time(NULL);
    phil[i] = HUNGRY;
    while(!can_i_eat())
    {
        wait(NO_FORKS[i], M);  // Unlock de M mientras esperamos
    }
    
    phil[i] = EATING;
    Unlock(M);
}

void put_down(int i)
{
    int left = LEFT_PHIL(I);
    int right = RIGHT_PHIL(I);

    Lock(M);
    phil[i] = THINKING;
    
    singal(NO_FROKS[left]);     // Despertamos a los dos que están al lado
    singal(NO_FROKS[right]);    // Son los que realmente afectan
    unlock(M);
}

bool can_i_eat() // Espera por si alguno de sus lados llevam mucho sin comer
{
    int left = LEFT_PHIL(I);
    int right = RIGHT_PHIL(I);

    if(phil[left] == EATING || phil[right] == EATING)
        return false;
    
    if(time(null) - WAIT_START[I] > MAX_TIME_WITHOUT_EATING)
        return true;
    
    if(time(null) - WAIT_START[left] > TOO_LONG && phil[left] == HUNGRY)
	    // Aquí es donde decidimos si ceder el turno al de al lado
        return false;

    if(time(null) - WAIT_START[righ] > TOO_LONG && phil[right] == HUNGRY)
        return false;

    return true;
}
```