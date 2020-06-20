#include <stdio.h>
#include <math.h>

#define n 3

int main(int argc, char** argv)
{
    int A[n][n] = {
        { 1, 1, 1 },
        { 1, 1, 1 },
        { 1, 1, 1 }
    };

    int B[n][n] = {
        { 1, 1, 1 },
        { 1, 2, 1 },
        { 1, 1, 1 }
    };

    // Compute multiplication
    long long C[n][n];
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (size_t k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Display results
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            printf("%lli ", C[i][j]);
        }

        printf("\n");
    }

    return 0;
}
