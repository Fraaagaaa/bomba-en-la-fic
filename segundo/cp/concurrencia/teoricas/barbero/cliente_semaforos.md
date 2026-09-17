Cliente
```c
SEM_T CUSTOMERS = 0;
SEM_T FREE_CHAIRS = CHAIRS;
While(true)
{
    if(TRYP(FREE_CHAIRS) == 0) // Intenta hacer un P, pero no lo hace, solo devuelve si se podria hacer
    {
        V(CUSTOMERS); // +1
        P(BARBERS); // Si no hay barberos, esperamos, sino restamos uno y seguimos
        V(FREE_CHAIRS);
        cut_hair();
    }
}
```
