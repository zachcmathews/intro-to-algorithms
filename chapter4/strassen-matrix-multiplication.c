#include <stdio.h>
#include <stdlib.h>

#define N 4 
#define UNUSED(x) (void)(x)

int countDigits(int n);

typedef struct PartitionableMatrix {
    size_t rowOffset;
    size_t colOffset;
    size_t nRows;
    size_t nCols;
    size_t nRowsPartition;
    size_t nColsPartition;
    int* matrix;
} PartitionableMatrix;

PartitionableMatrix* createPartitionableMatrix(size_t, size_t);
void destroyPartitionableMatrix(PartitionableMatrix*);

void partitionMatrixIntoQuadrants(
    PartitionableMatrix*,
    PartitionableMatrix*, PartitionableMatrix*,
    PartitionableMatrix*, PartitionableMatrix*
);
int* getPartitionableMatrixEntry(PartitionableMatrix*, size_t, size_t);
void printPartitionableMatrix(PartitionableMatrix*);

void multiplyPartitionableMatrix(
    PartitionableMatrix*,
    PartitionableMatrix*,
    PartitionableMatrix*
);
void addPartitionableMatrix(
    PartitionableMatrix*, 
    PartitionableMatrix*, 
    PartitionableMatrix*
);
void subtractPartitionableMatrix(
    PartitionableMatrix*, 
    PartitionableMatrix*, 
    PartitionableMatrix*
);

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    int A_mat[N][N] = {
        { 1, 1, 1, 1 },
        { 1, 1, 1, 1 },
        { 1, 1, 1, 1 },
        { 1, 1, 1, 1 }
    };
    PartitionableMatrix A = {
        .rowOffset = 0,
        .colOffset = 0,
        .nRows = N,
        .nCols = N,
        .nRowsPartition = N,
        .nColsPartition = N,
        .matrix = (int *) A_mat
    };
    printPartitionableMatrix(&A);

    int B_mat[N][N] = {
        {  10,  20,  30,  40 },
        {  50,  60,  70,  80 },
        {  90, 100, 110, 120 },
        { 130, 140, 150, 160 }
    };
    PartitionableMatrix B = {
        .rowOffset = 0,
        .colOffset = 0,
        .nRows = N,
        .nCols = N,
        .nRowsPartition = N,
        .nColsPartition = N,
        .matrix = (int *) B_mat
    };
    printPartitionableMatrix(&B);

    int C_mat[N][N];
    PartitionableMatrix C = {
        .rowOffset = 0,
        .colOffset = 0,
        .nRows = N,
        .nCols = N,
        .nRowsPartition = N,
        .nColsPartition = N,
        .matrix = (int *) C_mat
    };
    multiplyPartitionableMatrix(&A, &B, &C);
    printPartitionableMatrix(&C);

    return 0;
}

PartitionableMatrix* createPartitionableMatrix(size_t nRows, size_t nCols)
{
    PartitionableMatrix* pMat = 
        (PartitionableMatrix*) malloc(sizeof(PartitionableMatrix));

    pMat->rowOffset = 0;
    pMat->colOffset = 0;
    pMat->nRows = nRows;
    pMat->nCols = nCols;
    pMat->nRowsPartition = nRows;
    pMat->nColsPartition = nCols;
    pMat->matrix = (int *) malloc(N * N * sizeof(int));

    return pMat;
}

void destroyPartitionableMatrix(PartitionableMatrix* pMat)
{
    free(pMat->matrix);
    free(pMat);
}

