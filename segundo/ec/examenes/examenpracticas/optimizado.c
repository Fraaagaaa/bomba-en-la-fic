#define N 18000
double v1 [N], v2[N];
int main()
{
    for (int i = 0; i < N; ++i)
    {
        v1[i] = (i + 1) * 1.0f;
        v1[i] += (i/2) * 3.1416f; 
        v2[i] = v1[i] * 0.5f;   
    }
    return 0;
}
