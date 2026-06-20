
``` c
#define N
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
    
    if(time(null) - WAIT_START[left] > TOO_LONG && phil[left] == HUNGRY) // Aquí es donde decidimos si ceder el turno al de al lado
        return false;

    if(time(null) - WAIT_START[righ] > TOO_LONG && phil[right] == HUNGRY)
        return false;

    return true;
}
```
