package dimers;

/**
 * Represents a dimer occupying two sites.
 */
class Dimer {
    Coordinate[] sites;

    /**
     * @param sites the two sites occupied by the dimer
     */
    Dimer(Coordinate[] sites) {
        this.sites = sites;
    }
}
