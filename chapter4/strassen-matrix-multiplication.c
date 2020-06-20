#include <stdio.h>
#include <math.h>

void multiply_matrices(size_t n, int A[n][n], int B[n][n], long long C[n][n]);

int main(int argc, char** argv)
{
    int A[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
    };

    int B[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };

    const size_t n = sqrt(sizeof A / sizeof(int));
    long long C[4][4];
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            C[i][j] = 0;
        }
    }

    multiply_matrices(n, A, B, C);

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

void multiply_matrices(size_t n, int A[n][n], int B[n][n], long long C[n][n])
{
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Divide
    int** A_11 = &A[0][0];      int** A_12 = &A[0][n/2];
    int** A_21 = &A[n/2][0];    int** A_22 = &A[n/2][n/2];
    int** B_11 = &B[0][0];      int** B_12 = &B[0][n/2];
    int** B_21 = &B[n/2][0];    int** B_22 = &B[n/2][n/2];
                       
    long long** C_11 = &C[0][0];   
    long long** C_12 = &C[0][n/2];
    long long** C_21 = &C[n/2][0]; 
    long long** C_22 = &C[n/2][n/2];

    // Compute multiplication
    multiply_matrices(n/2, A_11, B_11, C_11);
    multiply_matrices(n/2, A_12, B_21, C_11);

    multiply_matrices(n/2, A_11, B_12, C_12);
    multiply_matrices(n/2, A_12, B_22, C_12);

    multiply_matrices(n/2, A_21, B_11, C_21);
    multiply_matrices(n/2, A_22, B_21, C_21);

    multiply_matrices(n/2, A_21, B_12, C_22);
    multiply_matrices(n/2, A_22, B_22, C_22);
}
