# Barriers
``` c
int MPI_Barrier(MPI_COMM comm);

int main (int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int mpi_rank, mpi_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mp_size);

    for(int i = 0; i < mpi_size; i++)
    {
        if (i == mpi_rank)
            printf("Hello world from %d out of %d", mpi_rank, mpi_size);

        MPI_Barrier(MPI_COM_WORLD);
    }

    MPI_Finalize();
    
    return 0;

}

```
