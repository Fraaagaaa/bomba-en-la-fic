
//DEFINICIÓN DE LIBRERÍAS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

//DEFINICIÓN DE CONSTANTES
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define K 1000



//DEFINICIÓN DE TYPEDEFS

//struct de la entrada al diccionario
typedef struct entrada_ {
	int ocupada;
	char clave [LONGITUD_CLAVE];
	char sinonimos [LONGITUD_SINONIMOS];
} entrada;


typedef int pos;

typedef entrada *tabla_cerrada;

typedef struct {
	char clave [LONGITUD_CLAVE];
	char sinonimos [LONGITUD_SINONIMOS];
} item;


//UNSIGNED INTS
unsigned int dispersionA(char *clave, int tamTabla) {
    int i, n = MIN(8, strlen(clave));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++)
	    valor += clave[i];
    return valor % tamTabla;
}

unsigned int dispersionB(char *clave, int tamTabla) {
	int i, n = MIN(8, strlen(clave));
	unsigned int valor = clave[0];
	for (i = 1; i < n; i++)
	valor = (valor<<5) + clave[i]; /* el desplazamiento de 5 bits equivale a */
	return valor % tamTabla; /* multipicar por 32 */
}

//FUNCIÓN MICROSEGUNDOS
double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla () {
	srand(time(NULL));
}


//FUNCIONES DISPERSIÓN CERRADA

//RESOL COLISIONES
unsigned int resol_lineal(int pos_ini, int num_intento) {
	return (unsigned int)(num_intento);
}

unsigned int resol_cuadratica(int pos_ini, int num_intento) {
	return (unsigned int) pow(num_intento,2);
}

unsigned int resol_doble(int pos_ini, int num_intento) {
	return (unsigned int) (num_intento*(10007 - (pos_ini % 10007)));
}




void inicializar_cerrada(tabla_cerrada *diccionario, int tam)
{
	int i;
	for (i=0;i<tam;i++){
        (*diccionario)[i].clave[0] = '\0';
        (*diccionario)[i].sinonimos[0] = '\0';
		(*diccionario)[i].ocupada=0;
	}
}

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
					int *colisiones, unsigned int (*dispersion)(char *, int),
					unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
{
	int i =0;
	int x= dispersion(clave, tam);
	pos posActual=x;

	while(diccionario[posActual].ocupada!=0 && strcmp(diccionario[posActual].clave, clave)!=0){
		i+=1;
		posActual=(x+ resol_colisiones(x, i))%tam;
	}

	*colisiones=i;
	return posActual;
	
}



int insertar_cerrada(char *clave, char *sinonimos, tabla_cerrada *diccionario, int tam,unsigned int (*dispersion)(char *, int),unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
{
	int colisiones=0;
	pos posicion=buscar_cerrada(clave,*diccionario,tam,&colisiones,dispersion,resol_colisiones);
	
	if((*diccionario)[posicion].ocupada!=1){
		strcpy((*diccionario)[posicion].clave,clave);
		strcpy((*diccionario)[posicion].sinonimos,sinonimos);
		(*diccionario)[posicion].ocupada=1;
		
	}
	return colisiones;
}

void mostrar_cerrada(tabla_cerrada diccionario, int tam) {
	int i;
	printf("{\n");
    for (i = 0; i < tam; i++) {
        if (diccionario[i].ocupada==1) {
            printf("%d- (%s )\n", i, diccionario[i].clave);
        } else if(diccionario[i].ocupada==0){
            printf("%d-\n", i);
        }
    }
    printf("}\n");
}


//función  con el ejemplo visto en clase
int ndispersion(char *clave, int tamTabla) {
	if (strcmp(clave, "ANA")==0) return 7;
	if (strcmp(clave, "JOSE")==0) return 7;
	if (strcmp(clave, "OLGA")==0) return 7;
	return 6;
}

unsigned int dispersion(char *clave, int tamTabla) {
	return (unsigned int)ndispersion(clave, tamTabla);
}







int leer_sinonimos(item datos[]) {
	char c;
	int i, j;
	FILE *archivo;
	if ((archivo = fopen("sinonimos.txt", "r")) == NULL) {
		printf("Error al abrir ’sinonimos.txt’\n");
		return(EXIT_FAILURE);
	}
	for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++) {
		if ((c = fgetc(archivo)) != '\t') {
			printf("Error al leer el tabulador\n");
			return(EXIT_FAILURE);
		}
		for (j = 0; (c = fgetc(archivo)) != '\n'; j++) {
			if (j < LONGITUD_SINONIMOS - 1)
			datos[i].sinonimos[j] = c;
		}
		datos[i].sinonimos[MIN(j, LONGITUD_SINONIMOS -1)] = '\0';
	}
	if (fclose(archivo) != 0) {
		printf("Error al cerrar el fichero\n");
		return(EXIT_FAILURE);
	}
	return(i);
}

