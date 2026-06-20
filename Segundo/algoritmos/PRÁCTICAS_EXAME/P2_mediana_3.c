#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

#define UMBRAL 3

void ord_ins(int v[], int n);
void ord_rap(int v[], int n);
void ord_rap_aux(int v[], int iz, int dr);
void mediana3(int v[], int iz, int dr);
void test();
void ordear();
void inicializar_semilla();
void aleatorio(int v[], int n);
void ascendente(int v[], int n);
void esta_ordenado(int v[], int tamano);
void descendente(int v[], int n);
double microsegundos();
void ordenar_aleatorio(bool algoritmo, int n);
void ordenar_asc(bool algoritmo, int n);
void ordenar_desc(bool algoritmo, int n);
void tabla(int i);
void print_vec(int k, int v[]);

int main()
{
    inicializar_semilla();
    test();
    ordear();
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
                "     t(n)/n    |      t(n)/n²    |\n"); break;
        case 5: printf("Vector ordenado, quick sort\n");
                printf("|    N    |     t(n)      |   t(n)/n⁰·⁵   |"
                "     t(n)/n    |     t(n)/n²·¹   |\n"); break;
        default: break;
    }

}

void ordenar_aleatorio(bool algoritmo, int n)
{
    int i, v[n]; double t1, t, t_v1, t_v;
    aleatorio(v, n);
    t_v1 = microsegundos(); aleatorio(v, n); t_v = microsegundos() - t_v1;
    t1 = microsegundos();
    if(algoritmo) ord_ins(v, n - 1); else ord_rap(v, n);
    t = microsegundos() - t1 - t_v;
    if(t < 500)
    {
        t_v1 = microsegundos();
        for(i = 0; i < 1000; i++)
            aleatorio(v, n);
        t_v = microsegundos() - t_v1;
        if(algoritmo)
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {aleatorio(v, n);   ord_ins(v, n - 1);}
            t = (microsegundos() - t1 - t_v) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n, 1.8), t/pow(n,2), t/pow(n, 2.2));
        }
        else
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {aleatorio(v, n);   ord_rap(v, n);}
            t = (microsegundos() - t1 - t_v) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n,0.5), t/pow(n,1.1), t/pow(n, 2.2));
        }
    }
    else
        if (algoritmo)
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n, 1.8), t/pow(n,2), t/pow(n, 2.2));
        else
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n,0.5), t/pow(n,1.1), t/pow(n, 2.2));
}

void ordenar_desc(bool algoritmo, int n)
{
    int i, v[n]; double t1, t, t_v1, t_v;
    descendente(v, n);
    t_v1 = microsegundos(); descendente(v, n); t_v = microsegundos() - t_v1;
    t1 = microsegundos();
    if(algoritmo) ord_ins(v, n - 1); else ord_rap(v, n);
    t = microsegundos() - t1 - t_v;
    if(t < 500)
    {
        t_v1 = microsegundos();
        for(i = 0; i < 1000; i++)
            descendente(v, n);
        t_v = microsegundos() - t_v1;
        if(algoritmo)
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {descendente(v, n);   ord_ins(v, n - 1);}
            t = (microsegundos() - t1 - t_v) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/n, t/pow(n,2), t/pow(n,2.35));
        }
        else
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {descendente(v, n);   ord_rap(v, n);}
            t = (microsegundos() - t1 - t_v) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/log(n), t/pow(n, 1.055), t/pow(n,2.5));
        }
    }
    else
        if (algoritmo)
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
                , n, t, t/n, t/pow(n,2), t/pow(n,2.35));
        else
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/log(n), t/pow(n, 1.055), t/pow(n,2.5));
}

