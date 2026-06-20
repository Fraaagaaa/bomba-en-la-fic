Cliente
```c
While(true)
{
    Lock(M);
    if (customers < chairs)
    {
        CUSTOMERS++;
        while(free_barbers == 0)
        {
            WAIT(BARBER_BUSY, M);
        }
        FREE_BARBERS--;
        Unlock(M);
        cut_hair();
    }
    else
    {
        Unlock(M);
    }
    
}
```
