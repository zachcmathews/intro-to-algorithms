#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

typedef struct {
    size_t start;
    size_t end;
    long sum;
} Subarray;

void find_max_subarray(int[], size_t, size_t, Subarray*);
void find_max_crossing_subarray(int[], size_t, size_t, Subarray*);

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

    // Find max subarray
    Subarray max;
    find_max_subarray(sequence, 0, len-1, &max);

    // Print results
    printf("Max subarray found at:\n");
    printf("Start index: %i\n", (unsigned) max.start);
    printf("End index: %i\n", (unsigned) max.end);
    printf("Sum: %ld\n", max.sum);

    return 0;
}

void find_max_subarray(
        int sequence[], size_t start, size_t end, Subarray* max
)
{
    if (start == end) {
        max->start = start;
        max->end = end;
        max->sum = sequence[start];
        return;
    }

    size_t mid = (start + end) / 2;

    Subarray left_max;
    find_max_subarray(sequence, start, mid, &left_max);

    Subarray crossing_max;
    find_max_crossing_subarray(sequence, start, end, &crossing_max);

    Subarray right_max;
    find_max_subarray(sequence, mid+1, end, &right_max);

    if (
        left_max.sum > crossing_max.sum 
        && left_max.sum > right_max.sum
    ) {
        max->start = left_max.start;
        max->end = left_max.end;
        max->sum = left_max.sum;
        return;
    }
    else if (
        crossing_max.sum > left_max.sum 
        && crossing_max.sum > right_max.sum
    ) {
        max->start = crossing_max.start;
        max->end = crossing_max.end;
        max->sum = crossing_max.sum;
        return;
    }
    else {
        max->start = right_max.start;
        max->end = right_max.end;
        max->sum = right_max.sum;
        return;
    }
}

void find_max_crossing_subarray(
        int sequence[], size_t start, size_t end, Subarray* max
)
{
    size_t mid = (start + end) / 2;

    bool init = true;
    long sum = 0;
    size_t i = mid;
    long left_max = 0;
    do {
        sum = sum + sequence[i];
        if (init || sum > left_max) {
            init = false;
            left_max = sum;
            max->start = i;
        }
    } while (i-- > start);
    
    init = true;
    sum = 0;
    i = mid + 1;
    long right_max = 0;
    do {
        sum = sum + sequence[i];
        if (init || sum > right_max) {
            init = false;
            right_max = sum;
            max->end = i;
        }
    } while (i++ < end);

    max->sum = left_max + right_max;
}
