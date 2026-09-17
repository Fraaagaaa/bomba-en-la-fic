#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int MPI_BinomialColectiva(
  void *buffer,
  int count,
  MPI_Datatype datatype,
  int root,
  MPI_Comm comm
)
{
    int rank, numprocs, err;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &numprocs);
    // Asumiendo root es 0 por simplicidad como indica la practica
    
    if(rank != root)
    {
        err = MPI_Recv(buffer, count, datatype, MPI_ANY_SOURCE, 0, comm, MPI_STATUS_IGNORE);
    }

    for (int step = 1; step < numprocs; step *= 2)
    {
        if ((rank < step) && (rank + step) < numprocs)
        {
            err = MPI_Send(buffer, count, datatype, rank + step, 0, comm);
            if (err != MPI_SUCCESS) return err;
        }
    }
    return MPI_SUCCESS;
}

int MPI_FlattreeColectiva(
        void *sendbuf,
        void *recvbuf,
        int count,
        MPI_Datatype datatype,        // ASUMIMOS MPI_INT
        MPI_Op op,    // ASUMIMOS QUE ES SUM
        int root,
        MPI_Comm comm
        )
{
    int rank, numprocs, error;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &numprocs);

    int *sendptr = (int*)sendbuf;
    int *recvptr = (int*)recvbuf;

    if(rank == root)
    {
        for(int i = 0; i < count; i++)
        {
            recvptr[i] = sendptr[i];
        }
        int *temp_buffer = (int*)malloc(count * sizeof(int));

        for(int i = 0; i < numprocs; i++)
        {
            if(i != root)
            {
                error = MPI_Recv(temp_buffer, count, MPI_INT, i, 0, comm, MPI_STATUS_IGNORE);
                if(error != MPI_SUCCESS)
                {
                    free(temp_buffer);
                    return error;
                }

                for(int j = 0; j < count; j++)
                    recvptr[j] += temp_buffer[j];
            }
        }
        free(temp_buffer);
    }
    else
    {
        error = MPI_Send(sendptr, count, MPI_INT, root, 0, comm);
        if(error != MPI_SUCCESS) return error;
    }

    return MPI_SUCCESS;
}

void inicializaCadena(char *cadena, int n){
    int i;
    for(i=0; i<n/2; i++){
        cadena[i] = 'A';
    }
    for(i=n/2; i<3*n/4; i++){
        cadena[i] = 'C';
    }
    for(i=3*n/4; i<9*n/10; i++){
        cadena[i] = 'G';
    }
    for(i=9*n/10; i<n; i++){
        cadena[i] = 'T';
    }
}

int main(int argc, char *argv[])
{
    int i, n, count=0, total_count=0;
    int numProcs, rank;
    char *cadena;
    char L;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if(rank == 0)
    {
        if(argc != 3){
            printf("Numero incorrecto de parametros\nLa sintaxis debe ser: program n L\n  program es el nombre del ejecutable\n  n es el tamaño de la cadena a generar\n  L es la letra de la que se quiere contar apariciones (A, C, G o T)\n");
            exit(1); 
        }
        n = atoi(argv[1]);
        L = *argv[2];
    }

    MPI_BinomialColectiva(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    cadena = (char *) malloc(n*sizeof(char));
    if(rank == 0) 
        inicializaCadena(cadena, n);
    MPI_BinomialColectiva(cadena, n, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_BinomialColectiva(&L, 1, MPI_CHAR, 0, MPI_COMM_WORLD);


    for(i=rank; i<n; i+=numProcs)
        if(cadena[i] == L)
            count++;


    MPI_FlattreeColectiva(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
        printf("El numero de apareciones de la letra %c es %d\n", L, total_count);

    MPI_Finalize();
    free(cadena);
}