void ordenar_asc(bool algoritmo, int n)
{
    int i, v[n]; double t1, t, t_v1, t_v;
    ascendente(v, n);
    t_v1 = microsegundos(); ascendente(v, n); t_v = microsegundos() - t_v1;
    t1 = microsegundos();
    if(algoritmo) ord_ins(v, n - 1); else ord_rap(v, n);
    t = microsegundos() - t1 - t_v;
    if(t < 500)
    {
        t_v1 = microsegundos();
        for(i = 0; i < 1000; i++)
            ascendente(v, n);
        t_v = microsegundos() - t_v1;
        if(algoritmo)
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {ascendente(v, n);   ord_ins(v, n - 1);}
            t = (microsegundos() - t1 - t_v) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(2,3), t/n, t/pow(n,2));
        }
        else
        {
            t1 = microsegundos();
            for(i = 0; i < 1000; i++)
            {ascendente(v, n);   ord_rap(v, n);}
            t = (microsegundos() - t1 - t_v) / 1000;
            printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n,0.5), t/n, t/pow(n, 2.1));
        }
    }
    else
        if (algoritmo)
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(2,3), t/n, t/pow(n,2));
        else
            printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n"
            , n, t, t/pow(n,0.5), t/n, t/pow(n, 2.1));
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

void ord_ins(int v[], int n)
{
    int i, x, j;
    for(i = 1; i < n; i++)
    {
        x = v[i];
        for(j = i -1; j>= 0 && v[j] > x; j--)
            v[j+1] = v[j];
        v[j + 1] = x;
    }
}

void ord_rap(int v[], int n)
{
    ord_rap_aux(v, 0, n-1);
    ord_ins(v, n);
}

void mediana3(int v[], int iz, int dr)
{
    int i=iz, j=dr, tmp, centro = (i+j)/2;
    if (v[i] > v[centro])
    {
        tmp = v[centro];
        v[centro] = v[i];
        v[i] = tmp;
    }
    if (v[i] > v[j])
    {
        tmp = v[j];
        v[j] = v[i];
        v[i] = tmp;
    }
    if (v[centro] > v[j])
    {
        tmp = v[j];
        v[j] = v[centro];
        v[centro] = tmp;
    }
    tmp = v[j-1];
    v[j-1] = v[centro];
    v[centro] = tmp;
}

// Función auxiliar de QuickSort con Mediana de Tres
void ord_rap_aux(int v[], int iz, int dr)
{
    int k,m, i=iz, j=dr, tmp, pivote;
    if (i + UMBRAL > j)
    {
        mediana3(v, iz, dr);
        pivote = v[j-1];
        k = i;
        m = j - 1;
        while (m > k) {
            while (v[k] < pivote) {
                k++;
            }
            while (v[m] > pivote) {
                m--;
            }
            tmp = v[m];
            v[m] = v[k];
            v[k] = tmp;
        }

        tmp = v[m];
        v[m] = v[k];
        v[k] = tmp;

        tmp = v[j-1];
        v[j-1] = v[k];
        v[k] = tmp;

        ord_rap_aux(v, iz, k - 1);
        ord_rap_aux(v, k + 1, dr);
    }
}

// test

void test()
{
    int n = 17;
    int v[n];
    printf("\n-----------------------------------TEST"
                 "--------------------------------------\n");
    
    /*
    printf("\\nnOrdenación por insercion con inicialización aleatoria\n\n");
    aleatorio(v, 20); print_vec(20, v);
    ord_ins(v, 20); print_vec(20, v);
    */
    printf("\n\nOrdenación por quicksort con inicialización aleatoria\n\n");
    aleatorio(v, 20); print_vec(20, v);
    ord_rap(v, 20); print_vec(20, v);
    /*
    printf("\n\nOrdenación por inserción con inicialización descendente\n\n");
    descendente(w, 20); print_vec(20, w);
    ord_ins(w, 20); print_vec(20, w);
    */
    printf("\n\nOrdenación por quicksort con inicialización descendente\n\n");
    descendente(v, 20); print_vec(20, v);
    ord_rap(v, 20); print_vec(20, v);
    /*
    printf("\n\nOrdenación por inserción con inicialización ordenada\n\n");
    ascendente(w, 20); print_vec(20, w);
    ord_ins(w, 20); print_vec(20, w);
    */
    printf("\n\nOrdenación por quicksort con inicialización ordenada\n\n");
    ascendente(v, 20); print_vec(20, v);
    ord_rap(v, 20); print_vec(20, v);
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
    printf("\nOrdenado 1\n");
}

// tipos de ordenaciones de vectores

void aleatorio(int v[], int n)
{
    int i, m = 2*n+1;
    for (i = 0; i < n; i++)
        v[i] = rand() % m - n;
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
    k--;
    for(i = 0; i < k; i++)
        printf("%d, ", v[i]);
    printf("%d", v[k]);
    esta_ordenado(v, k);
}
