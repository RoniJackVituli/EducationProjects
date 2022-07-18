package program;

import javax.swing.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class Main extends JFrame {
   private static final long serialVersionUID = 1L;
   private PostSystemPanel panel;


   
   public static void main(String[]args) {
	   Main fr = new Main();
	   fr.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
	   fr.setSize(1200,700);
	   fr.setVisible(true);
   }

   
   public Main() {
	    super("Post tracking system");
	    panel = new PostSystemPanel(this);
	    add(panel);
	    panel.setVisible(true);
   }
   


}
