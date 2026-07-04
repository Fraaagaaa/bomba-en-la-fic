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

void ord_ins(int v[], int n);
void ord_rap(int v[], int n);
void ord_rap_aux(int v[], int iz, int dr);
void bubble_sort(int v[], int n);
void test();
void inicializar_semilla();
void aleatorio(int v[], int n);
void ascendente(int v[], int n);
void esta_ordenado(int v[], int tamano);
void descendente(int v[], int n);
double microsegundos();
void ordenar(void algoritmo(int v[], int n), int n, void crear_vector(int v[], int n), int cotas);
void start();
void tabla(int i);
void print_vec(int k, int v[]);
double cotas(int c, int i, int n);

int main()
{
    inicializar_semilla();
    //start();
    test();
    return 0;
}

void start()
{
    const int tamano[7] = {500, 1000, 2000, 4000, 8000, 16000, 32000};
    int i, j;
    for (i = 0; i < 9; i++)
    {
        tabla(i);
        switch (i)
        {
            case 0:
                for (j = 0; j < 7; j++)
                    {ordenar(ord_ins, tamano[j], ascendente, i);} break;
            case 1:
                for (j = 0; j < 7; j++)
                    {ordenar(ord_ins, tamano[j], descendente, i);} break;
            case 2:
                for (j = 0; j < 7; j++)
                    {ordenar(ord_ins, tamano[j], aleatorio, i);} break;
            case 3:
                for (j = 0; j < 7; j++)
                    {ordenar(ord_rap, tamano[j], ascendente, i);} break;
            case 4:
                for (j = 0; j < 7; j++)
                    {ordenar(ord_rap, tamano[j], descendente, i);} break;
            case 5:
                for (j = 0; j < 7; j++)
                    {ordenar(ord_rap, tamano[j], aleatorio, i);} break;
            case 6:
                for (j = 0; j < 7; j++)
                    {ordenar(bubble_sort, tamano[j], ascendente, i);} break;
            case 7:
                for (j = 0; j < 7; j++)
                    {ordenar(bubble_sort, tamano[j], descendente, i);} break;
            case 8:
                for (j = 0; j < 7; j++)
                    {ordenar(bubble_sort, tamano[j], aleatorio, i);} break;
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
        case 0: printf("Vector ascendente, ordenación por inserción\n");
                printf("|    N    |     t(n)      |   t(n)/n¹·⁸   |"
           "    t(n)/n²  |     t(n)/n²·²     |\n"); break;
        case 1: printf("Vector descendente, ordenación por inserción\n");
                printf("|    N    |     t(n)      |   t(n)/n⁰·⁵   |"
                "    t(n)/n¹·¹  |    t(n)/n²·²    |\n");break;
        case 2: printf("Vector aleatorio, ordenación por inserción\n");
                printf("|    N    |     t(n)      |    t(n)/n    |"
                "    t(n)/n²     |    t(n)/n²·³⁵   |\n"); break;
        case 3: printf("Vector ascendente, quick sort\n");
                printf("|    N    |     t(n)      |  t(n)/log(n)  |"
                "   t(n)/n¹·⁰⁵⁵ |    t(n)/n²·⁵    |\n"); break;
        case 4: printf("Vector descendente, quick sort\n");
                printf("|    N    |      t(n)     |   t(n)/n²·³   |"
                "     t(n)/n    |      t(n)/n²    |\n"); break;
        case 5: printf("Vector aleatorio, quick sort\n");
                printf("|    N    |     t(n)      |   t(n)/n⁰·⁵   |"
                "     t(n)/n    |     t(n)/n²·¹   |\n"); break;
        case 6: printf("Vector ascendente, bubble sort\n");
                printf("|    N    |     t(n)      |   t(n)/n⁰·⁵   |"
                "     t(n)/n    |     t(n)/n²·¹   |\n"); break;
        case 7: printf("Vector descendente, bubble sort\n");
                printf("|    N    |     t(n)      |   t(n)/n⁰·⁵   |"
                "     t(n)/n    |     t(n)/n²·¹   |\n"); break;
        case 8: printf("Vector aleatorio, bubble sort\n");
                printf("|    N    |     t(n)      |   t(n)/n⁰·⁵   |"
                "     t(n)/n    |     t(n)/n²·¹   |\n"); break;
        default: break;
    }

}

void ordenar(void algoritmo(int v[], int n), int n, void crear_vector(int v[], int n), int c)
{
    int i, *v = malloc(n * sizeof(int)); double t1, t, t_v1, t_v;
    double c1 = cotas(c, 0, n), c2 = cotas(c, 1, n), c3 = cotas(c, 2, n);
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
        printf("| * %5d |%14.4f |%14.10f |%14.10f |%16.12f |\n", n, t, t*c1, t*c2, t*c3);
    }
    else
        printf("|%8d |%14.4f |%14.10f |%14.10f |%16.12f |\n", n, t, t*c1, t*c2, t*c3);
    free(v);
}

