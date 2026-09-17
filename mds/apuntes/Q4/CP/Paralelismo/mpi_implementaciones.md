``` c
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    // Entre enstas dos llamadas es donde podemos enviar mensajes a procesos
    MPI_Finalize();
    return 0;
}
```

todas las funciones devuelven int `int MPI_Function(...)`, va a devolver una de estas constantes:
`MPI_SUCCESS` o `MPI_ERR_?`

``` c
#include <mpi.h>

int main(int argc, char *argv[])
{
    int numprocs, rank;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Process %d on %s out of %d\n", rank, processor_name, numprocs);

    MPI_Finalize();
    return 0;
}
```
