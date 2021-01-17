#include <stdio.h>

#define UNUSED(x) (void)(x)
#define N 4 

void multiplyMatrix(size_t n, int A[n][n], int B[n][n], int C[n][n]);
void partitionMatrix(
        size_t n, int A[n][n], 
        int A_11[n/2][n/2], int A_12[n/2][n/2], 
        int A_21[n/2][n/2], int A_22[n/2][n/2]
);
void addMatrix(size_t n, int A[n][n] , int B[n][n], int C[n][n]);
void printMatrix(size_t nRows, size_t nCols, int matrix[nRows][nCols]);
int countDigits(int n);

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    int A[N][N] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
    };

    int B[N][N] = {
        {  10,  20,  30,  40 },
        {  50,  60,  70,  80 },
        {  90, 100, 110, 120 },
        { 130, 140, 150, 160 }
    };

    int C[N][N];
    multiplyMatrix(N, A, B, C);

    printMatrix(N, N, A);
    printMatrix(N, N, B);
    printMatrix(N, N, C);
    
    return 0;
}

void multiplyMatrix(size_t n, int A[n][n] , int B[n][n], int C[n][n])
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
    }
    else
    {
        // Partition the matrix
        int A_11[n/2][n/2], A_12[n/2][n/2],
            A_21[n/2][n/2], A_22[n/2][n/2];
        int B_11[n/2][n/2], B_12[n/2][n/2],
            B_21[n/2][n/2], B_22[n/2][n/2];
        int C_11[n/2][n/2], C_12[n/2][n/2],
            C_21[n/2][n/2], C_22[n/2][n/2];
        partitionMatrix(n, A, A_11, A_12, A_21, A_22);
        partitionMatrix(n, B, B_11, B_12, B_21, B_22);

        // Multiply the partitions
        int C_11_1[n/2][n/2],
            C_11_2[n/2][n/2];
        multiplyMatrix(
            n / 2,
            A_11,
            B_11,
            C_11_1
        );
        multiplyMatrix(
            n / 2,
            A_12,
            B_21,
            C_11_2
        );
        addMatrix(n / 2, C_11_1, C_11_2, C_11);
                
        int C_12_1[n/2][n/2],
            C_12_2[n/2][n/2];
        multiplyMatrix(
            n / 2,
            A_11,
            B_12,
            C_12_1
        );
        multiplyMatrix(
            n / 2,
            A_12,
            B_22,
            C_12_2
        );
        addMatrix(n / 2, C_12_1, C_12_2, C_12);

        int C_21_1[n/2][n/2],
            C_21_2[n/2][n/2];
        multiplyMatrix(
            n / 2,
            A_21,
            B_11,
            C_21_1
        );
        multiplyMatrix(
            n / 2,
            A_22,
            B_21,
            C_21_2
        );
        addMatrix(n / 2, C_21_1, C_21_2, C_21);

        int C_22_1[n/2][n/2],
            C_22_2[n/2][n/2];
        multiplyMatrix(
            n / 2,
            A_21,
            B_12,
            C_22_1
        );
        multiplyMatrix(
            n / 2,
            A_22,
            B_22,
            C_22_2
        );
        addMatrix(n / 2, C_22_1, C_22_2, C_22);

        // Combine the sub-matrices
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if (i < n/2 && j < n/2)
                {
                    C[i][j] = C_11[i][j];
                }
                else if (i < n/2 && j >= n/2)
                {
                    size_t col = j - n/2;
                    C[i][j] = C_12[i][col];
                }
                else if (i >= n/2 && j < n/2)
                {
                    size_t row = i - n/2;
                    C[i][j] = C_21[row][j];
                }
                else if (i >= n/2 && j >= n/2)
                {
                    size_t row = i - n/2;
                    size_t col = j - n/2;
                    C[i][j] = C_22[row][col];
                }
            }
        }
    }
}

void partitionMatrix(
        size_t n, int A[n][n], 
        int A_11[n/2][n/2], int A_12[n/2][n/2], 
        int A_21[n/2][n/2], int A_22[n/2][n/2]
)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i < n/2 && j < n/2)
            {
                A_11[i][j] = A[i][j];
            }
            else if (i < n/2 && j >= n/2)
            {
                size_t col = j - n/2;
                A_12[i][col] = A[i][j];
            }
            else if (i >= n/2 && j < n/2)
            {
                size_t row = i - n/2;
                A_21[row][j] = A[i][j];
            }
            else if (i >= n/2 && j >= n/2)
            {
                size_t row = i - n/2;
                size_t col = j - n/2;
                A_22[row][col] = A[i][j];
            }
        }
    }
}


void addMatrix(size_t n, int A[n][n], int B[n][n], int C[n][n])
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void printMatrix(size_t nRows, size_t nCols, int matrix[nRows][nCols])
{
    // Find max # digits
    int maxDigits = 0;
    for (size_t i = 0; i < nRows; i++)
    {
        for (size_t j = 0; j < nCols; j++)
        {
            int numDigits = countDigits(matrix[i][j]);
            if (numDigits > maxDigits) maxDigits = numDigits;
        }
    }

    // Print matrix
    for (size_t i = 0; i < nRows; i++)
    {
        for (size_t j = 0; j < nCols; j++)
        {
            printf("%*i ", maxDigits, matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int countDigits(int n)
{
    int count = 0;
    while (n) 
    {
        n /= 10;
        count++;
    }
    return count;
}