void test(tabla_cerrada *d,unsigned int (*resol_colisiones)(int pos_ini, int intentos), int tamTabla){
	int i;
	pos posicion;
    inicializar_cerrada(d, tamTabla);
	char* claves[] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN","CARLOS"};
	int colisionesTot=0, colisiones ,colisiones_busqueda;

    for (i=0;i<6; i++) {
    	colisiones=insertar_cerrada(claves[i], "nombre propio", d, tamTabla, dispersion,resol_colisiones);
    	colisionesTot+=colisiones;

    }
    mostrar_cerrada(*d, tamTabla);

	printf("Numero total de colisiones al insertar los elementos: %d\n\n", colisionesTot);

    for (i = 0; i < 7; i++) {
    	colisiones_busqueda=0;
       
        posicion = buscar_cerrada(claves[i], *d, tamTabla, &colisiones_busqueda, dispersion, resol_colisiones);
        if (strcmp((*d)[posicion].clave, claves[i])==0) {
            printf("Al buscar: %s, encuentro: %s, colisiones: %d\n", claves[i], (*d)[posicion].clave, colisiones_busqueda);
        } else {
            printf("No encuentro: %s, colisiones: %d\n\n", claves[i], colisiones_busqueda);
        }
    }
    
}


void testS(tabla_cerrada *d, unsigned int (*resol_colisiones)(int pos_ini, int intentos), unsigned int (*disp)(char *clave, int tamTabla),  int tamS,item datos[], int numDatos) {
	int i;
    int colisionesTot=0, colisiones;

	inicializar_cerrada(d, tamS);
	
    for (i=0;i<numDatos; i++) {
    	colisiones=insertar_cerrada(datos[i].clave, datos[i].sinonimos, d, tamS, disp,resol_colisiones);
    	colisionesTot+=colisiones;
    }

    printf("Insertando %d elementos... Numero total de colisiones: %d\n", tamS, colisionesTot);

}


//FUNCIÓN DE TIEMPOS
double tiempo(unsigned int (*disp)(char*, int),
              unsigned int (*resol_colisiones)(int, int), int tam,
              tabla_cerrada *d, item datos[], int num_datos, int n){
             
    double t1, t2, ta, tb, t, aux;
    int i, j, k, random; 
    int colisiones = 0;

    t1 = microsegundos();
    for (i = 0; i <= n; i++){
        random = rand() % num_datos;
        buscar_cerrada(datos[random].clave, *d, tam, 
                       &colisiones, disp, resol_colisiones);
    }
    t2 = microsegundos();
    ta = t2 - t1;
    
    t1 = microsegundos();
    for (i = 0; i <= n; i++){
        random = rand() % num_datos;
    }
    t2 = microsegundos();
    tb = t1 - t2;
    
    t = ta - tb;

    if (t < 500) {
        t1 = microsegundos();
        for (k = 0; k < K; k++){
            for (j = 0; j <= n; j++){
                 random = rand() % num_datos;
            }
        }
        t2 = microsegundos();
        aux = t2 - t1;
        t1 = microsegundos();
        for (k = 0; k < K; k++){
            for (j = 0; j <= n; j++){
                random = rand() % num_datos;
                buscar_cerrada(datos[random].clave, *d, tam,
                               &colisiones, disp, resol_colisiones);
            }
        }
        t2 = microsegundos();
        
        t = (t2 - t1 - aux) / k;
    }
    return t;
}

void printComplejidadLinealA(tabla_cerrada *d, int tam, item datos[], int numDatos) {    
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95\t           t(n)/n"
             "   t(n)/(n*log(n))\n");

    for (i = 125; i <=16000; i*=2) {
        t = tiempo(dispersionA, resol_lineal, tam, d, datos, numDatos, i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / i, t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / i, t / (i * log(i)));
        }
    }
}

