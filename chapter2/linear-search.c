#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    if (argc < 3) {
        printf("Expected >=2 arguments:\n");
        printf("1) Value to search for\n");
        printf("2) Sequence to search\n");
    }

    int v = atoi( argv[1] ); 

    int i;
    for (i = 2; i < argc; i++) {
        if (v == atoi( argv[i] )) break;
    }

    if (i < argc) printf("Found value %i at index %i\n", v, i-2);
    else printf("Did not find value %i in sequence\n", v);

    return 0;
}
