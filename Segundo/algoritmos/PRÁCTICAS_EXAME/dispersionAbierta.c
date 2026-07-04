#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define TAMANO 38197
#define TAMTEST 11
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

typedef struct item {
    char clave[LONGITUD_CLAVE];
    char sinonimos[LONGITUD_SINONIMOS];
    struct item *siguiente;
} item;

typedef item *entrada;
typedef entrada Tabla[TAMANO];

void inicializar_semilla();
double microsegundos();
void inicializar_tabla(Tabla tabla, int tam);
item *buscar(char* clave, Tabla tabla, int tam, int *colisiones, unsigned int dispersion(char *clave, int tamTabla));
int insertar_abierta(char* clave, char *sinonimos, Tabla *tabla, int tam, int *colisiones, unsigned int (*dispersion)(char *, int));
item *buscar_lista(char* clave, entrada entrada, int *colisiones);
void insertar_entrada(char* clave, entrada *entrada);
void test();
void imprimir_entrada(entrada entrada);
void imprimir_tabla(Tabla tabla, int tam);
int leer_sinonimos(item datos[]);
void calculos();
double cota(int cotas, int i, int n);
double medir_tiempos_slow(Tabla tabla, item datos[], int num_datos, int n, unsigned int (*dispersion)(char *, int));

unsigned int dispersionB(char *clave, int tamTabla);
unsigned int dispersionA(char *clave, int tamTabla);
void liberar_memoria(Tabla tabla, int tam);
void calcular_tiempos(Tabla tabla, item datos[], int num_datos, int n, unsigned int (*dispersion) (char *, int), int cotas);
// PASAR A BOOL LO DE LAS COTAS

// Recordatorio de que las entradas en tablas abiertas son:
// [][][A;B][C][][][][]
// Cada [] representa una entrada
// Cada letra representa un elemento
// El ; representa el siguiente elemento de la lista

// FALTARIA CALCULAR LAS COLISIONES
int main()
{
    inicializar_semilla();
    test();
    calculos();
    return 0;
}

void test()
{
    Tabla tabla; int tam = 11;
    char *elementos_insertar[] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA" ,"IVAN"};
    int total_colisiones_lineal = 0, i, colisiones = 0;
    char sinonimos[] = "";
    inicializar_tabla(tabla, TAMTEST);
    printf("Dispersion A: \n");
    for (i = 0; i < 6; i++)
    {
        colisiones = 0;
        insertar_abierta(elementos_insertar[i], sinonimos, &tabla, TAMTEST, &colisiones, dispersionA);
        total_colisiones_lineal += colisiones;
    }
    imprimir_tabla(tabla, tam);
    printf("Número total de colisiones al insertar los elementos con dispersión A: %d\n\n", total_colisiones_lineal);
    total_colisiones_lineal = 0;
    
    liberar_memoria(tabla, TAMTEST);
    inicializar_tabla(tabla, TAMTEST);

    printf("\n\n");
    printf("Dispersión B: \n");
    for (i = 0; i < 6; i++)
    {
        colisiones = 0;
        insertar_abierta(elementos_insertar[i], sinonimos, &tabla, TAMTEST, &colisiones, dispersionB);
        total_colisiones_lineal += colisiones;
    }
    imprimir_tabla(tabla, tam);
    printf("Número total de colisiones al insertar los elementos con dispersión B: %d\n\n\n", total_colisiones_lineal);

    liberar_memoria(tabla, TAMTEST);
}

