#!/usr/bin/env python

"""
Generates solutions to the dimer-covering problem using simulated annealing.
"""

# TODO:
# -- optimize (setup takes way too long)
# -- option to draw text grids
# -- use argparse
# -- output text results

import math
import random
import sys
import time

class Grid(object):
    def __init__(self, width, height):
        """
        Constructs a grid with dimensions width x height.
        @type  width: int
        @param width: width of grid
        @type  height: int
        @param height: height of grid
        """
        self.width = width
        self.height = height
        self.n_dimers = 0

        self.cells = {}
        for x in range(height):
            for y in range(width):
                # Populate dictionary with coordinate keys
                # 1: adjacent cells, 2: Dimer object (if present)
                self.cells[(x, y)] = [None, None]
        # Get adjacent cells for each coordinate
        for coord, data in self.cells.iteritems():
            data[0] = self.get_adjacent_cells(coord)

    def get_adjacent_cells(self, coord):
        """
        Returns coordinates of all cells adjacent (horizontally or vertically)
        to this cell.
        @type  coord: tuple
        @param coord: (x,y) coordinate of cell
        @rtype: list of tuples
        @return: (x,y) coordinates of adjacent cells
        """
        adjacent_cells = []
        for (xa, ya) in ((coord[0] - 1, coord[1]), (coord[0] + 1, coord[1]),
                         (coord[0], coord[1] - 1), (coord[0], coord[1] + 1)):
            if (xa, ya) in self.cells.keys():
                adjacent_cells.append((xa, ya))

        return adjacent_cells

    def place_dimer(self, sites, verbose=False):
        """
        Places a dimer occupying the two specified sites (only if both sites
        are unoccupied).
        @type  sites: list of tuples
        @param sites: (x,y) coordinates of both sites
        """
        if self.cells[sites[0]][1] or self.cells[sites[1]][1]:
            # Site(s) is/are occupied; terminate
            if verbose: print "Site(s) is/are occupied; skipping"
            return

        dimer = Dimer(sites)
        self.cells[sites[0]][1] = dimer
        self.cells[sites[1]][1] = dimer
        self.n_dimers += 1

        if verbose: print "Placed dimer at", sites

    def remove_dimer(self, sites, verbose=False):
        """
        Removes a dimer occupying the two specified sites (only if both sites
        are occupied, and by the same dimer).
        @type  sites: list of tuples
        @param sites: (x,y) coordinates of both sites
        """
        if self.has_single_dimer(sites):
            self.cells[sites[0]][1] = None
            self.cells[sites[1]][1] = None
            self.n_dimers -= 1

            if verbose:
                print "Removed dimer from", sites

    def has_single_dimer(self, sites):
        return (self.cells[sites[0]][1]
                and self.cells[sites[0]][1] == self.cells[sites[1]][1])

    def dimers(self):
        """
        Returns all dimers on the grid.
        """
        return set([value[1] for key, value in self.cells.items() if value[1]])

    def draw(self):
        """
        Returns a string representation of the grid.
        """
        result = [[" " for _ in range(self.width * 2)] for _ in range(self.height * 2)]
        for dimer in self.dimers():
            site_0 = dimer.sites[0]
            site_1 = dimer.sites[1]

            coords_0 = (site_0[0] * 2, site_0[1] * 2)
            coords_1 = (site_1[0] * 2, site_1[1] * 2)

            line_symbol = "-" if coords_0[0] == coords_1[0] else "|"
            line_row = (coords_0[0] if coords_0[0] == coords_1[0]
                        else (coords_0[0] + coords_1[0]) / 2)
            line_col = (coords_0[1] if coords_0[1] == coords_1[1]
                        else (coords_0[1] + coords_1[1]) / 2)

            result[coords_0[0]][coords_0[1]] = "o"
            result[coords_1[0]][coords_1[1]] = "o"
            result[line_row][line_col] = line_symbol

        return "\n".join("".join(line) for line in result)


class Dimer(object):
    def __init__(self, sites):
        """
        Constructs a dimer occupying the two specified sites.
        @type  sites: tuple
        @param sites: (x,y) coordinates of both sides
        """
        self.sites = sites

def pick_sites(grid):
    """
    Randomly pick two adjacent sites on a grid.
    @type  grid: Grid object
    @param grid: grid
    """
    # Pick the first site
    site1 = (random.randrange(grid.height), random.randrange(grid.width))
    # Pick an adjacent site
    site2 = random.choice(grid.cells[site1][0])
    return (site1, site2)

