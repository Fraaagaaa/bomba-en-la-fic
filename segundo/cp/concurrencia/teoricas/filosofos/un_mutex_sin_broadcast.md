
``` c
#define N
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
