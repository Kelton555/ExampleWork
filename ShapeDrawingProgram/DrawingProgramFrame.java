// Kelton
// Program Project 7 - Shapes 3

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import javax.swing.JColorChooser;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

/**
 * Extension of JFrame set up to allow users to draw with Shapes.
 * @author Kelton
 * @version 1.1
 */
public class DrawingProgramFrame extends JFrame {
    private static final int FRAME_WIDTH = 1000;
    private static final int FRAME_HEIGHT = 800;

    private DrawingComponent drawingArea;

    /**
     * Default constructor
     */
    public DrawingProgramFrame() {
        drawingArea = new DrawingComponent();
        add(drawingArea, BorderLayout.CENTER);

        // https://stackoverflow.com/questions/11428573/write-a-string-on-a-jpanel-centered
        // https://stackoverflow.com/questions/6810581/how-to-center-the-text-in-a-jlabel
        JLabel instructionPanel = new JLabel("(E)rase (T)rails (L)ine (B)ox (O)val (C)olor (S)ave (R)estore", SwingConstants.CENTER);
        instructionPanel.setFont(new Font("Arial", Font.PLAIN, 18));
        instructionPanel.setForeground(Color.BLACK);
        add(instructionPanel, BorderLayout.SOUTH);

        drawingArea.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent event) {
                drawingArea.setStartingPoint(event.getPoint());
            }
    
            @Override
            public void mouseReleased(MouseEvent event) {
                drawingArea.finalizeCurrentShape();
            }
        });

        // https://stackoverflow.com/questions/15574065/java-mousedragged-and-moving-around-in-a-graphical-interface
        drawingArea.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent event) {
                drawingArea.previewShape(event.getPoint());
            }
        });

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent event) { // https://stackoverflow.com/questions/10876491/how-to-use-keylistener
                int key = event.getKeyCode();

                if (key == KeyEvent.VK_E) {
                    drawingArea.eraseShapes();
                } else if (key == KeyEvent.VK_T) {
                    drawingArea.toggleTrails();
                } else if (key == KeyEvent.VK_L) {
                    drawingArea.setShapeType(ShapeType.LINE);
                } else if (key == KeyEvent.VK_B) {
                    drawingArea.setShapeType(ShapeType.BOX);
                } else if (key == KeyEvent.VK_O) {
                    drawingArea.setShapeType(ShapeType.OVAL);
                } else if (key == KeyEvent.VK_C) {
                    // https://stackoverflow.com/questions/26565166/how-to-display-a-color-selector-when-clicking-a-button
                    drawingArea.setShapeColor(JColorChooser.showDialog(drawingArea, "Choose a color", drawingArea.getShapeColor()));
                } else if (key == KeyEvent.VK_S) { // save to file
                    // https://stackoverflow.com/questions/14589386/how-to-save-file-using-jfilechooser-in-java
                    JFileChooser saveFileChooser = new JFileChooser(".");
                    if (saveFileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
                        try {
                            try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(saveFileChooser.getSelectedFile()))) {
                                out.writeObject(drawingArea.getShapes());
                            }
                        } catch (IOException e) {
                            System.out.println("DEBUG ERROR: IOException thrown while attempting to save.");
                        }
                    }
                } else if (key == KeyEvent.VK_R) { // load from file
                    JFileChooser loadFileChooser = new JFileChooser(".");
                    if (loadFileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
                        try {
                            try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(loadFileChooser.getSelectedFile()))) {
                                drawingArea.setShapes((ArrayList<Shape>) in.readObject());
                            }
                        } catch (IOException e) {
                            System.out.println("DEBUG ERROR: IOException thrown while attempting to load. " + e.getMessage());
                        } catch (ClassNotFoundException e) {
                            System.out.println("DEBUG ERROR: ClassNotFoundException thrown while attempting to load. " + e.getMessage());
                        }
                    }
                }
            }
        });

        setSize(FRAME_WIDTH, FRAME_HEIGHT);
        setTitle("Drawing Program");
    }
}
