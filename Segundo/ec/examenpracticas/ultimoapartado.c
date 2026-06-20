#define N 2
int i, j;
float a[N][N];

int main()
{
    a[0][0] = 2;
    a[0][1] = 6;
    a[1][0] = 3;
    a[1][1] = 8;
    for(i = 1; i < (N-1); i++)
        for(j = 1; j < (N-1); j++)
        {
            a[j][i] = a [j+1][i-1];
        }
}
