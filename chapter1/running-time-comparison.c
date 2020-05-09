#include <stdio.h>
#include <math.h>

// time in microseconds
const double SECOND = 10*10*10*10*10*10;
const double MINUTE = 60*SECOND;
const double HOUR = 60*MINUTE;
const double DAY = 24*HOUR;
const double MONTH = 31*DAY;
const double YEAR = 365*DAY;
const double CENTURY = 100*YEAR;

int main (int argc, char **argv) 
{
    const double intervals[] = { SECOND, MINUTE, HOUR, DAY, MONTH, YEAR, CENTURY };
    const unsigned int num_intervals = sizeof intervals / sizeof intervals[0];
    
    const char* algorithms[] = { "lg n", "sqrt n", "n", "n^2", "n^3", "2^n" };
    const unsigned int num_algorithms = sizeof algorithms / sizeof algorithms[0];

    double largest_n[num_algorithms][num_intervals];
    for (int i = 0; i < num_intervals; i++) {
        const double t = intervals[i];

        largest_n[0][i] = pow(2, t);            // lg n
        largest_n[1][i] = pow(t, 2);            // sqrt n
        largest_n[2][i] = t;                    // n
        largest_n[3][i] = sqrt(t);              // n^2 
        largest_n[4][i] = pow(t, 1.0/3);        // n^3
        largest_n[5][i] = log2(t);              // 2^n                              
    }

    printf(
        "%16s\t%16s\t%16s\t%16s\t%16s\t%16s\t%16s\t%16s\t\n",
        "",
        "SECOND",
        "MINUTE",
        "HOUR",
        "DAY",
        "MONTH",
        "YEAR",
        "CENTURY"
    );

    for (int i = 0; i < num_algorithms; i++) {
        const char* algorithm = algorithms[i];
        
        printf(
            "%16s\t%16.2g\t%16.2g\t%16.2g\t%16.2g\t%16.2g\t%16.2g\t%16.2g\n",
            algorithm,
            largest_n[i][0], 
            largest_n[i][1],
            largest_n[i][2],
            largest_n[i][3],
            largest_n[i][4],
            largest_n[i][5],
            largest_n[i][6]
        );
        
    }

    return 0;
}

