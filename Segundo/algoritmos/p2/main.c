/*
Realizado por: Xián Cotelo Varela   x.cotelo@udc.es
               Miguel Fraga Pico    miguel.fraga.pico@udc.es
Grupo: 3.3
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

void ord_ins(int *v, int n);
void ord_rap(int *v, int iz, int dr);
void ord_rap_aux(int *v, int iz, int dr);
void test();
void ordear();
void inicializar_semilla();
void aleatorio(int *v, int n);
void ascendente(int *v, int n);
void esta_ordenado(int *v, int tamano);
void descendente(int *v, int n);
double microsegundos();
void ordenar_aleatorio(bool algoritmo, int n);
void ordenar_asc(bool algoritmo, int n);
void ordenar_desc(bool algoritmo, int n);
void tabla(int i);

int main()
{
    inicializar_semilla();
    ordear();
    //test();
    return 0;
}

void ordear()
{
    const int tamano[7] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int i, j;
    for (i = 0; i < 6; i++)
    {
        tabla(i);
        switch (i)
        {
            case 0:
                for (j = 0; j < 7; j++)
                {ordenar_aleatorio(true, tamano[j]);} break;
            case 1:
                for (j = 0; j < 7; j++)
                    {ordenar_aleatorio(false, tamano[j]);} break;
            case 2:
                for (j = 0; j < 7; j++)
                    {ordenar_desc(true, tamano[j]);} break;
            case 3:
                for (j = 0; j < 7; j++)
                    {ordenar_desc(false, tamano[j]);} break;
            case 4:
                for (j = 0; j < 7; j++)
                    {ordenar_asc(true, tamano[j]);} break;
            case 5:
                for (j = 0; j < 7; j++)
                    {ordenar_asc(false, tamano[j]);} break;
            default: break;
        }
    }
}

void tabla(int i)
{
    printf("\n--------------------------------------------"
           "--------------------------------\n\n");
    switch(i)
    {
        case 0: printf("Vector aleatorio, ordenación por inserción\n");
                printf("|    N    |     t(n)      |   t(n)/n¹·⁸   |"
           "    t(n)/n²  |     t(n)/n²·²     |\n"); break;
        case 1: printf("Vector aleatorio, quick sort\n");
                printf("|    N    |     t(n)      |   t(n)/n⁰·⁵   |"
                "    t(n)/n¹·¹  |    t(n)/n²·²    |\n");break;
        case 2: printf("Vector descendente, ordenación por inserción\n");
                printf("|    N    |     t(n)      |    t(n)/n    |"
                "    t(n)/n²     |    t(n)/n²·³⁵   |\n"); break;
        case 3: printf("Vector descendente, quick sort\n");
                printf("|    N    |     t(n)      |  t(n)/log(n)  |"
                "   t(n)/n¹·⁰⁵⁵ |    t(n)/n²·⁵    |\n"); break;
        case 4: printf("Vector ordenado, ordenación por inserción\n");
                printf("|    N    |      t(n)     |   t(n)/n²·³   |"
                "     t(n)/n    |     t(n)/n⁰·⁵   |\n"); break;
        case 5: printf("Vector ordenado, quick sort\n");
                printf("|    N    |     t(n)      |   t(n)/n²·¹   |"
                "     t(n)/n    |  t(n)/n*log(n)  |\n"); break;
        default: break;
    }

}

void ordenar_aleatorio(bool algoritmo, int n)
{
    int i, *v; double t1, t2, t;
    v = malloc(n * sizeof(int));
    if(v == NULL) exit(1);

    t1 = microsegundos(); aleatorio(v, n);
    if(algoritmo) ord_ins(v, n - 1); else ord_rap(v, 0, n - 1);
    t2 = microsegundos(); t = t2 - t1;
    if(t < 500)
        if(algoritmo)
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {aleatorio(v, n);   ord_ins(v, n - 1);}
            t2 = microsegundos();
            t = (t2 - t1) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n, 1.8), t/pow(n,2), t/pow(n, 2.2));
        }
        else
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {aleatorio(v, n);   ord_rap(v, 0, n - 1);}
            t2 = microsegundos();
            t = (t2 - t1) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n,0.5), t/pow(n,1.1), t/pow(n, 2.2));
        }
    else
    {
        if (algoritmo)
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n, 1.8), t/pow(n,2), t/pow(n, 2.2));
        else
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n,0.5), t/pow(n,1.1), t/pow(n, 2.2));
    }
    free(v);
}

void ordenar_desc(bool algoritmo, int n)
{
    int i, *v; double t1, t2, t;

    v = malloc(n * sizeof(int));
    if(v == NULL) exit(1);
    t1 = microsegundos();
    descendente(v, n);
    if(algoritmo) ord_ins(v, n - 1); else ord_rap(v, 0, n - 1);
    t2 = microsegundos();
    t = t2 - t1;
    if(t < 500)
        if(algoritmo)
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {descendente(v, n);   ord_ins(v, n - 1);}
            t2 = microsegundos();
            t = (t2 - t1) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/n, t/pow(n,2), t/pow(n,2.35));
        }
        else
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {descendente(v, n);   ord_rap(v, 0, n - 1);}
            t2 = microsegundos();
            t = (t2 - t1) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/log(n), t/pow(n, 1.055), t/pow(n,2.5));
        }
    else
        if(algoritmo)
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
                , n, t, t/n, t/pow(n,2), t/pow(n,2.35));
        else
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/log(n), t/pow(n, 1.055), t/pow(n,2.5));
    free(v);
}



void ordenar_asc(bool algoritmo, int n)
{
    int i, *v; double t1, t2, t;
    v = malloc(n * sizeof(int));
    if(v == NULL)exit(1);
    t1 = microsegundos();
    ascendente(v, n);
    if(algoritmo) ord_ins(v, n - 1); else ord_rap(v, 0, n - 1);
    t2 = microsegundos();
    t = t2 - t1;
    if(t < 500)
        if(algoritmo)
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {ascendente(v, n);   ord_ins(v, n - 1);}
            t2 = microsegundos();
            t = (t2 - t1) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(2,3), t/n, t/pow(n,0.5));
        }
        else
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {ascendente(v, n);   ord_rap(v, 0, n - 1);}
            t2 = microsegundos();
            t = (t2 - t1) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n,2.1), t/n, t/log(n));

        }
    else
        if (algoritmo)
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(2,3), t/n, t/pow(n,0.5));
        else
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n,2.1), t/n, t/log(n));
    free(v);
}

// medición de tempos

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla()
{
    srand(time(NULL));
}

// algoritmos

void ord_ins(int *v, int n)
{
    int i, x, j;
    for(i = 2; i < n; i++)
    {
        x = v[i];
        for(j = i -1; j>= 0 && v[j] > x; j--)
            v[j+1] = v[j];
        v[j + 1] = x;
    }
}

void ord_rap(int *v, int iz, int dr)
{
    ord_rap_aux(v, iz, dr);
}

void ord_rap_aux(int *v, int iz, int dr)
{
    int pivote, aux, j, i, x;
    if (iz < dr)
    {
        x = iz + rand() % (dr - iz + 1), i = iz + 1, j = dr;
        pivote = v[x];

        aux = v[iz];
        v[iz] = v[x];
        v[x] = aux;

        while (i <= j)
        {
            while (i <= j && v[i] <= pivote)
                i++;
            while (i <= j && v[j] > pivote)
                j--;

            if (i <= j)
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;

                i++;
                j--;
            }

        }

        aux = v[iz];
        v[iz] = v[j];
        v[j] = aux;

        ord_rap_aux(v, iz, j - 1);
        ord_rap_aux(v, j + 1, dr);
    }
}


// test

void test()
{
    int i;
    int *v = malloc(17 * sizeof(int));
    int *w = malloc(10 * sizeof(int));

    if(v == NULL || w == NULL)
        return;

    printf("\n-----------------------------------TEST--------------------------------------\n");
    printf("\nOrdenación por insercion con inicialización aleatoria\n");
    aleatorio(v, 17);
    for(i = 0; i < 16; i++)
        printf("%d, ", v[i]);
    printf("%d", v[16]);
    esta_ordenado(v, 17);

    ord_rap(v, 0, 16);
    for(i = 0; i < 16; i++)
        printf("%d, ", v[i]);
    printf("%d", v[16]);
    esta_ordenado(v, 17);


    descendente(w, 10);
    printf("\nOrdenación por inserción con inicialización descendente\n");
    for(i = 0; i < 9; i++)
        printf("%d, ", w[i]);
    printf("%d", w[9]);
    esta_ordenado(w, 10);

    ord_rap(w, 0, 9);
    for(i = 0; i < 9; i++)
        printf("%d, ", w[i]);
    printf("%d", w[9]);
    esta_ordenado(w, 10);

    free(v); free(w);
}

void esta_ordenado(int *v, int tamano)
{
    int i;
    for(i = 0; i < tamano - 1; i++)
        if(v[i] > v[i + 1])
        {
            printf("\nordenado? 0\nordenando...\n");
            return;
        }
    printf("\nOrdenado 1\n");
}

// tipos de ordenaciones de vectores

void aleatorio(int *v, int n)
{
    int i, m = 2*n+1;
    for (i = 0; i < n; i++)
        v[i] = rand() % m - n;
}

void ascendente(int *v, int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int *v, int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
}
