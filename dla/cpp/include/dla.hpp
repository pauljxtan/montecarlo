#ifndef DLA_HPP
#define DLA_HPP

class Dla {
    private:
        // Dimensions of the lattice
        int grid_width, grid_height;
        // Verbose flag
        bool verbose;
        // Grid representation of the system (anchor=true)
        bool **anchors;
        // (x,y) coordinates of the grid center
        int center_x, center_y;
        // Distance of the furthest particle from the center
        double r;
        // Radius of the bounding box
        int radius;

        // Update the radius of the bounding box
        void update_box_radius();
        // Anchors the second particle
        void anchor_second_particle();
        // Returns all grid points lying on the bounding box
        int * get_points_on_box();
        // Computes the distance from the center
        double get_distance_from_center(int, int);
        // Checks if the coordinate is contained in the grid
        bool point_not_in_grid(int, int);
        // Checks if the particle is adjacent to an anchor
        bool adjacent_to_anchor(int, int);
        // Introduces a new particle
        void walk_particle();

    public:
        // Constructor
        Dla(int, int, bool verbose);
        // Prints the grid to stdout
        void print_grid();
        // Writes the grid to an output file
        void write_grid_to_file(char *);
        // Main wrapper function
        void simulate();
};

class Walker {
    friend class Dla;
    private:
        // (x,y) coordinates of the walker
        int x, y;
        // Coordinates of the next prospective position
        int next_x, next_y;

        // Constructor
        Walker(int, int);
        // Choose the next prospective position
        void choose_next_coords();
        // Move to the next position
        void move_to_next();
};

#endif // DLA_HPP
