/*
 * Generating solutions to the travelling salesman problem using simulated
 * annealing.
 *
 * Example parameters:
 *     n_cities    : 100
 *     grid_width  : 100
 *     grid_height : 100
 *     temp_init   : 1e-3
 *     temp_final  : 10.0
 *     tau         : 1e4
 *
 * Usage:
 *     travsal ./travsal -n 100 -w 100 -h 100 -i 1e-3 -f 10 -t 1e4
 */

#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double cooling(double, double, double);
double boltz(double, double);
double dist(int [], int);
void swap(int [], int, int);
void print_usage();

int main(int argc, char * argv[]) {
    if (argc < 13) {
        print_usage();
        return 0;
    }

    int c;
    int n_cities;
    int grid_width, grid_height;
    double temp_init, temp_final;
    double tau;

    opterr = 0;
    while ((c = getopt(argc, argv, "n:w:h:i:f:t:")) != -1) {
        switch (c) {
            case 'n':
                n_cities = atoi(optarg);
                break;
            case 'w':
                grid_width = atoi(optarg);
                break;
            case 'h':
                grid_height = atoi(optarg);
                break;
            case 'i':
                temp_init = atof(optarg);
                break;
            case 'f':
                temp_final = atof(optarg);
                break;
            case 't':
                tau = atof(optarg);
                break;
            default:
                print_usage();
                return 1;
        }
    }

    int i, j;
    // N.B. last element of array is same as first
    // (i.e. salesman returns to starting postiion)
    int * route = malloc(2 * (n_cities + 1) * sizeof(int));

    // Get random city coordinates (TODO: from user input)
    srand(time(NULL));
    for (i = 0; i < 2 * n_cities; i += 2) {
        // x-coordinate
        route[i] = rand() % grid_width;
        // y-coordinate
        route[i + 1] = rand() % grid_height;
    }
    route[2 * n_cities] = route[0];
    route[2 * n_cities + 1] = route[1];

    // Start Markov chain
    int t = 0;
    double dist_now = dist(route, n_cities);
    double dist_prev;
    double temp = temp_final;
    while (temp > temp_init) {
        t++;
        temp = cooling(t, temp_final, tau);
        
        // Store the current distance for comparing later
        dist_prev = dist_now;

        // Pick cities to swap
        i = rand() % n_cities;
        j = rand() % n_cities;
        // Cities must be different
        while (i == j) {
            i = rand() % n_cities;
            j = rand() % n_cities;
        }

        // Swap cities
        swap(route, i, j);
        // Get new distance
        dist_now = dist(route, n_cities);

        // Decide whether to keep this move
        if ((double) rand() / (double) RAND_MAX
            > boltz(dist_now - dist_prev, temp)) {
            // Revert to previous route
            swap(route, i, j);
            dist_now = dist(route, n_cities);
        }

        if (t % (int) (tau / 10) == 0) {
            //printf("%d %f %f\n", t, temp, dist_now);
            printf("%f ", dist_now);
            for (i = 0; i < 2 * n_cities; i += 2)
                printf("%d %d ", route[i], route[i + 1]);
            printf("%d %d\n", route[n_cities], route[n_cities + 1]);
        }
    }

    return 0;
}

// Computes the "temperature" of the system for a given cooling schedule
double cooling(double t, double temp_final, double tau) {
    return temp_final * exp(-t / tau);
}

// Computes the Boltzmann probability for a given step
double boltz(double dist_change, double temp) {
    return exp(-dist_change / temp);
}

// Computes the total distance travelled for the current route
double dist(int route[], int n_cities) {
    int i;
    double d = 0.0;
    for (i = 0; i < 2 * n_cities; i += 2)
        d += sqrt(pow(route[i + 2] - route[i], 2) +
                  pow(route[i + 3] - route[i + 1], 2));
    return d;
}

// Swaps the cities i and j
void swap(int route[], int i, int j) {
    int tmp;

    i *= 2;
    j *= 2;

    // Swap x-coordinates
    tmp = route[i];
    route[i] = route[j];
    route[j] = tmp;
    // Swap y-coordinates
    tmp = route[i + 1];
    route[i + 1] = route[j + 1];
    route[j + 1] = tmp;
}

// Prints program usage
void print_usage() {
    printf("Usage: travsal -n [number of cities] -w [grid width] -h [grid height]\n       -i [initial temperature] -f [final temperature] -t [cooling timescale]\n");
}
           
