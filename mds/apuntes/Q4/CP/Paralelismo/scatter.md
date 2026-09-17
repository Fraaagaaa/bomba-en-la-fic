``` c
#include <mpi.h>
#include <stdio.h>

MPI_Scatter(void *buff, int sencnt, MPI_Datatype sendtype, void *recvbuff, int recvcnt, MPI_Datatype recvtype, int root, MPI_Comm comm);

int main (int argc, char *argv[])
{
    int rank, mpi_size;
    int *data, *root_data;
    int recv;

    int l_size =  N / mpi_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    data = (int *) malloc (l_size * malloc (N * sizeof(int)));
    if(rank == 0)
    {
        root_data = (int *) malloc (N * sizeof(int));
        for(int i = 0; i < N; i++)
            root_data[i] = i;
    }

    // print_data(data, l_size, rank);
    // MPI_Barrier(MPI_COMM_WORLD)

    MPI_Scatter(root_data, l_size, MPI_INT, data, l_size, MPI_INT, 0, MPI_COMM_WORLD);
    print_data(data, l_size, rank);

    if(rank == 0)
        free(root_data);

    free(data)
    MPI_Finalize();
    
    return 0;
}

```