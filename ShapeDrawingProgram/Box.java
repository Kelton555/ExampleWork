// Kelton
// Program Project 7 - Shapes 3

import java.awt.Point;
import java.awt.Color;
import java.awt.Graphics;

/**
 * A class describing a rectangular box
 * @author Kelton
 * @version 1.0
 */
public class Box extends Shape {
    /**
     * The constructor for creating a Box object
     * @param point1 The first Point of the Box
     * @param point2 The second Point of the Box
     * @param color The Color of the Box
     */
    public Box(Point point1, Point point2, Color color) {
        super(point1, point2, color);
    }

    /**
     * A method to draw the Box
     * @param g A Graphics object use for drawing
     */
    public void draw(Graphics g) {
        int x, y, wx, wy;

        x = Math.min(getPoint1().x, getPoint2().x);
        wx = Math.max(getPoint1().x, getPoint2().x) - x;

        y = Math.min(getPoint1().y, getPoint2().y);
        wy = Math.max(getPoint1().y, getPoint2().y) - y;

        g.setColor(getColor());
        g.drawRect(x, y, wx, wy);
    }
}
