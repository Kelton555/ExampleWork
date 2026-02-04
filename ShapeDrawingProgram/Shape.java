// Kelton
// Program Project 7 - Shapes 3

import java.awt.Point;
import java.io.Serializable;
import java.awt.Color;
import java.awt.Graphics;

/**
 * A base abstract class for shapes described by two points and a color
 * @author Kelton
 * @version 1.0
 */
public abstract class Shape implements Serializable {
    private Point point1;
    private Point point2;
    private Color color;

    /**
     * Constructor for data members of a Shape object
     * @param point1 The first point describing the shape
     * @param point2 The second point describing the shape
     * @param color The color of the shape
     */
    public Shape(Point point1, Point point2, Color color) {
        this.point1 = point1;
        this.point2 = point2;
        this.color = color;
    }

    /**
     * Gets the first Point of the Shape
     * @return The first Point of the Shape
     */
    public Point getPoint1() {return point1;}

    /**
     * Gets the second Point of the Shape
     * @return The second Point of the Shape
     */
    public Point getPoint2() {return point2;}

    /**
     * Gets the Color of the Shape
     * @return The Color of the Shape
     */
    public Color getColor() {return color;}

    /**
     * Sets the first Point of the Shape to a new Point
     * @param newPoint1 The Point to replace the first Point of the Shape with
     */
    public void setPoint1(Point newPoint1) {point1 = newPoint1;}

    /**
     * Sets the second Point of the Shape to a new Point
     * @param newPoint2 The Point to replace the second Point of the Shape with
     */
    public void setPoint2(Point newPoint2) {point2 = newPoint2;}

    /**
     * Sets the Color of the Shape to a new Color
     * @param newColor The Color to replace the Shape's Color with
     */
    public void setColor(Color newColor) {color = newColor;}

    /**
     * Abstract class for drawing a concrete Shape
     * @param g A Graphics object to use for drawing
     */
    abstract void draw(Graphics g);
}
