package dimers;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;

/**
 * Represents the grid of specified width and height on which dimers are
 * placed; the main data structure is a <code>HashMap</code> that maps cell
 * coordinates to its adjacent cells and to <code>Dimer</code> objects (if
 * they are present).
 */
class Grid {
    int width;
    int height;
    int nDimers = 0;
    HashMap<Coordinate, CellData> cells = new HashMap<Coordinate, CellData>();
    private Random random = new Random();

    /**
     * @param width the width of the grid
     * @param height the height of the grid
     */
    Grid(int width, int height) {
        this.width = width;
        this.height = height;
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++)
                this.cells.put(new Coordinate(x, y), new CellData());
        }
        for (Coordinate coordinate : cells.keySet())
            this.cells.get(coordinate).adjacentCells = getAdjacentCells(coordinate);
    }

    /**
     * Returns an <code>ArrayList</code> of cells adjacent to the given cell.
     *
     * @param coordinate the coordinate for which to find adjacent cells
     * @return the list of adjacent cells
     */
    private ArrayList<Coordinate> getAdjacentCells(Coordinate coordinate) {
        ArrayList<Coordinate> adjacents = new ArrayList<Coordinate>();
        Coordinate[] possibleAdjacents = {
            new Coordinate(coordinate.x - 1, coordinate.y),
            new Coordinate(coordinate.x + 1, coordinate.y),
            new Coordinate(coordinate.x, coordinate.y - 1),
            new Coordinate(coordinate.x, coordinate.y + 1)
        };
        for (Coordinate coord : possibleAdjacents) {
            if (this.cells.containsKey(coord))
                adjacents.add(coord);
        }
        return adjacents;
    }

    /**
     * Places a dimer on the given sites, if they are both empty.
     *
     * @param sites the two sites at which to place the dimer
     */
    void placeDimer(Coordinate[] sites) {
        if (this.cells.get(sites[0]).dimer != null
            || this.cells.get(sites[0]).dimer != null)
            return;
        Dimer dimer = new Dimer(sites);
        this.cells.get(sites[0]).dimer = dimer;
        this.cells.get(sites[1]).dimer = dimer;
        nDimers++;
    }

    /**
     * Removes the dimer occupying the given sites, if present.
     *
     * @param sites the sites from which to remove the dimer
     */
    void removeDimer(Coordinate[] sites) {
        if (hasSingleDimer(sites)) {
            this.cells.get(sites[0]).dimer = null;
            this.cells.get(sites[1]).dimer = null;
            nDimers--;
        }
    }

    /**
     * Checks if the given sites are occupied by a single dimer.
     *
     * @param sites the sites to check
     */
    boolean hasSingleDimer(Coordinate[] sites) {
        if (this.cells.get(sites[0]).dimer != null
            && this.cells.get(sites[0]).dimer == this.cells.get(sites[1]).dimer)
            return true;
        return false;
    }

    /**
     * Checks if neither site is occupied by a dimer.
     *
     * @param sites the sites to check
     */
    boolean hasNoDimer(Coordinate[] sites) {
        if (this.cells.get(sites[0]).dimer == null && this.cells.get(sites[1]).dimer == null)
            return true;
        return false;
    }

    /**
     * Randomly selects two adjacent sites to feed into the Markov chain.
     *
     * @return the two chosen sites
     */
    Coordinate[] pickSites() {
        Coordinate site1 = new Coordinate(random.nextInt(this.height),
                                          random.nextInt(this.width));
        ArrayList<Coordinate> adjacents = this.cells.get(site1).adjacentCells;
        Coordinate site2 = new Coordinate(adjacents.get(random.nextInt(adjacents.size())));
        Coordinate[] sites = {site1, site2};
        return sites;
    }
}
