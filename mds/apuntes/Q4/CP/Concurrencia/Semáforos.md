Los semáforos se usan para el control de variables entre threads, tienen tres funciones principales

``` C
sem_init(sem_t*, int pshared, unsigned int value);
sem_wait(sem_t*);    // P()
sem_trywait(sem_t*);
sem_post(sem_t*)     // V()
```

La función `init` inicializa la cantidad de threads  **`value`**.

La función `wait` comprueba si **value** es positivo, decrementa **value** y regresa, si **value** es 0, espera hasta que aumente.

La función `trywait` hace lo mismo que wait, pero si **value** es 0, regresa sin esperar. Devuelve si ha decrementado value.

La función `post` aumenta el valor de **value**.