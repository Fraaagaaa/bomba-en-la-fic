#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <mpi.h>

#define T 100
#define P 100


int read(void * a){ return 1;}
void imprime_resultados(int *a, int *b){}
void inicializa_datos(int *pedido, float* pesos, float* precios){}
void memsets(float *a, int b, int c){}

int main(int argc, char *argv[] )
{
    int rank, numProcs;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int i,j,k;
    int pedido [ T ][ P ] , tienda_id ;
    float pesos [ P ] , precios [ P ] , wp [ P ] , ps [ T ];

    inicializa_datos ( pedido , pesos , precios );
    memsets( ps , 0 , T * sizeof ( float ) );
    memsets( wp , 0 , P * sizeof ( float ) );

    int Bsize = ceil((double)T/numProcs);
    int Tpadded = Bsize * numProcs;

    int pedidos[Tpadded][P];

    // Uno para pesos y otro para precios
    // MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
    // MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)


    // MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

    int Bsize2 = (rank < numProcs -1) ? Bsize : (T - Bsize * rank);
    for (i = 0; i < P; i++)
    {
        for(k = 0; k < Bsize2; k ++)
        {
            wp [ i ] += pesos [ i ] * pedido [ k ][ i ];
            ps [ k ] += precios [ i ] * pedido [ k ][ i ];
        }
    }


    while (read(&tienda_id))
    {
        if(ceil(tienda_id / Bsize == rank))
            printf ( " Los productos de la tienda %d cuestan %f euros \n ",tienda_id , ps [ tienda_id % Bsize ]);
    }

    // MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
    // MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)

    if(!rank)
        imprime_resultados ( wp , ps );
}

