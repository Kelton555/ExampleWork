// Kelton
// Program Project 7 - Shapes 3

import java.util.ArrayList;
import javax.swing.JComponent;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;

/**
 * JComponent to contain, display, and draw new shapes to the screen.
 * @author Kelton
 * @version 1.1
 */
public class DrawingComponent extends JComponent {
    private ArrayList<Shape> shapes = new ArrayList<Shape>();

    private ShapeType shapeType = ShapeType.BOX;
    private Color currentColor = Color.BLACK;
    private boolean trails = false;

    private Point shapeStartingPoint;

    private Shape currentShape;

    @Override
    public void paintComponent(Graphics g) {
        for (Shape shape: shapes) {
            shape.draw(g);
        }
        if (currentShape != null) {
            currentShape.draw(g);
        }
    }

    /**
     * Gets the list of shapes represented in this DrawingComponent
     * @return The list of shapes represented in this DrawingComponent
     */
    protected ArrayList<Shape> getShapes() {
        return shapes;
    }

    /**
     * Sets the list of shapes represented in this DrawingComponent, then redraws it
     * @param shapes The new list of shapes for this DrawingComponent to represent
     */
    protected void setShapes(ArrayList<Shape> shapes) {
        this.shapes = shapes;
        repaint();
    }

    /**
     * Erases all the shapes currently contained by the DrawingComponent
     */
    public void eraseShapes() {
        shapes.clear();
        repaint();
    }

    /**
     * Sets the type of Shape to preview (user picking Shape size) with previewShape(...).
     * @param sType the type of Shape to preview (Enum of ShapeType)
     */
    public void setShapeType(ShapeType sType) {shapeType = sType;}

    /**
     * Sets the Color to draw all new Shapes as
     * @param color Color to draw all new shapes as
     */
    public void setShapeColor(Color color) {currentColor = color;}

    /**
     * Returns the Color that this component is currently drawing new Shapes as
     * @return the Color currently being used for new Shapes
     */
    public Color getShapeColor() {return currentColor;}

    /**
     * Sets the starting point for new Shapes to anchor at
     * @param startingPoint a Point for new Shapes to anchor at
     */
    public void setStartingPoint(Point startingPoint) {shapeStartingPoint = startingPoint;}

    /**
     * Sets whether previewing (user picking Shape size) should leave a trail of Shapes
     * @param trails boolean of whether previewing (user picking Shape size) should leave a trail of the Shape being drawn
     */
    public void setTrails(boolean trails) {this.trails = trails;}

    /**
     * Toggles whether trails should be drawn when previewing (user picking Shape size) Shapes.
     */
    public void toggleTrails() {trails = !trails;}

    /**
     * Gets whether trails are currently being drawn when previewing (user picking Shape size) Shapes
     * @return boolean of whether trails are currently being drawn
     */
    public boolean getTrails() {return trails;}

    /**
     * Displays a non-persistent Shape on the screen. Used to allow a user to change the size of a Shape before finalizing it. The previewed Shape will be drawn when finalizeCurrentShape() is called.
     * If trails are being drawn (is true), every call to this function will store the Shape (it will not be removed when the user moves their mouse).
     * @param endPoint the second point for the Shape to be drawn to. The first (anchor) point is determined by method setStartingPoint(...)
     */
    public void previewShape(Point endPoint) {
        if (shapeStartingPoint != null) {
            if (shapeType == ShapeType.BOX) {
                currentShape = new Box(shapeStartingPoint, endPoint, currentColor);
            } else if (shapeType == ShapeType.OVAL) {
                currentShape = new Oval(shapeStartingPoint, endPoint, currentColor);
            } else {
                currentShape = new Line(shapeStartingPoint, endPoint, currentColor);
            }
    
            if (trails) {
                shapes.add(currentShape);
                currentShape = null;
            }
    
            repaint();
        }
    }

    /**
     * Finalizes the currently previewed Shape and stores it.
     */
    public void finalizeCurrentShape() {
        shapeStartingPoint = null;
        if (currentShape != null) {
            shapes.add(currentShape);
            currentShape = null;
            repaint();
        }
    }
}
