import java.util.Random;
import javax.swing.JFrame;

public class Main {
    public static void main(String[] args) {
        // Get these from user input later
        final int width = 50;
        final int height = 50;
        final double tempFinal = 1e-3;
        final double tempInit = 10.0;
        final double tau = 1e4;
        final int frameSkip = 0;

        Random random = new Random();

        int t = 0;
        double temp = tempInit;

        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(width * 10 + 50, height * 10 + 50);
        frame.setVisible(true);

        GridPanel gridPanel = new GridPanel(width, height);
        frame.add(gridPanel);

        while (temp > tempFinal) {
            t++;
            temp = cooling(t, tau, tempInit);

            // Do the Markov chain
            Coordinate[] sites = gridPanel.grid.pickSites();
            if (gridPanel.grid.hasSingleDimer(sites)) {
                if (random.nextDouble() < Math.exp(-1 / temp))
                        gridPanel.grid.removeDimer(sites);
            }
            else if (gridPanel.grid.cells.get(sites[0]).dimer == null
                     && gridPanel.grid.cells.get(sites[1]).dimer == null)
                gridPanel.grid.placeDimer(sites);
            
            if (t % (frameSkip + 1) == 0) {
                System.out.format("%d %f %d\n", t, temp, gridPanel.grid.nDimers);
                gridPanel.repaint();
            }
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