def cooling(t, tau, T_init):
    return T_init * math.exp(-t / tau)

def parse_infile(infile):
    params = open(infile).read().split()
    width = int(params[0])
    height = int(params[1])
    T_final = float(params[2])
    T_init = float(params[3])
    tau = float(params[4])

    return width, height, T_final, T_init, tau

def main(frameskip=10, draw_text=True, draw_mpl=False):
    if draw_mpl:
        from matplotlib import pyplot

    width_default = 50
    height_default = 25
    T_init_default = 10.0
    T_final_default = 0.025
    tau_default = 10000.0

    if len(sys.argv) < 2:
        print "Parameter file not specified - using default parameters"
        width = width_default
        height = height_default
        T_init = T_init_default
        T_final = T_final_default
        tau = tau_default
    else:
        infile = sys.argv[1]
        print "Using parameters from file:", infile
        width, height, T_init, T_final, tau = parse_infile(sys.argv[1])

    print "-" * 64
    print "Lattice width       = ", width
    print "Lattice height      = ", height
    print "Initial temperature = ", T_init
    print "Final temperature   = ", T_final
    print "Cooling timescale   = ", tau
    print "-" * 64

    print "Initializing the grid..."

    grid = Grid(width, height)

    if draw_mpl:
        print "Setting up the matplotlib figure"
        print "This will take quite a while if the grid is large (~50x50)"
        # Set up matplotlib figure
        pyplot.ion()
        fig = pyplot.figure()
        sp = fig.add_subplot(111)
        sp.set_xlim(-1, grid.width)
        sp.set_ylim(-1, grid.width)
        # Initialize circles
        circles = [[sp.scatter(x, y, alpha=0.0, c='k') for y in range(width)] for x in range(height)]
        lines = {}
        # Initialize lines joining circles
        #     TODO: Figure out how to skip repeating lines
        for x in range(height):
            print "-- Row {} initialized".format(x)
            for y in range(width):
                adjacents = grid.cells[(x, y)][0]
                for adjacent in adjacents:
                    lines[((x, y), adjacent)] = sp.plot((x, adjacent[0]), (y, adjacent[1]), 'k-', alpha=0.0)

    print "Starting Markov chain"

    t = 0
    T = T_init
    while T > T_final:
        t += 1

        T = cooling(t, tau, T_init)

        # Do the Markov chain        
        sites = pick_sites(grid)
        # Apply the Metropolis algorithm
        if grid.has_single_dimer(sites):
            # Decide whether to remove
            if random.random() < math.exp(-1 / T):
                grid.remove_dimer(sites, False)

                if draw_mpl:
                    circles[sites[0][0]][sites[0][1]].set_alpha(0.0)
                    circles[sites[1][0]][sites[1][1]].set_alpha(0.0)
                    lines[(sites[0], sites[1])][0].set_alpha(0.0)
                    lines[(sites[1], sites[0])][0].set_alpha(0.0)

        elif not (grid.cells[sites[0]][1] or grid.cells[sites[1]][1]):
            # Always add dimer to empty sites
            grid.place_dimer(sites, False)

            if draw_mpl:
                circles[sites[0][0]][sites[0][1]].set_alpha(1.0)
                circles[sites[1][0]][sites[1][1]].set_alpha(1.0)
                lines[(sites[0], sites[1])][0].set_alpha(1.0)
                lines[(sites[1], sites[0])][0].set_alpha(1.0)

        if t % frameskip == 0:
            if draw_text:
                print grid.draw()
                time.sleep(0.05)

            if draw_mpl:
                # Redraw the figure
                sp.clear()
                for x in range(height):
                    for y in range(width):
                        if grid.cells[(x, y)][1]:
                            sp.scatter(x, y, c='k')
                sp.set_title("t=%07d, T=%.3f, n_dimers=%d" % (t, T, grid.n_dimers))
                #fig.savefig("./test/%07d_%.3f_%d.png" % (t, T, grid.n_dimers))
                pyplot.draw()

        if t % 10 == 0:
            efficiency = 100.0 * grid.n_dimers / (grid.width * grid.height)
            print ("t: {0:d}, T: {1:.8f}, # dimers: {2:d} ({3:.2f}% efficiency)"
                   .format(t, T, grid.n_dimers, efficiency))

if __name__ == '__main__':
    main(10, True, False)
