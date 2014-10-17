class WalkerSelfAvoid extends Walker {

    @Override
    public void step(boolean verbose) {
        this.x_new = this.getCurrentX();
        this.y_new = this.getCurrentY();

        // Check if walker is stuck
        if (this.position.contains(new Coordinate(this.getCurrentX() + 1,
                                                  this.getCurrentY())) &&
            this.position.contains(new Coordinate(this.getCurrentX() - 1,
                                                  this.getCurrentY())) &&
            this.position.contains(new Coordinate(this.getCurrentX(),
                                                  this.getCurrentY() + 1)) &&
            this.position.contains(new Coordinate(this.getCurrentX(),
                                                  this.getCurrentY() - 1))) {
            // Terminate walk
            System.exit(0);
        }

        while (this.position.contains(new Coordinate(this.x_new, this.y_new))) {
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
               }

            this.position.add(new Coordinate(this.x_new, this.y_new));
            
            if (verbose)
                this.printCurrentState();

            this.nSteps++;
    }
}
