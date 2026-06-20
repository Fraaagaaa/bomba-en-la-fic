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

void shell(int v[], int n);
void test();
void inicializar_semilla();
void aleatorio(int v[], int n);
void ascendente(int v[], int n);
void esta_ordenado(int v[], int tamano);
void descendente(int v[], int n);
double microsegundos();
void ordenar(void algoritmo(int v[], int n), int n, void crear_vector(int v[], int n));
void start();
void tabla(int i);
void print_vec(int k, int v[]);
double cotas(int c, int n);

int main()
{
    inicializar_semilla();
    start();
    //test();
    return 0;
}

void start()
{
    const int tamano[7] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int i, j;
    for (i = 0; i < 3; i++)
    {
        tabla(i);
        switch (i)
        {
            case 0:
                for (j = 0; j < 7; j++)
                    {ordenar(shell, tamano[j], ascendente);} break;
            case 1:
                for (j = 0; j < 7; j++)
                    {ordenar(shell, tamano[j], descendente);} break;
            case 2:
                for (j = 0; j < 7; j++)
                    {ordenar(shell, tamano[j], aleatorio);} break;
            default: break;
        }
    }
}

void shell(int v[], int n)
{
    int incremento = n, tmp, i, j;
    bool seguir;
    do
    {
        incremento = incremento / 2;
        for (i = incremento; i < n; i++)
        {
            tmp = v[i];
            j = i;
            seguir = true;
            while(j-incremento >= 0 && seguir)
                if(tmp < v[j-incremento])
                {
                    v[j] = v[j-incremento];
                    j -= incremento;
                }
                else
                    seguir = false;
            v[j] = tmp;
        }
    }
    while(incremento > 1);
}

void tabla(int i)
{
    printf("\n--------------------------------------------"
           "--------------------------------\n\n");
    switch(i)
    {
        case 0: printf("Vector ascendente, ordenación por shell\n");
                printf("|    N    |     t(n)      |     t(n)/n    |"
           "t(n)/(n*log(n))|     t(n)/n²     |\n"); break;
        case 1: printf("Vector descendente, ordenación por shell\n");
                printf("|    N    |      t(n)       |   t(n)/n    |"
                "t(n)/(n*log(n))|     t(n)/n²     |\n");break;
        case 2: printf("Vector aleatorio, ordenación por shell\n");
                printf("|    N    |      t(n)      |    t(n)/n    |"
                "t(n)/(n*log(n))|     t(n)/n²     |\n"); break;
        default: break;
    }
}

void ordenar(void algoritmo(int v[], int n), int n, void crear_vector(int v[], int n))
{
    int i, *v = malloc(n * sizeof(int)); double t1, t, t_v1, t_v;
    double c1 = cotas(0, n), c2 = cotas(1, n), c3 = cotas(2, n);
    if(v == NULL) exit(1);

    crear_vector(v, n);
    t_v1 = microsegundos(); crear_vector(v, n); t_v = microsegundos() - t_v1;
    t1 = microsegundos();
    algoritmo(v, n);
    t = microsegundos() - t1 - t_v;
    if(t < 500)
    {
        t_v1 = microsegundos();
        for(i = 0; i < 1000; i++)
            crear_vector(v, n);
        t_v = microsegundos() - t_v1;

        t1 = microsegundos();
        for(i = 0; i < 1000; i++)
        {
            crear_vector(v, n);
            algoritmo(v, n - 1);
        }
        t = (microsegundos() - t1 - t_v) / 1000;
        printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n", n, t, t/c1, t/c2, t/c3);
    }
    else
        printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n", n, t, t/c1, t/c2, t/c3);
    free(v);
}

double cotas(int c, int n)
{               
    switch(c)
    {
        case 0: return n;
        case 1: return (n*log(n));
        default: return pow(n ,2);
    }
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

// test

void test()
{
    int n = 17;
    int v[n]; int w[n];
    printf("\n-----------------------------------TEST"
                 "--------------------------------------\n");


    printf("\n-----------------------------------Shell"
                 "--------------------------------------\n");

    printf("\n\nOrdenación por inserción con inicialización ordenada\n\n");
    ascendente(w, 20); print_vec(20, w);
    shell(w, 20); print_vec(20, w);

    printf("\n\nOrdenación por inserción con inicialización descendente\n\n");
    descendente(w, 20); print_vec(20, w);
    shell(w, 20); print_vec(20, w);

    printf("\\nnOrdenación por insercion con inicialización aleatoria\n\n");
    aleatorio(v, 20); print_vec(20, v);
    shell(v, 20); print_vec(20, v);
}

void esta_ordenado(int v[], int tamano)
{
    int i;
    for(i = 0; i < tamano - 1; i++)
        if(v[i] > v[i + 1])
        {
            printf("\nordenado? 0\nordenando...\n");
            return;
        }
    printf("\nordenado? 1\n");
}

// tipos de ordenaciones de vectores

void aleatorio(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = rand() % 100;
}

void ascendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
}

// Print vector

void print_vec(int k, int v[])
{
    int i;
    for(i = 0; i < k-1; i++)
        printf("%d, ", v[i]);
    printf("%d", v[k - 1]);
    esta_ordenado(v, k);
}