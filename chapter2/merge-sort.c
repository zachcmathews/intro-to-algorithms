#include <stdio.h>
#include <stdlib.h>

void merge_sort(int sequence[], size_t len);

int main (int argc, char** argv)
{
    if (argc < 2) return -1;

    // gather sequence and echo
    int sequence[argc-1];
    for (int i = 0; i < argc-1; i++) sequence[i] = atoi( argv[i+1] );
    for (int i = 0; i < argc-1; i++) printf("%i ", sequence[i]);
    printf("\n");

    // sort sequence
    merge_sort(sequence, argc-1);

    // print sorted sequence
    for (int i = 0; i < argc-1; i++) printf("%i ", sequence[i]);
    printf("\n");

    return 0;
}

void merge_sort(int sequence[], size_t len)
{
    // divide
    int half = len / 2;
    int left[half];
    for (int i = 0; i < half; i++) left[i] = sequence[i];
    int right[len-half];
    for (int i = 0; i < len-half; i++) right[i] = sequence[half+i];
    
    // conquer
    if (half > 1) {
        merge_sort(left, half);
        merge_sort(right, len-half);
    }

    // combine
    int left_index = 0, right_index = 0;
    for (int i = 0; i < len; i++)
    {
        // choose next least between left and right
        if (right[right_index] < left[left_index]) {
            sequence[i] = right[right_index];
            right_index++;
        } else {
            sequence[i] = left[left_index];
            left_index++;
        }

        // if left or right is exhausted, exhaust the other
        if (left_index >= half) {
            while (++i < len) sequence[i] = right[right_index++];
        }
        if (right_index >= len-half) {
            while (++i < len) sequence[i] = left[left_index++];
        }
    }
}

