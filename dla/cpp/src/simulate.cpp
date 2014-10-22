#include <cstdlib>
#include <iostream>
#include "dla.hpp"

void print_usage();

int main(int argc, char *argv[]) {
    if (argc < 4) {
        print_usage();
        exit(0);
    }

    int grid_width = std::atoi(argv[1]);
    int grid_height = std::atoi(argv[2]);
    char *outfile = argv[3];

    Dla dla = Dla(grid_width, grid_height, false);
    dla.simulate();
    //dla.print_grid();
    dla.write_grid_to_file(outfile);
    return 0;
}

void print_usage() {
    std::cout << "Usage: ./simulate grid_width grid_height output_file\n";
}
