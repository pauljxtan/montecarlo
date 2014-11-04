import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;
import javax.swing.JFrame;

import dimers.GridPanel;
import dimers.Coordinate;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length == 0) {
            System.err.println("Input file not given");
            return;
        }

        if (args.length > 1) {
            System.err.println("Too many arguments given");
            return;
        }

        // Read parameters from input file
        File infile = new File(args[0]);
        Scanner scanner = new Scanner(new File(args[0]));
        int gridWidth = scanner.nextInt();
        int gridHeight = scanner.nextInt();
        double tempInit = scanner.nextDouble();
        double tempFinal = scanner.nextDouble();
        double tau = scanner.nextDouble();
        int frameSkip = scanner.nextInt();
        boolean verbose = (scanner.nextInt() == 0) ? false : true;

        Random random = new Random();

        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(GridPanel.PANEL_WIDTH, GridPanel.PANEL_HEIGHT);
        frame.setVisible(true);

        GridPanel gridPanel = new GridPanel(gridWidth, gridHeight);
        frame.add(gridPanel);

        int t = 0;
        double temp = tempInit;

        if (!verbose)
            System.out.println("Simulating...");

        while (temp > tempFinal) {
            t++;
            temp = cooling(t, tau, tempInit);

            // Do the Markov chain
            Coordinate[] sites = gridPanel.pickSites();
            if (gridPanel.hasSingleDimer(sites)) {
                if (random.nextDouble() < Math.exp(-1 / temp))
                        gridPanel.removeDimer(sites);
            }
            else if (gridPanel.hasNoDimer(sites))
                gridPanel.placeDimer(sites);
            
            if (t % (frameSkip + 1) == 0) {
                if (verbose)
                    System.out.format("%d %f %d\n", t, temp, gridPanel.getNDimers());
                gridPanel.repaint();
            }
        }
        // Print the final state
        if (!verbose)
            System.out.format("Final state: %d %f %d\n", t, temp, gridPanel.getNDimers());
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
