Intercambio de bucles
Fusión de arrays
Fusión de bucles
Rellenado de arrays
Partición en bloques
Distribución de datos en estructuras



# Intercambio de bucles
``` c 
double m[4][8];
for (j = 0; j < 8; j++)
    for(i = 0; i < 4; i++)
        q += m[i][j]
```

``` c 
double m[4][8]
for(i = 0; i < 4; i++) // Hacer los bubcles por filas en vez de por columnas
    for(j=0; j < 8; j++)
        q += m[i][j];
```

# Fusión de arrays
``` c 
float a[512], b[512];
for(i = 0; i < 512; i++)
    a[i] += b[i];
```

``` c 
struct reg {
    float a, b;
};
struct reg v[512];

for(i = 0; i < 512; i++)
    v[i].a += v[i].b;
```

# Fusión de bucles
``` c 
for( i = 0; i < N; i++)
    for( j = 0; j < N; j++)
        a[i][j] = 1 / b[i][j] * c [i][j];

for (i = 0; i < N; i++)
    for(j = 0; j < N; j++)
        d[i][j] = a[i][j] + c[i][j];
```

``` c 
for (i = 0; i < N; i++)
    for(j = 0; j < N; j++)
    {
        a[i][j] = 1 / b[i][j] * c [i][j];
        d[i][j] = a[i][j] + c[i][j];
    }
```

