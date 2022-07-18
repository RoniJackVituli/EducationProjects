package GUI;

import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JButton;

import javax.swing.JPanel;


/**
 * This class produces "ok" and "cancel" buttons and adds it to MyPanel
 *  @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * 
 * */

public class Ok_Cancel_Panel extends JPanel {
	
	
	private JButton ok, cancel; 
	
	
	private static final long serialVersionUID = 1L;

	public Ok_Cancel_Panel() {
		ok = new JButton("OK");
		cancel = new JButton("Cancel");
	
		ok.setBackground(Color.GRAY);
		cancel.setBackground(Color.GRAY);
		
		this.setLayout(new GridLayout(0,2,10,10));
		this.add(ok);
		this.add(cancel);
		
	}

	public JButton getOk() {
		return ok;
	}

	public JButton getCancel() {
		return cancel;
	}
}
