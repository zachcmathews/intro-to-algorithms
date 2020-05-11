#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    if (argc < 2) return -1;

    // gather unsorted array
    size_t count = argc - 1;
    int sequence[count];
    for (int i = 0; i < count; i++) 
        sequence[i] = atoi( argv[i+1] );

    // sort array
    for (int i = 0; i < count; i++) {
        int minimum = i;
        
        for (int j = i+1; j < count; j++) {
            if (sequence[j] < sequence[minimum]) minimum = j;
        }

        int temp = sequence[i];
        sequence[i] = sequence[minimum];
        sequence[minimum] = temp;
    }

    // print sorted
    for (int i = 0; i < count; i++) printf("%i ", sequence[i]);
    printf("\n");
    
    return 0;
}
