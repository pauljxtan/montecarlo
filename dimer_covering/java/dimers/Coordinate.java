package dimers;

/**
 * An immutable pair structure for storing (x,y) coordinates, meant to be used
 * as keys for the <code>HashMap</code> delineating cells on the grid.
 */
public class Coordinate {
    final int x;
    final int y;

    /**
     * @param x the x-coordinate
     * @param y the y-coordinate
     */
    public Coordinate(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * @param other the (x,y) coordinate to copy
     */
    public Coordinate(Coordinate other) {
        this.x = other.x;
        this.y = other.y;
    }

    @Override
    public boolean equals(Object other) {
        Coordinate o = (Coordinate) other;
        return (this.x == o.x && this.y == o.y);
    }

    @Override
    public int hashCode() {
        int hash = 1;
        hash = hash * 17 + this.x;
        hash = hash * 31 + this.y;
        return hash;
    }
}
