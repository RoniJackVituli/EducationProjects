package GUI;


import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;

public class SliderPanel extends JPanel{
	
	
	private JLabel branch, truck, pack;
	private JSlider slider_br , slider_tr , slider_pa;
	
	/**
	 * This is a class which takes care of making the window when I click on the "create system" button and creates slides of choice a few branches, a few packages, a few trucks.
	 *  * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349

	 * */
	
	private static final long serialVersionUID = 1L;
	private static final int NORMAL = 0;

	public SliderPanel() {
		branch = new JLabel("Number of branches");
		truck = new JLabel("Number of truck per branch");
		pack = new JLabel("Number of packages");
		this.setLayout(new GridLayout(0,1));
		
		// Branch slider
		branch.setHorizontalAlignment(NORMAL);
	
		slider_br = new JSlider(1,10,5);
		slider_br.setPaintTicks(true);
		slider_br.setPaintTrack(true);
		slider_br.setMajorTickSpacing(1);
		slider_br.setPaintLabels(true);	
		this.add(branch);
		this.add(slider_br);
		
		
		//Truck Slider
		slider_tr = new JSlider(1,10,5);
		truck.setHorizontalAlignment(NORMAL);
		
		slider_tr .setPaintTicks(true);
		slider_tr.setPaintTrack(true);
		slider_tr.setMajorTickSpacing(1);
		slider_tr .setPaintLabels(true);	
		this.add(truck);
		this.add(slider_tr);
		
		//Package Slider
		slider_pa = new JSlider(2,20,8);
		slider_pa.setPaintTicks(true);
		slider_pa.setMinorTickSpacing(1);
		slider_pa.setPaintTrack(true);
		slider_pa.setMajorTickSpacing(2);
		slider_pa.setPaintLabels(true);	
		
		pack.setHorizontalAlignment(NORMAL);
		this.add(pack);
		this.add(slider_pa);
		
		
	}

	public JSlider getSlider_br() {
		return slider_br;
	}

	public JSlider getSlider_tr() {
		return slider_tr;
	}

	public JSlider getSlider_pa() {
		return slider_pa;
	}





	
	
	
	
}
