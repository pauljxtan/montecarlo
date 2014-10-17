import java.util.ArrayList;

public class Walker {
    
    public int nSteps = 0;
    public int x_new, y_new;
    public double test;
    public ArrayList<Coordinate> position = new ArrayList<Coordinate>();

    public Walker() {
        this.position.add(new Coordinate(0, 0));
    }

    public Walker(int x0, int y0) {
        this.position.add(new Coordinate(x0, y0));
    }

    public int getCurrentX() {
        return this.lastPosition(this.position).x;
    }
    
    public int getCurrentY() {
        return this.lastPosition(this.position).y;
    }

    public int[] getAllX() {
        int[] x = new int[this.nSteps];
        for (int i = 0; i < this.nSteps; i++)
            x[i] = this.position.get(i).x;
        return x;
    }
    
    public int[] getAllY() {
        int[] y = new int[this.nSteps];
        for (int i = 0; i < this.nSteps; i++)
            y[i] = this.position.get(i).y;
        return y;
    }

    public int getNumberOfSteps() {
        return this.nSteps;
    }

    public void printCurrentState() {
        System.out.format("%d %d %d %.2f\n", this.nSteps, this.getCurrentX(),
                          this.getCurrentY(), this.getDisp());
    }

    /**
     * Returns the displacement from the starting position.
     * @return displacement
     */
    public double getDisp() {
        return Math.sqrt(Math.pow(this.getCurrentX() -
                                  this.position.get(0).x, 2) +
                         Math.pow(this.getCurrentY() -
                                  this.position.get(0).y, 2));
    }

    /**
     * Returns the displacement from the specified position.
     * @param idx index of specified position
     * @return displacement
     */
    public double getDisp(int idx) {
        return Math.sqrt(Math.pow(this.position.get(idx).x -
                                  this.position.get(0).x, 2) +
                         Math.pow(this.position.get(idx).y -
                                  this.position.get(0).y, 2));
        
    }

    public void step(boolean verbose) {
        this.test = Math.random();

        if (this.test < 0.25) {
            // Move up
            this.x_new = this.getCurrentX();
            this.y_new = this.getCurrentY() + 1;
        }
        else if (this.test < 0.5) {
            // Move down
            this.x_new = this.getCurrentX();
            this.y_new = this.getCurrentY() - 1;
        }
        else if (this.test < 0.75) {
            // Move right
            this.x_new = this.getCurrentX() + 1;
            this.y_new = this.getCurrentY();
        }
        else {
            // Move left
            this.x_new = this.getCurrentX() - 1;
            this.y_new = this.getCurrentY();
        }

        this.position.add(new Coordinate(this.x_new, this.y_new));
        
        if (verbose)
            this.printCurrentState();

        this.nSteps++;
    }

    public void walk(int nSteps, boolean verbose) {
        if (verbose)
            this.printCurrentState();
        for (int n = 0; n < nSteps; n++)
            this.step(verbose);
    }

    private Coordinate lastPosition(ArrayList<Coordinate> z) {
        return z.get(z.size() - 1);
    }
}
