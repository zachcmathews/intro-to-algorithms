#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

int main (int argc, char** argv)
{
    if (argc < 2) return -1;

    // Fill sequence with args
    size_t len = argc - 1;
    int sequence[len];
    char *end;
    for (size_t i = 0; i < len; i++) {
        errno = 0;
        sequence[i] = strtol(argv[i+1], &end, 10);
        if (errno || *end) {
            printf("Error: %s is invalid input\n", end);
            return -1;
        }
    }


    // Echo sequence
    printf("Sequence: ");
    for (size_t i = 0; i < len; i++) printf("%i ", sequence[i]);
    printf("\n\n");


    // Find maximum subarray
    size_t start, stop;
    long max_sum = 0;
    bool init = true;
    for (size_t i = 0; i < len; i++)
    {
        long sum = 0;
        for (size_t j = i; j < len; j++)
        {
            sum += sequence[j];
            if (sum >= max_sum || init) 
            {
                init = false;
                start = i;
                stop = j;
                max_sum = sum;
            }
        }
    }

    printf("Maximum subarray: \n");
    printf("start: %li\n", start);
    printf("stop: %li\n", stop);
    printf("sum: %li\n", max_sum);

    return 0;
}


