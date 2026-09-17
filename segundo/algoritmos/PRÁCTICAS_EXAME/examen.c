#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define TAM 256000
#define TAMTEST 10
#define TAMCOMP 10
#define IZQ(i) (2*i + 1)
#define DER(i) (2*i + 2)
#define PADRE(i) ((i-1)/2)
struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo * pmonticulo;
double microsegundos();
void iniMonticulo(pmonticulo m);
void insertarMonticulo(pmonticulo m, int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m, int v[], int n);
void ordenarPorMonticulos(int v[], int n);
void hundir(pmonticulo m, int i);
void flotar(pmonticulo m, int i);

void inicializar_semilla();

void demosEmpirica();
void demostracionCrear();
void demostracionInsertar();
double demosEmpiricaLentos(int n, bool caso);

void complejidades();
void medirTiempos();
double tiemposLentos(int vec, int n);
double cotas(int i, int n);
void tabla(bool quinto);

void test();
void comprobacionApartado3();

void monticulo_a_vector(pmonticulo m, int *v);
void printVector(int vector[], int n);
void imprimirPorNivel(pmonticulo m);

void vectorAleatorio(int *v, int n);
int kesimo_mayor(int v[], int n, int k);
void copiarVector(int v[], int w[], int n);


void calcularComplejidad();
double calcularComplejidadLentos(int n, bool quinto);

int main()
{
    inicializar_semilla();

    // Test - Apartado 3
    test();

    calcularComplejidad();

    return 0;
}

void tabla(bool quinto)
{
    if(quinto)
    {
        printf("Buscar el quinto mayor");
        printf("| L |    N    |   Tempo   |    t(n)/n^0.8     |"
                "t(n)/(n*log(n))|   t(n)/n   |\n");
    }

}

void calcularComplejidad()
{
    int v[TAM], i;
    // const int n[7] = {8, 16, 32, 64, 128, 256, 512};
    // const int n[7] = {1000, 2000, 4000, 8000, 16000, 32000, 64000};
    const int n[7] = {2000, 4000, 8000, 16000, 32000, 64000, 128000};
    double tiempo, c1, c2, c3;
    bool quinto = true, lento;
    printf("\n\n");
    // Prueba de buscar el 5º mayor
    vectorAleatorio(v, TAM);
    for(i = 0; i < 7; i++)
    {
        lento = false;
        tiempo = microsegundos();
        kesimo_mayor(v, n[i], 5);
        tiempo = microsegundos() - tiempo;
        if(tiempo < 500)
        {
            tiempo = calcularComplejidadLentos(n[i], quinto);
            lento = true;
        }
    
        c1 = cotas(1, n[i]) * tiempo;
        c2 = cotas(2, n[i]) * tiempo;
        c3 = cotas(3, n[i]) * tiempo;

        if (lento) {printf("|(*)| %7d | %9.2f | %13.7f |"
                          " %13.5f | %13.7f |\n",n[i], tiempo, c1, c2, c3);}
        else      {printf("|   | %7d | %9.2f | %13.7f |"
                          " %13.5f | %13.7f |\n",n[i], tiempo, c1, c2, c3);}
    }
    printf("\n\n");
    // Prueba de buscar n/3º
    quinto = false;

    for(i = 0; i < 7; i++)
    {
        lento = false;
        tiempo = microsegundos();
        kesimo_mayor(v, n[i], n[i]/3);
        tiempo = microsegundos() - tiempo;
        if(tiempo < 500)
        {
            tiempo = calcularComplejidadLentos(n[i], quinto);
            lento = true;
        }
        
        c1 = cotas(4, n[i]) * tiempo;
        c2 = cotas(5, n[i]) * tiempo;
        c3 = cotas(6, n[i]) * tiempo;
        
        if (lento) {printf("|(*)| %7d | %9.2f | %13.7f |"
                          " %13.5f | %13.7f |\n",n[i], tiempo, c1, c2, c3);}
        else      {printf("|   | %7d | %9.2f | %13.7f |"
                          " %13.5f | %13.7f |\n",n[i], tiempo, c1, c2, c3);}
    }
}

double cotas(int i, int n)
{
    switch(i)
    {
        case 1: return 1.0/pow(n, 1.1);
        case 2: return 1.0/pow(n, 0.9);
        case 3: return 1.0/pow(n, 0.6);
        case 4: return 1.0/(log(n)*n);
        case 5: return 1.0/pow(n, 1.1);
        case 6: return 1.0/pow(n, 0.8);
        default: return 0.0;
    }
    return 0.0;
}

