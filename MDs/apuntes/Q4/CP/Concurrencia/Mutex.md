Mutual - Exclusión

Los mutex se usan para el control de variables entre threads, tienen cinco funciones principales

``` c
pthread_mutex_init(pthread_mutex_t*);    // init
pthread_mutex_lock(pthread_mutex_t*);    // lock
pthread_mutex_trylock(pthread_mutex_t*); // trylock
pthread_mutex_unlock(pthread_mutex_t*);  // unlock
pthread_mutex_destroy(pthread_mutex_t*); // destroy
wait(pthread_cond_t*, pthread_mutex_t*);
```

La función `lock` comprueba si el mutex está disponible, si no lo está espera hasta que se libere el mutex, bloqueándolo antes de regresar.

La función `trylock` hace lo mismo que `lock` pero si el mutex no está disponible, regresa sin bloquearlo. Devuelve si pudo bloquear el mutex.

La función `unlock` libera el mutex que estaba previamente bloqueado, lo tiene que desbloquear el thread que lo ha bloqueado.

La función `init` inicializa el mutex.

La función `destroy` elimina el mutex independientemente de su estado.

La función `wait` espera hasta que se haga un **signal** o **broadcast** a la condición usada, cuando la función acaba el mutex va a estar bloqueado.