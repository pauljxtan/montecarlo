import java.util.Random;

public class Main {
    public static void main(String[] args) {
        // Get these from user input later
        double tempFinal = 1e-3;
        double tempInit = 10.0;
        double tau = 1e4;
        Random random = new Random();

        Grid grid = new Grid(50, 50);
        int t = 0;
        double temp = tempInit;

        while (temp > tempFinal) {
            t++;
            temp = cooling(t, tau, tempInit);

            // Do the Markov chain
            Coordinate[] sites = grid.pickSites();
            if (grid.hasSingleDimer(sites)) {
                if (random.nextDouble() < Math.exp(-1 / temp))
                        grid.removeDimer(sites);
            }
            else if (grid.cells.get(sites[0]).dimer == null
                     && grid.cells.get(sites[1]).dimer == null)
                grid.placeDimer(sites);
            
            if (t % 10000 == 0)
                System.out.format("%d %f %d\n", t, temp, grid.nDimers);
        }
    }

    /**
     * The cooling schedule for determining the probability of state changes
     * in the Markov chain.
     *
     * @param t the current time
     * @param tau the time constant
     * @param tempInit the initial "temperature" of the system
     * @return the new temperature of the system
     */
    private static double cooling(double t, double tau, double tempInit) {
        return tempInit * Math.exp(-t / tau);
    }
}