double calcularComplejidadLentos(int n, bool quinto)
{
    int i, v[TAM];
    double start, tiempo;
    vectorAleatorio(v, TAM);
    if(quinto)
    {
        start = microsegundos();
        for(i = 0; i < 100; i++)
        {
            //vectorAleatorio(v, TAM);
            kesimo_mayor(v, n, 5);
        }
        tiempo = microsegundos() - start;

    }
    else
    {
        start = microsegundos();
        for(i = 0; i < 100; i++)
        {
            //vectorAleatorio(v, TAM);
            kesimo_mayor(v, n, n/3);
        }
        tiempo = microsegundos() - start;

    }
    return tiempo/100;
}

int kesimo_mayor(int v[], int n, int k)
{
    struct monticulo m; int i;
    iniMonticulo(&m);

    crearMonticulo(&m, v, k);
    
    for(i = k; i < n; i++)
    {
        if(v[i] > consultarMenor(&m))
        {
            quitarMenor(&m);
            insertarMonticulo(&m, v[i]);
        }
    }
    return consultarMenor(&m);
}
void test()
{
    int v[TAMTEST], w[TAMTEST];
    int i;
    vectorAleatorio(v, TAMTEST);
    copiarVector(v , w, TAMTEST);

    printf("Vecor original: ["); printVector(v, TAMTEST); printf("]\n");
    
    printf("Elementos extraidos: ");
    for(i = 1; i < TAMTEST; i++)
    {
        copiarVector(v, w, TAMTEST);
        printf("%d", kesimo_mayor(w, TAMTEST, i));
        printf(", ");
    }
    printf("%d \n", kesimo_mayor(v, TAMTEST, TAMTEST));
}

void copiarVector(int v[], int w[], int n)
{
    int i;
    for(i = 0; i < n; i++)
        w[i] = v[i];
}

void inicializar_semilla()
{
    srand(time(NULL));
}

void printVector(int vector[], int n)
{
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", vector[i]);
}

void vectorAleatorio(int *v, int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = rand() % 100;
}


void ordenarPorMonticulos(int v[], int n)
{
    struct monticulo m; int i;
    iniMonticulo(&m);

    crearMonticulo(&m, v, n); // O(n)
    for (i = 0; i < n; i++)
    {
        v[i] = consultarMenor(&m);
        quitarMenor(&m); // O(n)
    }
}

void iniMonticulo(pmonticulo m)
{
    m->ultimo = -1;
}

void quitarMenor(pmonticulo m)
{
    m->vector[0] = m->vector[m->ultimo];
    m->ultimo--;
    if (m->ultimo > -1)
        hundir(m, 0);
}

int consultarMenor(const pmonticulo m)
{
    return m->vector[0];
}

void crearMonticulo(pmonticulo m, int v[], int n)
{
    int i;

    if (n > TAM)
    {
        printf("El vector supera el tamaño límite\n");
        return;
    }

    for (i = 0; i < n; i++)
        m->vector[i] = v[i];
    m->ultimo = n - 1;

    for (i = (m->ultimo / 2 - 1); i >= 0; i--)
        hundir(m, i);
}

void hundir(pmonticulo m, int i)
{
    int izquierdo = IZQ(i), derecho = DER(i), menor = i, temp;

    if (izquierdo <= m->ultimo && m->vector[izquierdo] < m->vector[menor])
        menor = izquierdo;

    if (derecho <= m->ultimo && m->vector[derecho] < m->vector[menor])
        menor = derecho;

    if (menor != i)
    {
        temp = m->vector[i];
        m->vector[i] = m->vector[menor];
        m->vector[menor] = temp;
        hundir(m, menor);
    }
}


void insertarMonticulo(pmonticulo m, int x)
{
    if (m->ultimo >= TAM - 1)
        exit(2);

    m->ultimo++;
    m->vector[m->ultimo] = x;

    flotar(m, m->ultimo);
}

void flotar(pmonticulo m, int i)
{
    int padre = PADRE(i), temp;

    while (i > 0 && m->vector[i] < m->vector[padre])
    {
        temp = m->vector[i];
        m->vector[i] = m->vector[padre];
        m->vector[padre] = temp;

        i = padre;
        padre = PADRE(i);
    }
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
