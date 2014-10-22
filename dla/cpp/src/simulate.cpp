#include <cstdlib>
#include <iostream>
#include "dla.hpp"

int main(int argc, char *argv[]) {
    int grid_width = std::atoi(argv[1]);
    int grid_height = std::atoi(argv[2]);
    char *outfile = argv[3];
    Dla dla = Dla(grid_width, grid_height, true);
    dla.simulate();
    //dla.print_grid();
    dla.write_grid_to_file(outfile);
    return 0;
}
