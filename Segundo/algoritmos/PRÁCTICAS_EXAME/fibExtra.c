#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>

double microsegundos();
int fib1(int n);
int fib2(int n);
int fib3(int n);
int fib4(int n);
void print_resultado(bool muyrapido, int fib,int array,
                     double t, double x, double z);
void test();
double toofast(int fib, int iteracions);
void iteracions();
void cronometro(int fib, int iteracions);

int main(){
    // Test
    test();

    // Complexidades
    iteracions();
    return 0;
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


int fib1(int n)
{
    if(n<2)
        return n;
    return fib1(n-1) + fib1(n-2);
}

int fib2(int n)
{
    int i = 1, j = 0, k = 1;
    for (; k <= n; k++)
    {
        j=i+j;
        i=j-i;
    }
    return j;
}

int fib3(int n) {
    int i = 1, j = 0, k = 0, h = 1, t;
    while ( n > 0 )
    {
        if ((n % 2) != 0)
        {
            t = j * h;
            j = (i * h) + (j * k) + t;
            i = (i * k) + t;
        }
        t = h * h;
        h = (2 * k * h) + t;
        k = (k * k) + t;
        n = n / 2;
    }
    return j;
}

void test()
{
    printf("\n------------TEST--------------\n");
    printf(("|  n |  fib1 |  fib2 |  fib3 |\n"));
    printf("------------------------------\n");
    int i = 0;
    for (; i <= 20; i++)
    {
        printf("| %2d | %5d | %5d | %5d |\n", i, fib1(i), fib2(i), fib3(i));
    }
    printf("-----------FIN-TEST-----------\n\n");
}

void iteracions()
{
    int i;
    const int arrayFib1[5] = {2,4,8,16,32};
    const int arrayFib23[5] = {1000,10000,100000,1000000,10000000};

    printf("----------------------------------");
    printf("--------------------------------------\n");
    printf("          |     N    |     Tempo    |      t(n)/2^n     |"
           "  t(n)/1.1^n  |\n");
    for(i = 0; i < 5; i++)
    {
        // fib 1
        cronometro(1, arrayFib1[i]);
    }

    printf("----------------------------------");
    printf("--------------------------------------\n");
    printf("          |     N    |     Tempo    |   t(n)/n*log(n)   |"
           "  t(n)/n^0.8  |\n");
    for(i = 0; i < 5; i++)
    {
        // fib 2
        cronometro(2, arrayFib23[i]);
    }
    printf("----------------------------------");
    printf("--------------------------------------\n");
    printf("          |     N    |     Tempo    | t(n)/sqrt(log(n)) |"
           "  t(n)/n^0.5  |\n");
    for(i = 0; i < 5; i++)
    {
        cronometro(3, arrayFib23[i]);
    }
    printf("----------------------------------");
    printf("--------------------------------------\n");
}

void print_resultado(bool muyrapido, int fib,int array,
                     double t, double x, double z)
{
    if(muyrapido)
    {
        if(fib == 1)
            printf("* FIB1    | %8d | %12.5f |%18.8f | %12.8f"
                   " |\n", array, t, x, z);
        if(fib == 2)
            printf("* FIB2    | %8d | %12.5f | %17.8f |"
                   " %12.6f |\n", array, t, x, z);
        if(fib == 3)
            printf("* FIB3    | %8d | %12.5f | %17.8f |"
                   " %12.8f |\n", array, t, x, z);
    }
    else
    {
        if(fib == 1)
            printf("  FIB1    | %8d | %12.5f | %17.8f | %12.7f"
                   " |\n", array, t, x, z);
        if(fib == 2)
            printf("  FIB2    | %8d | %12.5f | %17.8f |"
                   " %12.8f |\n", array, t, x, z);
        if(fib == 3)
            printf("  FIB3    | %8d | %12.5f | %17.8f |"
                   " %12.8f |\n", array, t, x, z);
    }
}

double toofast(int fib, int iteracions)
{
    if (fib > 3 || fib < 1)
        return 0;

    double t2, t1, t = 0; int i = 0;
    switch(fib)
    {
        case 1:
            t2 = microsegundos();
            for (; i < 1000; i++)
                fib1(iteracions);

            t1 = microsegundos();
            t = (t1 - t2) / 1000;
            break;
        case 2:
            t2 = microsegundos();
            for (; i < 1000; i++)
                fib2(iteracions);

            t1 = microsegundos();
            t = (t1 - t2) / 1000;
            break;
        case 3:
            t2 = microsegundos();
            for (; i < 100000; i++)
                fib3(iteracions);

            t1 = microsegundos();
            t = (t1 - t2) / 100000;
        default: break;
    }
    return t;
}


void cronometro(int fib, int iteracions)
{
    double t1, t2, t, x , z; bool muyrapido = false;
    switch(fib)
    {
        case 1:
            t1 = microsegundos(); fib1(iteracions); t2 = microsegundos();
            t = t2 - t1;
            if(t < 500)
            {
                t = toofast(1, iteracions);
                muyrapido = true;
            }
            x = t / pow(2, iteracions); z = t / pow(1.1, iteracions);
            print_resultado(muyrapido, 1, iteracions, t, x, z);
            break;
        case 2:
            t1 = microsegundos(); fib2(iteracions); t2 = microsegundos();
            t = t2 - t1;
            if(t < 500)
            {
                t = toofast(2, iteracions);
                muyrapido = true;
            }
            x = t / iteracions*log(iteracions); z = t / pow(iteracions, 0.8);
            print_resultado(muyrapido, 2, iteracions, t, x, z);
            break;
        case 3:
            t1 = microsegundos(); fib3(iteracions); t2 = microsegundos();
            t = t2 - t1;
            if(t < 500)
            {
                muyrapido = true;
                t = toofast(3, iteracions);
            }
            x = t / sqrt(log(iteracions)); z = t / pow(iteracions, 0.5);
            print_resultado(muyrapido, 3, iteracions, t, x, z);
            break;
        default: break;
    }
}
