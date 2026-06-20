Barbero
```c
While(true)
{
    Lock(M);
    FREE_BARBERS++;
    while(CUSTOMERS == 0)
    {
        WAIT(NOCUSTOMERS, M);
    }
    CUSTOMERS--;
    SIGNAL(BARBER_BUSY);
    Unlock(M);
    cut_hair();
}
```
