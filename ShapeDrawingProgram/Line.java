// Kelton
// Program Project 7 - Shapes 3

import java.awt.Point;
import java.awt.Color;
import java.awt.Graphics;

/**
 * A class describing a line
 * @author Kelton
 * @version 1.0
 */
public class Line extends Shape {
    /**
     * The constructor for creating a Line object
     * @param point1 The first Point of the Line
     * @param point2 The second Point of the Line
     * @param color The Color of the Line
     */
    public Line(Point point1, Point point2, Color color) {
        super(point1, point2, color);
    }

    /**
     * A method to draw the Line
     * @param g A Graphics object use for drawing
     */
    public void draw(Graphics g) {
        g.setColor(getColor());
        g.drawLine(getPoint1().x, getPoint1().y, getPoint2().x, getPoint2().y);
    }
}
