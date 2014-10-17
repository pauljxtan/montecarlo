public class Coordinate {
    public final int x;
    public final int y;

    public Coordinate(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object other) {
        Coordinate o = (Coordinate) other;
        return (this.x == o.x && this.y == o.y);
    }
}
