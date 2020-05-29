#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char** argv)
{
    if (argc < 3) return -1;

    // Get x
    int x = atoi(argv[1]);

    // Gather coefficients
    size_t count = argc - 2;
    int coeffs[count];
    for (int i = 0; i < count; i++) coeffs[i] = atoi(argv[i+2]);

    // Echo coefficients 
    for (int i = 0; i < count; i++) printf("%i ", coeffs[i]);
    printf("\n");

    // Evaluate polynomial
    int eval = 0;
    for (int k = count-1; k >= 0; k--)
    {
        eval = coeffs[k] + x * eval;
    }

    printf("%i \n", eval);

    return 0;
}
