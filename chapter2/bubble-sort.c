#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    if (argc < 2) return -1;

    // Gather sequence
    size_t count = argc - 1;
    int sequence[count];
    for (int i = 0; i < count; i++) sequence[i] = atoi(argv[i+1]);

    // Echo unsorted sequence
    for (int i = 0; i < count; i++) printf("%i ", sequence[i]);
    printf("\n");

    // Sort sequence
    for (int i = 0; i < count; i++)
    {
        for (int j = i; j < count-1; j++)
        {
            if (sequence[j] > sequence[j+1])
            {
                int temp = sequence[j];
                sequence[j] = sequence[j+1];
                sequence[j+1] = temp;
            }
        }
    }
    
    // Echo unsorted sequence
    for (int i = 0; i < count; i++) printf("%i ", sequence[i]);
    printf("\n");

    return 0;
}
