#ifndef DLA_HPP
#define DLA_HPP

#include <cstdio>

class Dla {
    //friend class Walker;
    private:
        int grid_width;
        int grid_height;
        int center_x;
        int center_y;
        double r;
        int radius;
        bool **anchors;

        int * get_points_on_square();
        double get_distance_from_center(int, int);
        void update_square_radius();
        void anchor_second_particle();
        void walk_particle();
        bool adjacent_to_anchor(int, int);
        bool point_not_in_grid(int, int);
    public:
        Dla(int, int);
        void print_grid();
        void write_grid_to_file(char *);
        void sim();
};

class Walker {
    friend class Dla;
    private:
        int x;
        int y;
        int next_x;
        int next_y;
        Walker(Dla *, int, int);
        void move_to_next();
        void choose_next_coords();
};

#endif // DLA_HPP
