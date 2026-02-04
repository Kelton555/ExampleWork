// Kelton
// Program Project 7 - Shapes 3

import java.awt.Point;
import java.awt.Color;
import java.awt.Graphics;

/**
 * A class describing an oval
 * @author Kelton
 * @version 1.0
 */
public class Oval extends Shape {
    /**
     * The constructor for creating a Oval object
     * @param point1 The first Point of the Oval
     * @param point2 The second Point of the Oval
     * @param color The Color of the Oval
     */
    public Oval(Point point1, Point point2, Color color) {
        super(point1, point2, color);
    }

    /**
     * A method to draw the Oval
     * @param g A Graphics object use for drawing
     */
    public void draw(Graphics g) {
        int x, y, wx, wy;

        x = Math.min(getPoint1().x, getPoint2().x);
        wx = Math.max(getPoint1().x, getPoint2().x) - x;

        y = Math.min(getPoint1().y, getPoint2().y);
        wy = Math.max(getPoint1().y, getPoint2().y) - y;

        g.setColor(getColor());
        g.drawOval(x, y, wx, wy);
    }
}
