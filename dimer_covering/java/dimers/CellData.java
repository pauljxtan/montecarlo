package dimers;

import java.util.ArrayList;

/**
 * Stores an <code>ArrayList</code> of all adjacent cells and a reference to
 * the <code>Dimer</code> object occupying this site, if any.
 */
class CellData {
    ArrayList<Coordinate> adjacentCells;
    Dimer dimer;
}
