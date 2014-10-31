#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include "dla.hpp"

void print_usage();

int main(int argc, char *argv[]) {
    if (argc < 7) {
        print_usage();
        return 0;
    }

    int c;
    int grid_width, grid_height;
    char *outfile;
    bool verbose = false;

    // Parse args
    opterr = 0;
    while ((c = getopt(argc, argv, "w:h:o:v")) != -1) {
        switch (c) {
            case 'w':
                grid_width = std::atoi(optarg);
                break;
            case 'h':
                grid_height = std::atoi(optarg);
                break;
            case 'o':
                outfile = optarg;
                break;
            case 'v':
                verbose = true;
                break;
            default:
                print_usage();
                return 1;
        }
    }

    std::cout << "Grid width      : " << grid_width << "\n";
    std::cout << "Grid height     : " << grid_height << "\n";
    std::cout << "Output filename : " << outfile << "\n";

    Dla dla = Dla(grid_width, grid_height, verbose);
    dla.simulate();
    //dla.print_grid();
    dla.write_grid_to_file(outfile);
    return 0;
}

void print_usage() {
    std::cout << "Usage: ./simulate -w grid_width -h grid_height -o output_filename [-v]\n";
}
