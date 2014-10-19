#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "dla.hpp"

Dla::Dla(int grid_width, int grid_height) {
    this->grid_width = grid_width;
    this->grid_height = grid_height;

    // Initialize all cells to zero
    this->anchors = (bool **) std::malloc(grid_height * sizeof(bool *));
    for (int i = 0; i < grid_height; i++)
        this->anchors[i] = (bool *) std::malloc(grid_width * sizeof(bool));
    for (int i = 0; i < grid_height; i++) {
        for (int j = 0; j < grid_width; j++)
            this->anchors[i][j] = false;
    }

    // Anchor a particle at the center
    this->center_x = grid_height / 2;
    this->center_y = grid_width / 2;
    this->anchors[this->center_x][this->center_y] = true;
    //std::cout << "New anchor at (" << center_x << "," << center_y << ")\n";
    this->r = 0.0;
    this->radius = 1;

    std::srand(std::time(NULL));
}

void Dla::print_grid() {
    for (int i = 0; i < grid_height; i++) {
        for (int j = 0; j < grid_width - 1; j++)
            std::cout << anchors[i][j] << " ";
        std::cout << anchors[i][grid_width - 1] << "\n";
    }
}

int * Dla::get_points_on_square() {
    // Not sure yet if should be > or >=
    // This should be handled by the main loop
    if (radius > grid_width / 2 || radius > grid_height / 2)
        return NULL;

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

void Dla::update_square_radius() {
    //radius = 1 + (int) std::ceil(r);
    radius = (int) std::ceil(r + 1);
}

void Dla::anchor_second_particle() {
    int test = std::rand() % 4;
    if (test == 0) anchors[center_x - 1][center_y] = true;
    else if (test == 1) anchors[center_x + 1][center_y] = true;
    else if (test == 2) anchors[center_x][center_y - 1] = true;
    else anchors[center_x][center_y + 1] = true;
    r = 1.0;
    update_square_radius();
}

void Dla::walk_particle() {
    // Get all points on square of radius r + 1 around center
    int *points = get_points_on_square();
    // This should be handled by the main loop, remove later
    if (points == NULL) {
        // End program
        print_grid();
        exit(0);
    }

    // Choose random point to be starting position
    int n_points = radius * 8;
    int test = std::rand() % n_points;
    int start_x = points[test * 2];
    int start_y = points[test * 2 + 1];
    std::free(points);

    Walker walker = Walker(this, start_x, start_y);
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
            //std::cout << "New anchor at (" << walker.x << "," << walker.y << ")\n";
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

bool Dla::adjacent_to_anchor(int x, int y) {
    if (!point_not_in_grid(x - 1, y) && anchors[x - 1][y]) return true;
    if (!point_not_in_grid(x + 1, y) && anchors[x + 1][y]) return true;
    if (!point_not_in_grid(x, y - 1) && anchors[x][y - 1]) return true;
    if (!point_not_in_grid(x, y + 1) && anchors[x][y + 1]) return true;
    return false;
}

// Faster than checking if point in grid since it short-circuits
bool Dla::point_not_in_grid(int x, int y) {
    return (x < 0 || x >= grid_height || y < 0 || y >= grid_width);
}

void Dla::sim() {
    // Anchor the second particle "manually" so that r becomes non-zero
    anchor_second_particle();

    // Experiment with this
    //while (r < grid_width / 2 && r < grid_height / 2) {
    while (radius < grid_width / 2 && radius < grid_height / 2) {
        walk_particle();
    }
}

Walker::Walker(Dla *parent, int x, int y) {
    this->parent = parent;
    this->x = x;
    this->y = y;
}

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