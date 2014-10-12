import math, random
from matplotlib import pyplot

"""
Generates solutions to the dimer-covering problem using simulated annealing.
"""

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
            if verbose:
                print "Site(s) is/are occupied; skipping"
            return
        
        dimer = Dimer(sites)
        self.cells[sites[0]][1] = dimer
        self.cells[sites[1]][1] = dimer
        self.n_dimers += 1

        if verbose:
            print "Placed dimer at", sites

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
        if (self.cells[sites[0]][1] and self.cells[sites[1]][1]
            and self.cells[sites[0]][1] == self.cells[sites[1]][1]):
            return True

        return False

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

def cooling(t, tau, T_max):
    return T_max * math.exp(-t / tau)

def main():
    # Get these from user input later
    T_min = 1e-2
    T_max = 10.0
    tau = 1e4
    width = 20
    height = 20
    frameskip = 100

    print "Initializing the grid..."

    grid = Grid(width, height)

    print "Setting up the animation (might take a while if grid is large)..."

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
        for y in range(width):
            adjacents = grid.cells[(x, y)][0]
            for adjacent in adjacents:
                lines[((x, y), adjacent)] = sp.plot((x, adjacent[0]), (y, adjacent[1]), 'k-', alpha=0.0)

    print "Started Markov chain"

    t = 0
    T = T_max
    while T > T_min:
        t += 1

        T = cooling(t, tau, T_max)

        # Do the Markov chain        
        sites = pick_sites(grid)
        # Apply the Metropolis algorithm
        if grid.has_single_dimer(sites):
            # Decide whether to remove
            if random.random() < math.exp(-1 / T):
                grid.remove_dimer(sites, False)
                circles[sites[0][0]][sites[0][1]].set_alpha(0.0)
                circles[sites[1][0]][sites[1][1]].set_alpha(0.0)
                lines[(sites[0], sites[1])][0].set_alpha(0.0)
                lines[(sites[1], sites[0])][0].set_alpha(0.0)
        elif not (grid.cells[sites[0]][1] or grid.cells[sites[1]][1]):
            # Always add dimer to empty sites
            grid.place_dimer(sites, False)
            circles[sites[0][0]][sites[0][1]].set_alpha(1.0)
            circles[sites[1][0]][sites[1][1]].set_alpha(1.0)
            lines[(sites[0], sites[1])][0].set_alpha(1.0)
            lines[(sites[1], sites[0])][0].set_alpha(1.0)
        if t % frameskip == 0:
            sp.set_title("t=%07d, T=%.3f, n_dimers=%d" % (t, T, grid.n_dimers))
            #fig.savefig("./test/%07d_%.3f_%d.png" % (t, T, grid.n_dimers))
            pyplot.draw()

        if t % 1000 == 0:
            print t, T, grid.n_dimers

if __name__ == '__main__':
    main()
