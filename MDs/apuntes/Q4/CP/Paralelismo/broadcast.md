``` c
#include <mpi.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    int rank, data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
        data = 42;
    }

    printf("Proceso %d tiene data = %d\n", rank, data);
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Proceso %d tiene data = %d\n", rank, data);

    MPI_Finalize();
    
    return 0;
}

```