void partitionMatrixIntoQuadrants(
    PartitionableMatrix* pMat,
    PartitionableMatrix* pMat_11, PartitionableMatrix* pMat_12,
    PartitionableMatrix* pMat_21, PartitionableMatrix* pMat_22
)
{
    pMat_11->rowOffset = pMat->rowOffset;
    pMat_11->colOffset = pMat->colOffset;
    pMat_11->nRows = pMat->nRows;
    pMat_11->nCols = pMat->nCols;
    pMat_11->nRowsPartition = pMat->nRowsPartition / 2;
    pMat_11->nColsPartition = pMat->nColsPartition / 2;
    pMat_11->matrix = pMat->matrix;
    
    pMat_12->rowOffset = pMat->rowOffset;
    pMat_12->colOffset = pMat->colOffset + pMat->nColsPartition / 2;
    pMat_12->nRows = pMat->nRows;
    pMat_12->nCols = pMat->nCols;
    pMat_12->nRowsPartition = pMat->nRowsPartition / 2;
    pMat_12->nColsPartition = pMat->nColsPartition / 2;
    pMat_12->matrix = pMat->matrix;

    pMat_21->rowOffset = pMat->rowOffset + pMat->nRowsPartition / 2;
    pMat_21->colOffset = pMat->colOffset;
    pMat_21->nRows = pMat->nRows;
    pMat_21->nCols = pMat->nCols;
    pMat_21->nRowsPartition = pMat->nRowsPartition / 2;
    pMat_21->nColsPartition = pMat->nColsPartition / 2;
    pMat_21->matrix = pMat->matrix;

    pMat_22->rowOffset = pMat->rowOffset + pMat->nRowsPartition / 2;
    pMat_22->colOffset = pMat->colOffset + pMat->nColsPartition / 2;
    pMat_22->nRows = pMat->nRows;
    pMat_22->nCols = pMat->nCols;
    pMat_22->nRowsPartition = pMat->nRowsPartition / 2;
    pMat_22->nColsPartition = pMat->nColsPartition / 2;
    pMat_22->matrix = pMat->matrix;
}


int* getPartitionableMatrixEntry(
        PartitionableMatrix* pMat,
        size_t row,
        size_t col
)
{
    size_t nCols = pMat->nCols;
    size_t rowOffset = pMat->rowOffset;
    size_t colOffset = pMat->colOffset;

    int (*matrix)[nCols] = (int (*)[nCols]) pMat->matrix;
    return &matrix[row + rowOffset][col + colOffset];
}

void printPartitionableMatrix(PartitionableMatrix* pMat)
{
    size_t nRows = pMat->nRowsPartition;
    size_t nCols = pMat->nColsPartition;

    // Find max # digits
    int maxDigits = 0;
    for (size_t i = 0; i < nRows; i++)
    {
        for (size_t j = 0; j < nCols; j++)
        {
            int* entry = getPartitionableMatrixEntry(pMat, i, j);
            int numDigits = countDigits(*entry);
            if (numDigits > maxDigits) maxDigits = numDigits;
        }
    }

    // Print matrix
    for (size_t i = 0; i < nRows; i++)
    {
        for (size_t j = 0; j < nCols; j++)
        {
            int* entry = getPartitionableMatrixEntry(pMat, i, j);
            printf("%*i ", maxDigits, *entry);
        }
        printf("\n");
    }
    printf("\n");
}

