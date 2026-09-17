#include <stdlib.h>
#define N 1024

float A[N][N];
int B[N][N];

int main()
{
    float avg = 0;
    srand (12345);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[j][i] = rand();

    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++)
            B[i][j] = A[i][j] > N ? 0 : N ;

    return 0;
}
