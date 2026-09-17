# Punte estrecho
Un puente antiguo de ancho reducido solo permite el tráfico simultáneo de vehículos en
un sentido. Se desea diseñar un sistema que controle el acceso al puente de forma que un
vehículo espere a la entrada si hay vehículos cruzando en sentido opuesto

``` c
int dirección;
mutex_t bridge;
int cars[2]; // Un contador para cada sentido de conducción
mutex_t cars_m[2]; // Un mutex para cada sentido
cond_t BRIDGE_IN_USE;

void enter_bridge(int dir)
{
    int op = (dir + 1) % 2
    Lock(bridge);
    while(cars[op] > 0)
    {
        wait(BRIDGE_IN_USE, bridge);
    }
    cars[dir]++;
    Unlock(bridge);
}

void exit_bridge(int dir)
{
    Lock(bridge);
    cars[dir]--;

    if(cars[dir] == 0) // comprobamos 0 pq acabamos de restarnos
    {
        broadcast(BRIDGE_IN_USE);
    }
    Unlock(bridge);
}

void *car(void *arg)
{
    int direction = (int *) *arg;
    enter_bridge(direction);
    // Cross the bridge
    exit_bridge(direction);
}
```
