#include <stdio.h>
#include <stdlib.h>

int binary_search (int value, int sequence[], size_t len);

int main (int argc, char** argv)
{
    if (argc < 3) return -1;

    // Gather value to search for and sequence to search
    const int value = atoi( argv[1] );
    const size_t len = argc - 2;
    int sequence[len];
    for (int i = 0; i < len; i++) sequence[i] = atoi( argv[i+2] );

    // Search for value in sequence
    const int index = binary_search(value, sequence, len);
    if (index != -1)
        printf("Found value %i at index %i\n", value, index);
    else
        printf("Did not find value %i in sequence\n", value);

    return 0;
}

int binary_search (int value, int sequence[], size_t len)
{
    // Are we at the end of our search?
    if (len == 0) {
        return -1;
    }

    // Keep searching for our value
    const unsigned midpoint = (unsigned) len / 2;
    if (value == sequence[midpoint]) {
        return midpoint;
    }
    else if (value < sequence[midpoint]) {
        return binary_search(value, sequence, midpoint);
    }
    else {
        int index = 
            binary_search(value, &sequence[midpoint+1], len-(midpoint+1));
        return (index != -1) ? (midpoint+1) + index : -1;
    }

}

