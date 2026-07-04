/*

    NOTA: ESTO DEJA EL ARRAY ORDENADO DE MAYOR A MENOR,
    SI PIDEN QUE SEA DE MENOR A MAYOR TIENES QUE DARLE LA VUELTA
    AÑADIENDO UNA FUNCIÓN EXTRA

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define TAM 256000
#define TAMTEST 19
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
void quitarMayor(pmonticulo m);
int consultarMayor(const pmonticulo m);
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
double cotas(int i, int j, int n);
void tabla(int t);

void test();
void comprobacionApartado3();

void monticulo_a_vector(pmonticulo m, int *v);
void printVector(int vector[], int n);
void imprimirPorNivel(pmonticulo m);

void vectorAsc(int *v, int n);
void vectorDesc(int *v, int n);
void vectorRand(int *v, int n, bool test);


int main()
{
    inicializar_semilla();

    // Test - Apartado 1
    test();

    // Demostraciones empiricas - Apartado 2
    demosEmpirica();

    // Comprobación de la función ordenarPorMonticulos - Apartado 3
    comprobacionApartado3();

    // Calcular complejidades - Apartado 4
    complejidades();

    return 0;
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void ordenarPorMonticulos(int v[], int n)
{
    struct monticulo m; int i;
    iniMonticulo(&m);

    crearMonticulo(&m, v, n);
    for (i = 0; i < n; i++)
    {
        v[i] = consultarMayor(&m);
        quitarMayor(&m);
    }
}

void iniMonticulo(pmonticulo m)
{
    m->ultimo = -1;
}

void quitarMayor(pmonticulo m)
{
    m->vector[0] = m->vector[m->ultimo];
    m->ultimo--;
    if (m->ultimo > -1)
        hundir(m, 0);
}

int consultarMayor(const pmonticulo m)
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
    int izquierdo = IZQ(i), derecho = DER(i), mayor = i, temp;

    if (izquierdo <= m->ultimo && m->vector[izquierdo] > m->vector[mayor])
        mayor = izquierdo;

    if (derecho <= m->ultimo && m->vector[derecho] > m->vector[mayor])
        mayor = derecho;

    if (mayor != i)
    {
        temp = m->vector[i];
        m->vector[i] = m->vector[mayor];
        m->vector[mayor] = temp;
        hundir(m, mayor);
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

    while (i > 0 && m->vector[i] > m->vector[padre])
    {
        temp = m->vector[i];
        m->vector[i] = m->vector[padre];
        m->vector[padre] = temp;

        i = padre;
        padre = PADRE(i);
    }
}

void imprimirPorNivel(pmonticulo m)
{
    int nivel_actual = 0, i, limite_nivel = (int) pow(2, nivel_actual) - 1, j;

    printf("              ");
    for ( i = 0; i <= m->ultimo; i++)
    {
        printf("%d ", m->vector[i]);

        if (i == limite_nivel)
        {
            nivel_actual++;
            limite_nivel += (int) pow(2, nivel_actual);
            printf("\n");
            for (j = 5; j > nivel_actual; j--)
                printf("   ");
        }
    }
    printf("\n");
}

void test()
{
    struct monticulo m;
    int v[TAMTEST];
    int i;

    printf("# Apartado 1: Implementación de crearMonticulo"
           " e insertarMonticulo\n\n");
    vectorRand(v, TAMTEST, true);
    for(i = 0; i < TAMTEST; i++)
        v[i] = rand() % 100;

    printf("Usando crearMonticulo\n");
    crearMonticulo(&m, v, TAMTEST);
    imprimirPorNivel(&m);

    printf("\nEl elemento mayor es: %d\n"
           "Eliminando mayor...\n", consultarMayor(&m));
    quitarMayor(&m);
    imprimirPorNivel(&m);

    printf("\n\nUsando insertarMonticulo\n");
    iniMonticulo(&m);
    for(i = TAMTEST; i > 0; i--)
        insertarMonticulo(&m, rand() % 100);
    imprimirPorNivel(&m);
}

void inicializar_semilla()
{
    srand(time(NULL));
}

void demosEmpirica()
{
    printf("\n\n# Apartado 2: Demostraciones empiricas\n\n");
    demostracionCrear();
    demostracionInsertar();
}

void demostracionInsertar()
{
    int i, j;
    double t1, tiempo, c1, c2, c3;
    bool slow;
    struct monticulo m;
    const int n[8] = {2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};

    tabla(4);
    for (i = 0; i < 8; i++)
    {
        slow = false;
        iniMonticulo(&m);

        t1 = microsegundos();
        for (j = 0; j < n[i]; j++)
            insertarMonticulo(&m, rand());
        tiempo = microsegundos() - t1;

        if (tiempo < 500)
        {
            slow = true;
            tiempo = demosEmpiricaLentos(n[i], true);
        }
        c1 = tiempo * cotas(4, 0, n[i]);
        c2 = tiempo * cotas(4, 1, n[i]);
        c3 = tiempo * cotas(4, 2, n[i]);
        if (slow) {printf("|(*)| %7d | %9.2f | %13.7f |"
                          " %13.5f | %13.7f |\n",n[i], tiempo, c1, c2, c3);}
        else      {printf("|   | %7d | %9.2f | %13.7f |"
                          " %13.5f | %13.7f |\n",n[i], tiempo, c1, c2, c3);}
    }
}

void demostracionCrear()
{
    int i, j, v[TAM];
    double tiempo, c1, c2, c3;
    bool slow; struct monticulo m;
    const int n[8] = {2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};

    tabla(3);
    for(i = 0; i < 8; i++)
    {
        slow = false;
        iniMonticulo(&m);

        for(j = 0; j < n[i]; j++)
            v[j] = rand();

        tiempo = microsegundos();
        crearMonticulo(&m, v, n[i]);
        tiempo = microsegundos() - tiempo;

        if(tiempo < 500)
        {
            tiempo = demosEmpiricaLentos(n[i], false);
            slow = true;
        }
        c1 = tiempo * cotas(3, 0, n[i]);
        c2 = tiempo * cotas(3, 1, n[i]);
        c3 = tiempo * cotas(3, 2, n[i]);
        if (slow) {printf("|(*)| %7d | %9.2f | %13.7f |"
                          " %13.5f | %13.7f |\n",n[i], tiempo, c1, c2, c3);}
        else      {printf("|   | %7d | %9.2f | %13.7f |"
                          " %13.5f | %13.7f |\n",n[i], tiempo, c1, c2, c3);}
    }
}

double demosEmpiricaLentos(int n, bool caso)
{
    struct monticulo m;
    int k = 1000, i, j, v[n];
    double t1, t2, t3, tiempo;

    if(caso)
    {
        t1 = microsegundos();
        for(i = 0; i < k; i++)
        {
            iniMonticulo(&m);
            for(j = 0; j < n; j++)
                insertarMonticulo(&m, rand());
        }
        tiempo = microsegundos() - t1;
    }
    else
    {
        t1 = microsegundos();
        for(i = 0; i < n; i++)
            v[i] = rand();

        for(i = 0; i < k; i++)
        {
            iniMonticulo(&m);
            crearMonticulo(&m, v, n);
        }
        t2 = microsegundos() - t1;

        t3 = microsegundos();
        for(i = 0; i < k; i++)
            iniMonticulo(&m);
        t1 = microsegundos() - t3;

        tiempo = t2 - t1;
    }
    return tiempo / k;
}

// Apartado 3

void printVector(int vector[], int n)
{
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", vector[i]);
    printf("\n");
}

void monticulo_a_vector(pmonticulo m, int *v)
{
    int i;
    for(i = 0; i < m->ultimo; i++)
        v[i] = m->vector[i];
}

void comprobacionApartado3()
{
    int vector[TAMCOMP];
    struct monticulo m;

    printf("\n\n# Apartado 3: Comprobación de la funcionalidad"
           " de ordernarPorMontuculos\n\n");
    vectorRand(vector, TAMCOMP, true);
    printf("Vector aleatorio: "); printVector(vector, TAMCOMP);
    crearMonticulo(&m, vector, TAMCOMP);
    printf("Mayor: %d\n", consultarMayor(&m));
    ordenarPorMonticulos(vector, TAMCOMP);
    printf("Vector ordenado: "); printVector(vector, m.ultimo);
    quitarMayor(&m);
    monticulo_a_vector(&m, vector);
    printf("Vector ordenado tras quitar el mayor: ");
    printVector(vector, m.ultimo);
}
// Apartado 4

void vectorAsc(int *v, int n)
{
    int i, j[8] = {2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};
        for (i = 0; i < j[n]; i++)
            v[i] = i;
}

void vectorDesc(int *v, int n)
{
    int i, j[8] = {2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};
        for (i = 0; i < j[n]; i++)
            v[i] = j[n] - i;
}

void vectorRand(int *v, int n, bool test)
{
    int i, j[8] = {2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};
    if (!test)
        for (i = 0; i < j[n]; i++)
            v[i] = rand() % 100;
    else
        for (i = 0; i < n; i++)
                v[i] = rand() % 100;
}

void complejidades()
{
    const int n[8] = {2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000}; int i, j;
    double t, tiempo, c1, c2, c3; int v[TAM]; bool slow;
    printf("\n\n# Apartado 4: Ordenación de vectores\n\n");
    for(i = 0; i < 3; i++)
    {
        tabla(i);
        for (j = 0; j < 8; j++)
        {
            slow = false;
            if (i == 0) vectorAsc(v, j);
            if (i == 1) vectorDesc(v, j);
            if (i == 2) vectorRand(v, j, false);
            t = microsegundos();
            ordenarPorMonticulos(v, n[j]);
            tiempo = microsegundos() - t;
            if (tiempo < 500) {slow = true;tiempo = tiemposLentos(i, n[j]);}

            c1 = tiempo * cotas(i, 0, n[j]);
            c2 = tiempo * cotas(i, 1, n[j]);
            c3 = tiempo * cotas(i, 2, n[j]);

            if (slow) {printf("|(*)| %7d | %9.2f | %13.7f | %13.10f |"
                              " %13.6f |\n",n[j], tiempo, c1, c2, c3);}
            else      {printf("|   | %7d | %9.2f | %13.7f | %13.10f |"
                              " %13.6f |\n",n[j], tiempo, c1, c2, c3);}
        }
    }
}


double cotas(int i, int j, int n)
{
    if (i > 5 || j > 3)
        exit(2);
    switch (i)
    {
        case 0: case 1: case 2:
            if (j == 0) return 1.0 / n;
            if (j == 1) return 1.0 / (n*log(n));
            if (j == 2) return 1.0 / pow(n, 1.2);
            break;
        case 3: // crear monticulo
            if (j == 0) return 1.0 / pow(n, 0.8);
            if (j == 1) return 1.0 / n;
            if (j == 2) return 1.0 / pow(n, 1.3);
            break;
        case 4: // InsertarMonticulo
            if (j == 0) return 1.0 / n;
            if (j == 1) return 1.0 / (n* log(n));
            if (j == 2) return 1.0 / pow(n,  1.2);
            break;
    }
    return 0;
}

void tabla(int t)
{
    switch(t)
    {
        case 0:
            printf("\n\nVector ascendente\n");
            printf("| L |    N    |   Tempo   |    t(n)/n     |"
                   "t(n)/(n*log(n))|   t(n)/n¹·²   |\n");
            break;
        case 1:
            printf("\n\nVector descendente\n");
            printf("| L |    N    |   Tempo   |    t(n)/n     |"
                   "t(n)/(n*log(n))|   t(n)/n¹·²   |\n");
            break;
        case 2:
            printf("\n\nVector aleatorio\n");
            printf("| L |    N    |   Tempo   |    t(n)/n     |"
                   "t(n)/(n*log(n))|   t(n)/n¹·²   |\n");
            break;
        case 3:
            printf("\n\nDemostración empírica de añadir n nodos"
                   " con crearMonticulo es O(n)\n");
            printf("| L |    N    |   Tempo   |   t(n)/n⁰·⁸   |"
                   "    t(n)/n     |   t(n)/n¹·³   |\n");
            break;
        case 4:
            printf("\n\nDemostración empírica de añadir n nodos"
                   " con insertarMonticulo es O(n*log(n))\n");
            printf("| L |    N    |   Tempo   |    t(n)/n     |"
                   "t(n)/(n*log(n))|   t(n)/n¹·²   |\n");
            break;
        default: exit(2);
    }
}

double tiemposLentos(int vec, int n)
{
    int k, v[TAM];
    double t;

    if (vec == 0) vectorAsc(v, n);
    if (vec == 1) vectorDesc(v, n);
    if (vec == 2) vectorRand(v, n, false);

    t = microsegundos();
    for (k = 1000; k != 0; k--)
        ordenarPorMonticulos(v, n);
    t = microsegundos() - t;

    return t / 1000;
}
