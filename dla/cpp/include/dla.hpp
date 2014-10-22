#ifndef DLA_HPP
#define DLA_HPP

#include <cstdio>

class Dla {
    private:
        int grid_width;
        int grid_height;
        bool verbose;
        bool **anchors;
        int center_x;
        int center_y;
        double r;
        int radius;

        void update_square_radius();
        void anchor_second_particle();
        int * get_points_on_square();
        double get_distance_from_center(int, int);
        bool point_not_in_grid(int, int);
        bool adjacent_to_anchor(int, int);
        void walk_particle();
    public:
        Dla(int, int, bool verbose);
        void print_grid();
        void write_grid_to_file(char *);
        void simulate();
};

class Walker {
    friend class Dla;
    private:
        int x;
        int y;
        int next_x;
        int next_y;

        Walker(int, int);
        void move_to_next();
        void choose_next_coords();
};

#endif // DLA_HPP
