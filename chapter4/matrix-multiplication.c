#include <stdio.h>

#define UNUSED(x) (void)(x)
#define N 3

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    int A[N][N] = {
        { 1, 1, 1 },
        { 1, 1, 1 },
        { 1, 1, 1 }
    };

    int B[N][N] = {
        { 1, 1, 1 },
        { 1, 2, 1 },
        { 1, 1, 1 }
    };

    // Compute multiplication
    long long C[N][N];
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (size_t k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Display results
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            printf("%lli ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
