#include <cstdlib>
#include <iostream>
#include "dla.hpp"

int main(int argc, char *argv[]) {
    Dla dla = Dla(501, 501);
    dla.sim();
    dla.print_grid();
    return 0;
}
