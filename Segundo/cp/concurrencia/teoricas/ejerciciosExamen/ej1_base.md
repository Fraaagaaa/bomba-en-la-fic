# Punte estrecho
Un puente antiguo de ancho reducido solo permite el tráfico simultáneo de vehículos en
un sentido. Se desea diseñar un sistema que controle el acceso al puente de forma que un
vehículo espere a la entrada si hay vehículos cruzando en sentido opuesto

``` c
int dirección;
mutex_t bridge;
int cars[2]; // Un contador para cada sentido de conducción
mutex_t cars_m[2]; // Un mutex para cada sentido

void enter_bridge(int dir)
{
    Lock(cars_m[dir]);
    cars[dir]++;

    if(cars[dir] == 1)
    {
        Lock(bridge);
    }

    Unlock(cars_m[dir]);
}

void exit_bridge(int dir)
{
    Lock(cars_m[dir]);
    cars[dir]--;

    if(cars[dir] == 1)
    {
        Lock(bridge);
    }

    Unlock(cars_m[dir]);
}

void *car(void *arg)
{
    int direction = (int *) *arg;
    enter_bridge(direction);
    // Cross the bridge
    exit_bridge(direction);
}
```