void inicializar_semilla()
{
    srand(time(NULL));
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
void calculos()
{
    item *datos = malloc(sizeof(item) * TAMANO);
    Tabla tabla;
    const int n[10] = {125, 250, 500, 1000, 2000, 4000, 8000, 16000, 32000, 64000};
    int colisiones, i, total_colisiones = 0, num_sinonimos = leer_sinonimos(datos);
    
    inicializar_tabla(tabla, TAMANO);

    for (i = 0; i < num_sinonimos; i++)
    {
        colisiones = 0;
        insertar_abierta(datos[i].clave, datos[i].sinonimos, &tabla, TAMANO, &colisiones, dispersionA);
        total_colisiones += colisiones;
    }

    printf("- Total de colisiones con dispersión A: %d\n", total_colisiones);

    for (i = 0; i < 10; i++)
        calcular_tiempos(tabla, datos, TAMANO, n[i], dispersionA, 0);

    liberar_memoria(tabla, TAMANO);

    inicializar_tabla(tabla, TAMANO);

    total_colisiones = 0;

    for (i = 0; i < num_sinonimos; i++) {
        colisiones = 0;
        insertar_abierta(datos[i].clave, datos[i].sinonimos, &tabla, TAMANO, &colisiones, dispersionB);
        total_colisiones += colisiones;
    }

    printf("\n\n- Total de colisiones con dispersión B: %d\n", total_colisiones);

    for (i = 0; i < 10; i++)
        calcular_tiempos(tabla, datos, TAMANO, n[i], dispersionB, 1);

    liberar_memoria(tabla, TAMANO);
    free(datos);
}

void calcular_tiempos(Tabla tabla, item datos[], int num_datos, int n, unsigned int (*dispersion) (char *, int), int cotas)
{
    int colisiones_busqueda, indice_aleatorio, i, slow = 0;
    double inicio, tempo, c1, c2, c3, sobre, axus, sub;

    inicio = microsegundos();

    for (i = 0; i < n; i++)
    {
        indice_aleatorio = rand() % num_datos;
        buscar(datos[indice_aleatorio].clave, tabla, TAMANO,
                       &colisiones_busqueda, dispersion);
    }
    tempo = microsegundos() - inicio;

    if(tempo < 500)
    {
        tempo = medir_tiempos_slow(tabla, datos, num_datos, n, dispersion) / 1000;
        slow = 1;
    }
    c1 = cota(cotas, 0, n);
    c2 = cota(cotas, 1,n);
    c3 = cota(cotas, 2, n);
    sobre = tempo * c1; axus = tempo * c2; sub = tempo * c3;
    if(slow)
        printf("(*) | %7d | %12.3f | %15.6f | %15.6f | %15.6f |\n"
            , n, tempo, sobre, axus, sub);
    else
        printf("    | %7d | %12.3f | %15.6f | %15.6f | %15.6f |\n"
            , n, tempo, sobre, axus, sub);

}

double cota(int cotas, int i, int n)
{
    if(cotas == 0)  // Dispersion A
    {
        if(i == 0)
            return 1.0 / pow( 125*n, 0.9);
        if(i == 1)
            return 1.0 / (125*n);
        return 1.0 / pow(2*n, 1.4);
    }
    if(cotas == 1)  // Dispersion B
    {
        if(i == 0)
            return 1.0 / pow(n, 0.65);
        if(i == 1)
            return 1.0 / (n*log(n));
        return 1.0 / pow(n, 1.2);
    }
    return 0;
}


double medir_tiempos_slow(Tabla tabla, item datos[], int num_datos, int n, unsigned int (*dispersion)(char *, int))
{
    int i, j, indice_aleatorio, colisiones_busqueda;
    double tiempo, tiempo_ale;
    double inicio = microsegundos();

    for(i = 0; i < 1000; i++)
        for(j = 0; j < n; j++)
        {
            indice_aleatorio = rand() % num_datos;
            buscar(datos[indice_aleatorio].clave, tabla, TAMANO, &colisiones_busqueda, dispersion);
        }
    tiempo = microsegundos() - inicio;

    inicio = microsegundos();
    for(i = 0; i < 1000; i++)
        for(j = 0; j < n; j++)
            indice_aleatorio = rand() % num_datos;
    tiempo_ale = inicio - microsegundos();

    return tiempo - tiempo_ale;
}


void inicializar_tabla(Tabla tabla, int tam)
{
    int i;
    for (i = 0; i < tam; i++) {
        tabla[i] = NULL;
    }
}

void imprimir_entrada(entrada entrada)
{
    item *actual = entrada;
    if(actual == NULL)
        printf("vacío.");
    while (actual != NULL)
    {
        if(actual->siguiente != NULL)
            printf("Clave: '%s' -> ", actual->clave);
        else
            printf("Clave: '%s' ", actual->clave);
        actual = actual->siguiente;
    }
    printf("\n");
}

void imprimir_tabla(Tabla tabla, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        printf("Índice %d: ", i);
        imprimir_entrada(tabla[i]);
    }
}
// Buscar
// Primero se busca dentro de la tabla
item *buscar(char* clave, Tabla tabla, int tam, int *colisiones, unsigned int dispersion(char *clave, int tamTabla))
{
    unsigned int i = dispersion(clave, tam);
    return buscar_lista(clave, tabla[i], colisiones);
}
// Después se busca dentro de la entrada
item *buscar_lista(char* clave, entrada entrada, int *colisiones)
{
    item *actual = entrada;
    while (actual != NULL)
    {
        if (strcmp(actual->clave, clave) == 0)
            return actual; // Encontrado
        actual = actual->siguiente;
        (*colisiones)++;
    }
    return NULL; // No encontrado
}