void printComplejidadLinealB(tabla_cerrada *d, int tam, item datos[], int numDatos) {    
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95\t      t(n)/n^1.05"
             "   t(n)/(n*log(n))\n");

    for (i = 125; i <=16000; i*=2) {

        t = tiempo(dispersionB, resol_lineal, tam, d, datos, numDatos, i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i, 1.05), t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i, 1.05), t / (i * log(i)));
        }
    }
}

void printComplejidadCuadraticaA(tabla_cerrada *d, int tam, item datos[], int numDatos) {    
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95\t           t(n)/n"
             "   t(n)/(n*log(n))\n");

    for (i = 125; i <=16000; i*=2) {

        t = tiempo(dispersionA, resol_cuadratica, tam, d, datos, numDatos, i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / i, t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / i, t / (i * log(i)));
        }
    }
}

void printComplejidadCuadraticaB(tabla_cerrada *d, int tam, item datos[], int numDatos) {    
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95       t(n)/n^1.05"
             "   t(n)/(n*log(n))\n");

    for (i = 125; i <=16000; i*=2) {
        t = tiempo(dispersionB, resol_cuadratica, tam, d, datos, numDatos, i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i, 1.05), t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i, 1.05), t / (i * log(i)));
        }
    }
}

void printComplejidadDobleA(tabla_cerrada *d, int tam, item datos[], int numDatos) {    
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95\t           t(n)/n"
             "   t(n)/(n*log(n))\n");

    for (i = 125; i <=16000; i*=2) {

        t = tiempo(dispersionA, resol_doble, tam, d, datos, numDatos, i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i,1), t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i,1), t / (i * log(i)));
        }
    }
}

void printComplejidadDobleB(tabla_cerrada *d, int tam, item datos[], int numDatos) {    
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95       t(n)/n^1.05"
             "   t(n)/(n*log(n))\n");

    for (i = 125; i <=16000; i*=2) {

        t = tiempo(dispersionA, resol_doble, tam, d, datos, numDatos, i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i, 1.05), t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i, 1.05), t / (i * log(i)));
        }
    }
}


int main(){
	tabla_cerrada d;
	int tamS =38197;
	item datos[19062];
	int numDatos = leer_sinonimos(datos);
	
 	
	int tamTabla =11;
	
	inicializar_semilla();
	

	
	d = malloc(38197 * sizeof(entrada));
	inicializar_cerrada(&d, tamTabla);
	//CERRADA LINEAL
	printf("***TABLA CERRADA LINEAL\n");
	test(&d,resol_lineal,tamTabla);


	//CERRADA CUADRÁTICA
	printf("***TABLA CERRADA CUADRÁTICA\n");
	test(&d,resol_cuadratica,tamTabla);

	//CERRADA LINEAL
	printf("***TABLA CERRADA DOBLE\n");
	test(&d,resol_doble,tamTabla);


	//SINÓNIMOS
	printf("***Dispersión cerrada lineal con dispersión A\n");
	testS(&d, resol_lineal, dispersionA, tamS,datos,numDatos);
    printComplejidadLinealA(&d, tamS, datos, numDatos);

	printf("\n***Dispersión cerrada lineal con dispersión B\n");
	testS(&d, resol_lineal, dispersionB,  tamS,datos,numDatos);
    printComplejidadLinealB(&d, tamS, datos, numDatos);


	printf("\n***Dispersión cerrada cuadratica con dispersión A\n");
	testS(&d, resol_cuadratica, dispersionA, tamS,datos,numDatos);
    printComplejidadCuadraticaA(&d, tamS, datos, numDatos);

	printf("\n***Dispersión cerrada cuadratica con dispersión B\n");
	testS(&d, resol_cuadratica, dispersionB, tamS,datos,numDatos);
	printComplejidadCuadraticaB(&d, tamS, datos, numDatos);



	printf("\n***Dispersión cerrada doble con dispersión A\n");
	testS(&d, resol_doble, dispersionA,  tamS,datos,numDatos);
    printComplejidadDobleA(&d, tamS, datos, numDatos);

	printf("\n***Dispersión cerrada doble con dispersión B\n");
	testS(&d, resol_doble, dispersionB, tamS,datos,numDatos);
    printComplejidadDobleB(&d, tamS, datos, numDatos);

	free(d);
	return 0;
}