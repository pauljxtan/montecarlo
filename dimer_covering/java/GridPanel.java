import java.util.HashMap;

import java.awt.BasicStroke;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;

import javax.swing.JPanel;

public class GridPanel extends JPanel {
    private Grid grid;
    // Cells are squares
    private int cellWidth;

    // Hard-code dimensions
    public static final double CELL_CIRC_RATIO = 0.8;
    public static final int PANEL_WIDTH = 640;
    public static final int PANEL_HEIGHT = 640;
    public static final int PANEL_MARGIN = 10;

    public GridPanel(int gridWidth, int gridHeight) {
        this.grid = new Grid(gridWidth, gridHeight);

        if (gridWidth <= gridHeight)
            this.cellWidth = (PANEL_WIDTH - 2 * PANEL_MARGIN) / gridWidth;
        else
            this.cellWidth = (PANEL_HEIGHT - 2 * PANEL_MARGIN) / gridHeight;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2 = (Graphics2D) g;

        for (int i = 0; i < grid.height; i++) {
            for (int j = 0; j < grid.width; j++) {
                Coordinate coord = new Coordinate(i, j);
                Dimer dimer = grid.cells.get(coord).dimer;
                if (dimer != null) {
                    g2.fill(new Ellipse2D.Double(PANEL_MARGIN + (j + 1.0 - CELL_CIRC_RATIO) * cellWidth,
                                                 PANEL_MARGIN + (i + 1.0 - CELL_CIRC_RATIO) * cellWidth,
                                                 CELL_CIRC_RATIO * cellWidth, 
                                                 CELL_CIRC_RATIO * cellWidth));
                    // Set line thickness
                    g2.setStroke(new BasicStroke(cellWidth / 5));
                    // Draw line (TODO: skip repeated lines)
                    g2.drawLine(PANEL_MARGIN + (2 * dimer.sites[0].y + 1) * cellWidth / 2,
                                PANEL_MARGIN + (2 * dimer.sites[0].x + 1) * cellWidth / 2,
                                PANEL_MARGIN + (2 * dimer.sites[1].y + 1) * cellWidth / 2,
                                PANEL_MARGIN + (2 * dimer.sites[1].x + 1) * cellWidth / 2);
                }
            }
        }
    }

    //----- Encapsulation for Grid methods
        
    public HashMap<Coordinate, CellData> getCells() {
        return grid.cells;
    }

    public Coordinate[] pickSites() {
        return grid.pickSites();
    }

    public boolean hasSingleDimer(Coordinate[] sites) {
        return grid.hasSingleDimer(sites);
    }

    public void removeDimer(Coordinate[] sites) {
        grid.removeDimer(sites);
    }

    public void placeDimer(Coordinate[] sites) {
        grid.placeDimer(sites);
    }

    public int getNDimers() {
        return grid.nDimers;
    }

    //-----
}
