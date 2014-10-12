#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
const int N_CITIES = 100;
const int X_MAX = 100;
const int Y_MAX = 100;
const double TEMP_MIN = 1e-3;
const double TEMP_MAX = 10.0;
const double TAU = 1e4;

double cooling(double);
double boltz(double, double);
double dist(int []);
void swap(int [], int, int);

int main(int argc, char * argv[]) {
    int i, j;
    // Recall that last element of array is same as first
    // (i.e. salesman returns to starting postiion)
    int * route = malloc(2 * (N_CITIES + 1) * sizeof(int));

    // Get random city coordinates (TODO: from user input)
    srand(time(NULL));
    for (i = 0; i < 2 * N_CITIES; i += 2) {
        // x-coordinate
        route[i] = rand() % X_MAX;
        // y-coordinate
        route[i + 1] = rand() % Y_MAX;
    }
    route[2 * N_CITIES] = route[0];
    route[2 * N_CITIES + 1] = route[1];

    // Start Markov chain
    int t = 0;
    double dist_now = dist(route);
    double dist_prev;
    double temp = TEMP_MAX;
    while (temp > TEMP_MIN) {
        t++;
        temp = cooling(t);
        
        // Store the current distance for comparing later
        dist_prev = dist_now;

        // Pick cities to swap
        i = rand() % N_CITIES;
        j = rand() % N_CITIES;
        // Cities must be different
        while (i == j) {
            i = rand() % N_CITIES;
            j = rand() % N_CITIES;
        }

        // Swap cities
        swap(route, i, j);
        // Get new distance
        dist_now = dist(route);

        // Decide whether to keep this move
        if ((double) rand() / (double) RAND_MAX
            > boltz(dist_now - dist_prev, temp)) {
            // Revert to previous route
            swap(route, i, j);
            dist_now = dist(route);
        }

        if (t % (int) (TAU / 10) == 0) {
            //printf("%d %f %f\n", t, temp, dist_now);
            printf("%f ", dist_now);
            for (i = 0; i < 2 * N_CITIES; i += 2)
                printf("%d %d ", route[i], route[i + 1]);
            printf("%d %d\n", route[N_CITIES], route[N_CITIES + 1]);
        }
    }

    return 0;
}

// Computes the "temperature" of the system for a given cooling schedule
double cooling(double t) {
    return TEMP_MAX * exp(-t / TAU);
}

// Computes the Boltzmann probability for a given step
double boltz(double dist_change, double temp) {
    return exp(-dist_change / temp);
}

// Computes the total distance travelled for the current route
double dist(int route[]) {
    int i;
    double d = 0.0;
    for (i = 0; i < 2 * N_CITIES; i += 2)
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