double cotas(int c, int i, int n)
{
    /*  
        c
        0: inserción
        1: quick sort
        2: bubble sort
    */
   switch(c)
   {
        // insercion ascendente
        case 0:
            switch (i)
            {
                case 0: return 1/pow(n, 2.3);
                case 1: return 1/pow(n, 2);
                case 2: return 1/pow(n, 0.5);
            }
        break;
        // insercion descendente
        case 1:
            switch (i)
            {
                case 0: return 1/n;
                case 1: return 1/(pow(n, 2));
                case 2: return 1/(pow(n, 2.35));
            }
        break;
        // insercion aleatorio
        case 2:
            switch (i)
            {
                case 0: return 1/pow(n, 2.3);
                case 1: return 1/n;
                case 2: return 1/(pow(n, 2));
            }
        break;
        // quicksort ascendente
        case 3:
            switch (i)
            {
                case 0: return 1/pow(n, 2.1);
                case 1: return 1/n;
                case 2: return 1/(n*log(n));
            }
        break;
        // quicksort descendente
        case 4:
            switch (i)
            {
                case 0: return 1/log(n);
                case 1: return 1/pow(n, 1.055);
                case 2: return 1/pow(n, 2.5);
            }
        break;
        // quicksort aleatorio
        case 5:
            switch (i)
            {
                case 0: return 0;
                case 1: return 0;
                case 2: return 0;
            }
        break;
        case 6:
            switch (i)
            {
                case 0: return 0;
                case 1: return 0;
                case 2: return 0;
            }
        break;
        // quicksort descendente
        case 7:
            switch (i)
            {
                case 0: return 0;
                case 1: return 0;
                case 2: return 0;
            }
        break;
        // quicksort aleatorio
        case 8:
            switch (i)
            {
                case 0: return 0;
                case 1: return 0;
                case 2: return 0;
            }
        break;
   }
   return 0.0;
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

void bubble_sort(int v[], int n)
{
    int i, j, aux;
    for(i = 0; i < n; i++)
        for(j = 0; j < n - i; j++)
            if(v[j] > v[j+1])
            {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
}

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
}

void ord_rap_aux(int v[], int iz, int dr)
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
                i++; j--;
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
    int n = 17;
    int v[n]; int w[n];
    printf("\n-----------------------------------TEST"
                 "--------------------------------------\n");


    printf("\n-----------------------------------Inserción"
                 "--------------------------------------\n");

    printf("\n\nOrdenación por inserción con inicialización ordenada\n\n");
    ascendente(w, 20); print_vec(20, w);
    ord_ins(w, 20); print_vec(20, w);

    printf("\n\nOrdenación por inserción con inicialización descendente\n\n");
    descendente(w, 20); print_vec(20, w);
    ord_ins(w, 20); print_vec(20, w);

    printf("\\nnOrdenación por insercion con inicialización aleatoria\n\n");
    aleatorio(v, 20); print_vec(20, v);
    ord_ins(v, 20); print_vec(20, v);


    printf("\n-----------------------------------Quick Sort"
                 "--------------------------------------");


    printf("\n\nOrdenación por quicksort con inicialización ordenada\n\n");
    ascendente(w, 20); print_vec(20, w);
    ord_rap(w, 20); print_vec(20, w);

    printf("\n\nOrdenación por quicksort con inicialización descendente\n\n");
    descendente(w, 20); print_vec(20, w);
    ord_rap(w, 20); print_vec(20, w);

    printf("\n\nOrdenación por quicksort con inicialización aleatoria\n\n");
    aleatorio(w, 20); print_vec(20, w);
    ord_rap(w, 20); print_vec(20, w);


    printf("\n-----------------------------------Bubble Sort"
                 "--------------------------------------");


    printf("\n\nOrdenación por bubble sort con inicialización ascendente\n\n");
    ascendente(w, 20); print_vec(20, w);
    bubble_sort(w, 20); print_vec(20, w);
    
    printf("\n\nOrdenación por bubble sort con inicialización descendente\n\n");
    descendente(w, 20); print_vec(20, w);
    bubble_sort(w, 20); print_vec(20, w);
    
    printf("\n\nOrdenación por bubble sort con inicialización aleatoria\n\n");
    aleatorio(w, 20); print_vec(20, w);
    bubble_sort(w, 20); print_vec(20, w);
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