#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "dla.hpp"

/***************************************** CONSTRUCTOR *****************************************/

Dla::Dla(int grid_width, int grid_height, bool verbose) {
    this->grid_width = grid_width;
    this->grid_height = grid_height;
    this->verbose = verbose;

    // Initialize all cells to zero
    this->anchors = (bool **) std::malloc(grid_height * sizeof(bool *));
    for (int i = 0; i < grid_height; i++)
        this->anchors[i] = (bool *) std::malloc(grid_width * sizeof(bool));
    for (int i = 0; i < grid_height; i++) {
        for (int j = 0; j < grid_width; j++)
            this->anchors[i][j] = false;
    }

    // Get coordinates of grid center
    this->center_x = grid_height / 2;
    this->center_y = grid_width / 2;

    // Anchor first particle at center
    this->anchors[this->center_x][this->center_y] = true;
    if (verbose)
        std::cout << "New anchor at (" << center_x << "," << center_y << ")\n";
    
    // Set initial radius for new walkers
    this->r = 0.0;
    update_square_radius();

    // Seed random generator
    std::srand(std::time(NULL));

    // Anchor second particle
    anchor_second_particle();
}

/***********************************************************************************************/

/************************************** PUBLIC FUNCTIONS ***************************************/

void Dla::print_grid() {
    for (int i = 0; i < grid_height; i++) {
        for (int j = 0; j < grid_width - 1; j++)
            std::cout << anchors[i][j] << " ";
        std::cout << anchors[i][grid_width - 1] << "\n";
    }
}

void Dla::write_grid_to_file(char *outfile) {
    std::FILE *p_outfile = std::fopen(outfile, "w");
    for (int i = 0; i < grid_height; i++) {
        for (int j = 0; j < grid_width - 1; j++)
            std::fprintf(p_outfile, "%d ", anchors[i][j]);
        std::fprintf(p_outfile, "%d\n", anchors[i][grid_width - 1]);
    }
    std::fclose(p_outfile);
}

void Dla::simulate() {
    // Introduce new walkers until starting position reaches edge of grid
    while (radius < grid_width / 2 && radius < grid_height / 2) {
        walk_particle();
    }
}

/***********************************************************************************************/

/************************************** PRIVATE FUNCTIONS **************************************/
void Dla::update_square_radius() {
    radius = (int) std::ceil(r + 1);
}

void Dla::anchor_second_particle() {
    int test = std::rand() % 4;
    int x, y;
    if (test == 0)      { x = center_x - 1; y = center_y; }
    else if (test == 0) { x = center_x + 1; y = center_y; }
    else if (test == 0) { x = center_x    ; y = center_y - 1; }
    else                { x = center_x    ; y = center_y + 1; }
    anchors[x][y] = true;
    r++;
    update_square_radius();
    if (verbose)
        std::cout << "New anchor at (" << x << "," << y << ")\n";
}

int * Dla::get_points_on_square() {
    int x, y;
    int i = 0;
    int *points = (int *) std::malloc(2 * (radius * 8) * sizeof(int));

    // Top edge
    x = center_x - radius;
    for (y = center_y - radius; y <= center_y + radius; y++) {
        points[i++] = x;
        points[i++] = y;
    }
    // Bottom edge
    x = center_x + radius;
    for (y = center_y - radius; y <= center_y + radius; y++) {
        points[i++] = x;
        points[i++] = y;
    }
    // Left edge
    y = center_y - radius;
    for (x = center_x - (radius - 1); x <= center_x + (radius - 1); x++) {
        points[i++] = x;
        points[i++] = y;
    }
    // Right edge
    y = center_y + radius;
    for (x = center_x - (radius - 1); x <= center_x + (radius - 1); x++) {
        points[i++] = x;
        points[i++] = y;
    }

    return points;
}

double Dla::get_distance_from_center(int x, int y) {
    return std::sqrt(std::pow(x - center_x, 2) + std::pow(y - center_y, 2));
}

// Faster than checking if point in grid since it short-circuits
bool Dla::point_not_in_grid(int x, int y) {
    return (x < 0 || x >= grid_height || y < 0 || y >= grid_width);
}

bool Dla::adjacent_to_anchor(int x, int y) {
    if (!point_not_in_grid(x - 1, y) && anchors[x - 1][y]) return true;
    if (!point_not_in_grid(x + 1, y) && anchors[x + 1][y]) return true;
    if (!point_not_in_grid(x, y - 1) && anchors[x][y - 1]) return true;
    if (!point_not_in_grid(x, y + 1) && anchors[x][y + 1]) return true;
    return false;
}

void Dla::walk_particle() {
    // Get all points on square of radius r + 1 around center
    int *points = get_points_on_square();

    // Choose random point to be starting position
    int n_points = radius * 8;
    int test = std::rand() % n_points;
    int start_x = points[test * 2];
    int start_y = points[test * 2 + 1];
    std::free(points);

    Walker walker = Walker(start_x, start_y);
    // Initialize to fake value
    double distance = 0.0;

    while (distance < 2.0 * r) {
        // Choose next move
        walker.choose_next_coords();
        while (point_not_in_grid(walker.next_x, walker.next_y))
            walker.choose_next_coords();
        walker.move_to_next();
        distance = get_distance_from_center(walker.x, walker.y);
        if (adjacent_to_anchor(walker.x, walker.y)) {
            // Anchor this particle
            if (verbose)
                std::cout << "New anchor at (" << walker.x << "," << walker.y << ")\n";
            anchors[walker.x][walker.y] = true;
            // Update furthest distance from center if necessary
            if (r < distance) {
                r = distance;
                // Update square radius
                update_square_radius();
            }
            return;
        }
    }
}

/***************************************** CONSTRUCTOR *****************************************/

Walker::Walker(int x, int y) {
    this->x = x;
    this->y = y;
}

/***********************************************************************************************/

/************************************** PRIVATE FUNCTIONS **************************************/

void Walker::move_to_next() {
    x = next_x;
    y = next_y;
}

void Walker::choose_next_coords() {
    int test;

    test = std::rand() % 4;
    if (test == 0) {
        next_x = x - 1;
        next_y = y;
    }
    else if (test == 1) {
        next_x = x + 1;
        next_y = y;
    }
    else if (test == 2) {
        next_x = x;
        next_y = y - 1;
    }
    else {
        next_x = x;
        next_y = y + 1;
    }
}