void multiplyPartitionableMatrix(
    PartitionableMatrix* A, 
    PartitionableMatrix* B,
    PartitionableMatrix* C
)
{
    if (
        A->nRowsPartition == 1 && A->nColsPartition == 1
        && B->nRowsPartition == 1 && B->nColsPartition == 1
        && C->nRowsPartition == 1 && C->nColsPartition == 1
    )
    {
        int* A_entry = getPartitionableMatrixEntry(A, 0, 0);
        int* B_entry = getPartitionableMatrixEntry(B, 0, 0);
        int* C_entry = getPartitionableMatrixEntry(C, 0, 0);

        *C_entry = *A_entry * *B_entry;
        return;
    }

    // Partition matrices
    PartitionableMatrix A_11, A_12,
                        A_21, A_22;
    partitionMatrixIntoQuadrants(A, &A_11, &A_12, &A_21, &A_22);

    PartitionableMatrix B_11, B_12,
                        B_21, B_22;
    partitionMatrixIntoQuadrants(B, &B_11, &B_12, &B_21, &B_22);

    PartitionableMatrix C_11, C_12,
                        C_21, C_22;
    partitionMatrixIntoQuadrants(C, &C_11, &C_12, &C_21, &C_22);

    // Number of rows and columns in each partition
    // This will be the same across A, B, and C
    size_t nRowsPartition = A_11.nRowsPartition;
    size_t nColsPartition = A_11.nColsPartition;

    // Compute sums and differences of partitions
    PartitionableMatrix* S_1 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    subtractPartitionableMatrix(&B_12, &B_22, S_1);

    PartitionableMatrix* S_2 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    addPartitionableMatrix(&A_11, &A_12, S_2);

    PartitionableMatrix* S_3 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    addPartitionableMatrix(&A_21, &A_22, S_3);

    PartitionableMatrix* S_4 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    subtractPartitionableMatrix(&B_21, &B_11, S_4);

    PartitionableMatrix* S_5 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    addPartitionableMatrix(&A_11, &A_22, S_5);

    PartitionableMatrix* S_6 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    addPartitionableMatrix(&B_11, &B_22, S_6);

    PartitionableMatrix* S_7 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    subtractPartitionableMatrix(&A_12, &A_22, S_7);

    PartitionableMatrix* S_8 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    addPartitionableMatrix(&B_21, &B_22, S_8);

    PartitionableMatrix* S_9 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    subtractPartitionableMatrix(&A_11, &A_21, S_9);

    PartitionableMatrix* S_10 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    addPartitionableMatrix(&B_11, &B_12, S_10);
    
    // Compute products of sums and differences
    PartitionableMatrix* P_1 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    multiplyPartitionableMatrix(&A_11, S_1, P_1);

    PartitionableMatrix* P_2 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    multiplyPartitionableMatrix(S_2, &B_22, P_2);

    PartitionableMatrix* P_3 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    multiplyPartitionableMatrix(S_3, &B_11, P_3);

    PartitionableMatrix* P_4 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    multiplyPartitionableMatrix(&A_22, S_4, P_4);

    PartitionableMatrix* P_5 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    multiplyPartitionableMatrix(S_5, S_6, P_5);

    PartitionableMatrix* P_6 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    multiplyPartitionableMatrix(S_7, S_8, P_6);

    PartitionableMatrix* P_7 = 
        createPartitionableMatrix(nRowsPartition, nColsPartition);
    multiplyPartitionableMatrix(S_9, S_10, P_7);

    // Compute multiplication by adding products
    addPartitionableMatrix(P_5, P_4, &C_11);
    subtractPartitionableMatrix(&C_11, P_2, &C_11);
    addPartitionableMatrix(&C_11, P_6, &C_11);

    addPartitionableMatrix(P_1, P_2, &C_12);

    addPartitionableMatrix(P_3, P_4, &C_21);

    addPartitionableMatrix(P_5, P_1, &C_22);
    subtractPartitionableMatrix(&C_22, P_3, &C_22);
    subtractPartitionableMatrix(&C_22, P_7, &C_22);

    // Cleanup byproducts
    destroyPartitionableMatrix(S_1);
    destroyPartitionableMatrix(S_2);
    destroyPartitionableMatrix(S_3);
    destroyPartitionableMatrix(S_4);
    destroyPartitionableMatrix(S_5);
    destroyPartitionableMatrix(S_6);
    destroyPartitionableMatrix(S_7);
    destroyPartitionableMatrix(S_8);
    destroyPartitionableMatrix(S_9);
    destroyPartitionableMatrix(S_10);
    destroyPartitionableMatrix(P_1);
    destroyPartitionableMatrix(P_2);
    destroyPartitionableMatrix(P_3);
    destroyPartitionableMatrix(P_4);
    destroyPartitionableMatrix(P_5);
    destroyPartitionableMatrix(P_6);
    destroyPartitionableMatrix(P_7);
}

void addPartitionableMatrix(
    PartitionableMatrix* A, 
    PartitionableMatrix* B,
    PartitionableMatrix* C
)
{
    size_t nRows = A->nRowsPartition;
    size_t nCols = A->nColsPartition;

    for (size_t i = 0; i < nRows; i++)
    {
        for (size_t j = 0; j < nCols; j++)
        {
            int* A_ij = getPartitionableMatrixEntry(A, i, j);
            int* B_ij = getPartitionableMatrixEntry(B, i, j);
            int* C_ij = getPartitionableMatrixEntry(C, i, j);

            *C_ij = *A_ij + *B_ij;
        }
    }
}

void subtractPartitionableMatrix(
    PartitionableMatrix* A, 
    PartitionableMatrix* B,
    PartitionableMatrix* C
)
{
    size_t nRows = A->nRowsPartition;
    size_t nCols = A->nColsPartition;

    for (size_t i = 0; i < nRows; i++)
    {
        for (size_t j = 0; j < nCols; j++)
        {
            int* A_ij = getPartitionableMatrixEntry(A, i, j);
            int* B_ij = getPartitionableMatrixEntry(B, i, j);
            int* C_ij = getPartitionableMatrixEntry(C, i, j);

            *C_ij = *A_ij - *B_ij;
        }
    }
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
