``` c
#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

// MPI_Reduce(void *buff, void *recvbuff, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
//
// MPI_{MAX, MIN, SUM, PROD}
// MPI_{LAND, LOR, LEXOR}  // logicas
// MPI_{BAND, BOR, BXOR} // bitwise
// MPI_{MAXLOC, MINLOC}
#define N 1e7
int is_prime(int x)
{
    if(x < 2) return 0;
    for (int i = 2; i * i <= x; i++)
        if(x % i == 0) return 0;
    return 1;
}

int main (int argc, char *argv[])
{
    int rank, mpi_size;
    int recv;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    long l_sum = 0, l_pmax = 0, sum = 0, pmax = 0;
    int l_count = 0, count = 0;

    double t_start = MPI_Wtime(); 

    for(int i = rank; i < N; i += mpi_size)
    {
        if(is_prime(i))
        {
            l_sum += i;
            l_count++;
            l_pmax = i;
        }
    }

    double t_end = MPI_Wtime();
    double local_time = t_end - t_start;

    printf("Process %d [LOCAL] Count = %d, Sum = %ld, Max = %ld, in %lf seconds\n", rank, l_count, l_sum, l_pmax, local_time);

    MPI_Reduce(&l_sum, &sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&l_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&l_pmax, &pmax, 1, MPI_LONG, MPI_MAX, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        usleep(5e5);
        printf("\nGlobal Prime Sum = %ld\n", sum);
        printf("Global Prime Count = %d\n", count);
        printf("Global Max Prime = %ld\n", pmax);
    }

    MPI_Finalize();
    
    return 0;
}
```