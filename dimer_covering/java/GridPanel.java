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
                if (grid.cells.get(new Coordinate(i, j)).dimer != null) 
                    g2.fill(new Ellipse2D.Double((i+1)*10, (j+1)*10, 8, 8));
            }
        }
    }
}
