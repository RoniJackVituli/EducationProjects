package GUI;

import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JPanel;

public class MainButton extends JPanel{
	

	/**
	  * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349

	 * It's class which produces me the main page buttons of the window
	 * */
	private static final long serialVersionUID = 1L;
	private JButton cs, start, stop, resume, a_p_i, branch_info;
	private GridLayout table;
	
	public MainButton() {
		super();
		cs = new JButton("Create System"); // create system button.
		start = new JButton("Start");
		stop = new JButton("Stop");
		resume = new JButton("Resume");
		a_p_i = new JButton("All Package info");
		branch_info = new JButton("Branch info");
		
		cs.setBackground(Color.GRAY);
		start.setBackground(Color.GRAY);
		stop.setBackground(Color.GRAY);
		resume.setBackground(Color.GRAY);
		a_p_i.setBackground(Color.GRAY);
		branch_info.setBackground(Color.GRAY);
		
		table = new GridLayout(0,6);
		this.setLayout(table);
		this.add(cs);
		this.add(start);
		this.add(stop);
		this.add(resume);
		this.add(resume);
		this.add(a_p_i);
		this.add(branch_info);
	

	}

	public JButton getCs() {
		return cs;
	}

	public JButton getStart() {
		return start;
	}

	public JButton getStop() {
		return stop;
	}

	public JButton getResume() {
		return resume;
	}

	public JButton getA_p_i() {
		return a_p_i;
	}

	public JButton getBranch_info() {
		return branch_info;
	}

}
