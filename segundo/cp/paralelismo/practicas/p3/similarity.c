#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <mpi.h>

#define DEBUG 0
// EL normal da 383999162

/* Translation of the DNA bases
   A -> 0
   C -> 1
   G -> 2
   T -> 3
   N -> 4*/

#define M  1000000 // Number of sequences
#define N  200  // Number of bases per sequence

unsigned int g_seed = 0;

int fast_rand(void)
{
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16) % 5;
}

// The distance between two bases
int base_distance(int base1, int base2)
{
    if((base1 == 4) || (base2 == 4))
        return 3;

    if(base1 == base2)
        return 0;

    if((base1 == 0) && (base2 == 3))
        return 1;

    if((base2 == 0) && (base1 == 3))
        return 1;

    if((base1 == 1) && (base2 == 2))
        return 1;

    if((base2 == 2) && (base1 == 1))
        return 1;

    return 2;
}

int main(int argc, char *argv[] )
{
    int i, j;
    int *data1, *data2;
    int *result;
    int numProcs, rank;
    struct timeval  tv1, tv2, tv_comm1, tv_comm2;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int tamBlq = ceil((double)M / numProcs); // Truncado hacia arriba

    // Reservar la memoria solo el proceso 0
    if(rank == 0)
    {
        data1 = (int *)     malloc(tamBlq * numProcs * N * sizeof(int));
        data2 = (int *)     malloc(tamBlq * numProcs * N * sizeof(int));
        result = (int *)    malloc(tamBlq * numProcs * sizeof(int));
    }

    /* Initialize Matrices */
    if(rank == 0)
    {
        for(i = 0; i < M; i++)
        {
            for(j = 0; j < N; j++)
            {
                /* random with 20% gap proportion */
                data1[i*N+j] = fast_rand();
                data2[i*N+j] = fast_rand();
            }
        }
    }

    int *parte_matriz1, *parte_matriz2;
    int *local_result;

    parte_matriz1 = (int *) malloc(tamBlq * N * sizeof(int));
    parte_matriz2 = (int *) malloc(tamBlq * N * sizeof(int));
    local_result = (int *) malloc(tamBlq * sizeof(int));

    // inicio tiempo de comunicacion (scatter)
    gettimeofday(&tv_comm1, NULL);

    MPI_Scatter(data1, tamBlq * N, MPI_INT, parte_matriz1, tamBlq * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(data2, tamBlq * N, MPI_INT, parte_matriz2, tamBlq * N, MPI_INT, 0, MPI_COMM_WORLD);

    gettimeofday(&tv_comm2, NULL); // fin de comunicación
    int microseconds_scatter = (tv_comm2.tv_usec - tv_comm1.tv_usec) + 1000000 * (tv_comm2.tv_sec - tv_comm1.tv_sec);

    // Aqui ajustamos por si M no es múltiplo de los procesos

    int filasValidas;
    if(rank == numProcs - 1)
        filasValidas = M - (rank * tamBlq);
    else
        filasValidas = tamBlq;

    gettimeofday(&tv1, NULL); // Inicio tiempo de computación

    for(i = 0; i < tamBlq; i++) 
    {
        local_result[i] = 0;
        if(i < filasValidas)
        {
            for(j = 0; j < N; j++)
            {
                local_result[i] += base_distance(parte_matriz1[i * N + j], parte_matriz2[i * N + j]);
            }
        }
    }

    gettimeofday(&tv2, NULL);
    // fin tiempo computación
    double segundos_comp = ((tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) / 1000000.0);

    gettimeofday(&tv_comm1, NULL); // inicio tiempo de comunicación (gather) 

    MPI_Gather(local_result, tamBlq, MPI_INT, result, tamBlq, MPI_INT, 0, MPI_COMM_WORLD);

    gettimeofday(&tv_comm2, NULL);  // fin tiempo de comunicación (gather)


    int microseconds_gather = (tv_comm2.tv_usec - tv_comm1.tv_usec) + 1000000 * (tv_comm2.tv_sec - tv_comm1.tv_sec);
    double segundos_comm = (microseconds_scatter + microseconds_gather) / 1000000.0;

    if(rank == 0)
    {
        /* Display result */
        if (DEBUG == 1)
        {
            int checksum = 0;
            for(i=0;i<M;i++) {
                checksum += result[i];
            }
            printf("Checksum: %d\n ", checksum);
        }
        else if (DEBUG == 2)
        {
            for(i=0;i<M;i++)
            {
                printf(" %d \t ",result[i]);
            }
        }
    }
    if(DEBUG == 0)
    {
        // Mandar los tiempos al proceso 0
        if(rank != 0)
        {
            MPI_Send(&segundos_comm, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&segundos_comp, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
        if(rank == 0)
        {
            // El primero ya lo puede printear
            printf("Proceso %2d | Computación: %lf s | Comunicación: %lf s\n", rank, segundos_comp, segundos_comm);
            for(i = 1; i < numProcs; i++)
            {
                MPI_Recv(&segundos_comm, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&segundos_comp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Proceso %2d | Computación: %lf s | Comunicación: %lf s\n", i, segundos_comp, segundos_comm);
            }
        }
    }

    if(rank == 0)
    {
        free(data1); free(data2); free(result);
    }

    free(parte_matriz1); free(parte_matriz2); free(local_result);

    MPI_Finalize();
    return 0;
}
