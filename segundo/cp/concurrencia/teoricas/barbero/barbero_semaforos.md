Barbero
```c
SEM_T BARBERS = 0;
While(true)
{
    V(BARBERS); // +1
    P(CUSTOMERS); // Si hay clientes resta 1, sino espera
    cut_hair();
}
```
