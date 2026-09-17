``` c
#include <mpi.h>
#include <stdio.h>

MPI_Gather(void *buff, int sencnt, MPI_Datatype sendtype, void *recvbuff, int recvcnt, MPI_Datatype recvtype, int root, MPI_Comm comm);

int main (int argc, char *argv[])
{
    int rank, mpi_size;
    int *data, *root_data;
    int recv;

    int l_size =  N / mpi_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    data = (int *) malloc (l_size * malloc (N * sizeof(int)));
    for(int i 0 0; i < l_size; i++)
        data[i] = rank;

    if(rank == 0)
    {
        root_data = (int *) malloc (N * sizeof(int));
    }

    // print_data(data, l_size, rank);
    // MPI_Barrier(MPI_COMM_WORLD)

    MPI_Gather(data, l_size, MPI_INT, root_data, l_size, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        print_data(root_data, N, rank);
        free(root_data);
    }

    free(data)
    MPI_Finalize();
    
    return 0;
}

```