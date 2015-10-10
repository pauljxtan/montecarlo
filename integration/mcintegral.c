/* Monte Carlo integration */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef double (* func_ptr)(double);

double mean_value(func_ptr, double, double, int);

int main(int argc, char *argv[]) {
    printf("f=sin(x), a=0, b=pi/2, n=1e6: %f\n", mean_value(&sin, 0.0, M_PI/2, 1e6));
    printf("f=cos(x), a=0, b=pi/2, n=1e6: %f\n", mean_value(&cos, 0.0, M_PI/2, 1e6));
    return EXIT_SUCCESS;
}

/* Estimates a definite integral using the mean value method */
double mean_value(func_ptr f, double a, double b, int n_points) {
    int count = 0;
    double sum = 0;

    srand(time(NULL));
    while (count++ < n_points)
        /* Not really uniform, but good enough... */
        sum += f( (b - a) * ((double) rand() / (double) RAND_MAX) + a );

    return (b - a) / n_points * sum;
}
