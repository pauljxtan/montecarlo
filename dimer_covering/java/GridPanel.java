import java.awt.BasicStroke;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;

import javax.swing.JPanel;

public class GridPanel extends JPanel {
    public Grid grid;

    public GridPanel(int width, int height) {
        grid = new Grid(width, height);
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
                    // Draw circle (TODO: hard-coded parameters for now)
                    g2.fill(new Ellipse2D.Double((i + 1) * 10, (j + 1) * 10,
                                                 8, 8));
                    // Make lines thicker
                    g2.setStroke(new BasicStroke(2));
                    // Draw line (TODO: skip repeated lines)
                    g2.drawLine((dimer.sites[0].x + 1) * 10 + 4,
                                (dimer.sites[0].y + 1) * 10 + 4,
                                (dimer.sites[1].x + 1) * 10 + 4,
                                (dimer.sites[1].y + 1) * 10 + 4);
                }
            }
        }
    }
}