int insertar_abierta(char* clave, char *sinonimos, Tabla *tabla, int tam, int *colisiones, unsigned int (*dispersion)(char *, int))
{
    unsigned int i = dispersion(clave, tam);
    if (buscar(clave, *tabla, tam, colisiones, dispersion) == NULL)
    {
        insertar_entrada(clave, &((*tabla)[i]));
    }
    return *colisiones;
}

void insertar_entrada(char* clave, entrada *entrada)
{
    item *nuevoitem = (item *)malloc(sizeof(item));
    if (!nuevoitem) {
        printf("Error al asignar memoria\n");
        return;
    }
    strcpy(nuevoitem->clave, clave);
    nuevoitem->siguiente = *entrada;
    *entrada = nuevoitem;
}

// Memory
void liberar_memoria(Tabla tabla, int tam)
{
    int i; item *actual, *temp;
    for (i = 0; i < tam; i++)
    {
        actual = tabla[i];
        while (actual != NULL)
        {
            temp = actual;
            actual = actual->siguiente;
            free(temp);
        }
    }
}

// COSAS QUE NO HE DE TOCAR

unsigned int dispersionA(char *clave, int tamTabla)
{
    int i, n = MIN(8, strlen(clave));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++)
        valor += clave[i];
    return valor % tamTabla;
}

unsigned int dispersionB(char *clave, int tamTabla)
{
    int i, n = MIN(8, strlen(clave));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++)
        valor = (valor<<5) + clave[i]; /* el desplazamiento de 5 bits equivale a */
    return valor % tamTabla; /* multipicar por 32 */
}

int leer_sinonimos(item datos[])
{
    char c;
    int i, j;
    FILE *archivo;
    if ((archivo = fopen("sinonimos.txt", "r")) == NULL)
    {
        printf("Error al abrir 'sinonimos.txt'\n");
        return(EXIT_FAILURE);
    }
    for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++)
    {
        if ((c = fgetc(archivo)) != '\t')
        {
            printf("Error al leer el tabulador\n");
            return(EXIT_FAILURE);
        }
        for (j = 0; (c = fgetc(archivo)) != '\n'; j++)
        {
            if (j < LONGITUD_SINONIMOS - 1)
                datos[i].sinonimos[j] = c;
        }
        datos[i].sinonimos[MIN(j, LONGITUD_SINONIMOS -1)] = '\0';
    }
    if (fclose(archivo) != 0)
    {
        printf("Error al cerrar el fichero\n");
        return(EXIT_FAILURE);
    }
    return(i);
}