#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    unsigned num_numbers;
    if (argc > 1) num_numbers = atoi( argv[1] ); 
    else num_numbers = 20;

    long unsorted[num_numbers], sorted[num_numbers];
    for (int i = 0; i < num_numbers; i++) unsorted[i] = rand()%10;

    sorted[0] = unsorted[0];
    for (int i = 1; i < num_numbers; i++) {
        // insert next value in unsorted at the end of sorted
        sorted[i] = unsorted[i];

        // loop backwards over sorted moving the newly 
        // inserted value into place
        for (int j = i-1; j >= 0; j--) {
            if (unsorted[i] < sorted[j]) {
                long temp = sorted[j];
                sorted[j] = unsorted[i];
                sorted[j+1] = temp;
            } else break;
        }
    }

    for (int i = 0; i < num_numbers; i++) printf("%li ", unsorted[i]);
    printf("\n");
    for (int i = 0; i < num_numbers; i++) printf("%li ", sorted[i]);
    printf("\n");
    
    return 0;
}

