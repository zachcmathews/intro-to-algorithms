#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int argc, char** argv)
{
    const int n_bits = atoi( argv[1] );
    bool integers[2][n_bits];
    bool sum[n_bits+1];
    bool carry = 0;

    // fill integer arrays by converting ascii input to binary
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < n_bits; j++) 
            integers[i][j] = (argv[i+2][j] == '0') ? 0 : 1;

    // compute sum
    for (int i = n_bits; i >= 1; i--) {
        sum[i] = carry ^ integers[0][i-1] ^ integers[1][i-1];
        carry = 
            (carry & integers[0][i-1])
            | (carry & integers[1][i-1])
            | (integers[0][i-1] & integers[1][i-1]);
    }
    sum[0] = carry;

    // print summands and sum
    for (int i = 0; i < 2; i++) {
        printf(" ");

        for (int j = 0; j < n_bits; j++) printf("%i", integers[i][j]);

        printf("\n");
    }
    for (int j = 0; j <= n_bits; j++) printf("%i", sum[j]);
    printf("\n");

    return 0;
}

