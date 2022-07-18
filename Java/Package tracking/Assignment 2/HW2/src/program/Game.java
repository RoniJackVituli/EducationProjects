package program;

import javax.swing.JFrame;

import GUI.MyPanel;


public class Game {
	public final static int WIDTH = 1200;
	public final static int HEIGHT = 700;
	
	public static void main(String[] args) {

		JFrame window = new JFrame("Post tracking system");
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		MyPanel myPanel = new MyPanel();
		window.add(myPanel);
		window.setSize(WIDTH, HEIGHT);
		window.setVisible(true);
		
	}

}
