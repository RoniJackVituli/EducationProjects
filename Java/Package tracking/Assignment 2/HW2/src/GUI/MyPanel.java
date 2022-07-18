package GUI;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

import java.awt.GridLayout;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import javax.swing.JScrollPane;
import javax.swing.JTable;


import components.Branch;
import components.Hub;
import components.MainOffice;
import components.NonStandardPackage;
import components.Package;
import components.Status;
import components.Truck;

/**
 * 
 * MyPanel Class
 * This is a class that takes care of displaying the GUI of the system itself.
 * 
 * @author Roni_Jack_Vituli -> 315369967 , Matan_Ben_Ishay -> 205577349
 * */

public class MyPanel extends JPanel{
	
	private static final long serialVersionUID = 1L;
	private JButton [] b_main;
	private String [] name_button = {"Create System", "Start", "Stop", "Resume", "All Package info", "Branch info"};
	private boolean  flagCreate = false;
	private boolean flagStart = false;
	private boolean flagCoordinates = false;
	private boolean flagAll = false;
	private int numOfBranches ;
	private int numOfTrucks;
	private int numOfPackages;
	private MainOffice game;
	private Hub hub;
	private final int DIAMETER = 30; 
	private final int CORDX = 10;
	public final static int HEIGHT = 700;
	public final static int WIDHT = 1200;
	private final int RECT_HEIGHT = 200;
	private final int RECT_WIDHT = 40;
	public static final int PACKCORDClientY = 5;
	public static final int PACKCORDCustomerY = 600;
	
	
	public MyPanel() {
		setBackground(Color.white);
		JPanel p1 = new JPanel();
		p1.setLayout(new GridLayout(0,6));
		
		b_main = new JButton[name_button.length];
		for(int i = 0; i < name_button.length ; i++) {
			b_main[i] = new JButton(name_button[i]);
			b_main[i].addActionListener(new ButtonListener(this,i));
			b_main[i].setBackground(Color.GRAY);
			p1.add(b_main[i]);
		}
		
		this.setLayout(new BorderLayout());
		add("South", p1);
	}
	
	
	//CreateSystem Button
	public void createSystem() {
			JDialog d_create_sys = new JDialog(new JFrame(), "Create post system", true);
			Ok_Cancel_Panel ok_cancel = new Ok_Cancel_Panel();
			SliderPanel slider_panel = new SliderPanel();
			d_create_sys.getContentPane().add(ok_cancel,BorderLayout.SOUTH);			
			d_create_sys.getContentPane().add(slider_panel, BorderLayout.CENTER);
			ok_cancel.getCancel().addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					d_create_sys.dispose();
				}
			});
	
			ok_cancel.getOk().addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					numOfBranches = slider_panel.getSlider_br().getValue();
					numOfTrucks = slider_panel.getSlider_tr().getValue();
					numOfPackages = slider_panel.getSlider_pa().getValue();
					d_create_sys.dispose();
					game = new MainOffice(numOfBranches,numOfTrucks, numOfPackages);
					hub = MainOffice.getHub();
					flagCreate = true;
				}
			});
			d_create_sys.setSize(600 ,400);
			d_create_sys.setVisible(true);
		
	}//end CreateSystem.
	 public void paint(Graphics g)  {
		 super.paint(g);
		 if(flagStart) {
			 int packCordX = 120;
			 for(int i = 0 ; i < game.getNumOfPackage() ; i++) {
				 game.getPackages().get(i).setPackageCordX(packCordX);
				 drawPackage((Graphics2D)g, packCordX, game.getPackages().get(i));
				 packCordX += HEIGHT/numOfPackages;
				 if(game.getPackages().get(i) instanceof NonStandardPackage)
					 drawLineBetWeenPackagesAndNonStandardTruck(game.getPackages().get(i), hub.getTrucks().get(numOfTrucks),(Graphics2D)g);
				 else
					 drawLineBetWeenPackagesAndBranch(game.getPackages().get(i), hub.getBranches() ,(Graphics2D)g);
			 }
		 }
		 if(flagCreate) {
			 int whereToGo = 270 + RECT_HEIGHT/numOfBranches - (RECT_HEIGHT/numOfBranches);
			 int spaceBetweenBranch;
			 for(int i = 0 ; i < numOfBranches; i++) {
				 spaceBetweenBranch =305 -(numOfBranches*30) + (i*65);
				 drawline(hub.getBranches().get(i), (Graphics2D)g, whereToGo, spaceBetweenBranch);
				 drawBranch(hub.getBranches().get(i), (Graphics2D)g, spaceBetweenBranch);
				 whereToGo += (RECT_HEIGHT/numOfBranches);
			 }
			 drawHub(hub ,(Graphics2D)g); 	
		 }
		 repaint();      
	}
	 
	 
	 //This method takes care of drawing the package
	 public void drawPackage(Graphics2D g2D, int x, Package p) {
		 if(p instanceof NonStandardPackage) {
			 if(p.getStatus() == Status.COLLECTION || p.getStatus() == Status.CREATION) {
				 g2D.setColor(Color.red);
				 p.setPackageCordClientY(PACKCORDClientY);
				 g2D.fillOval(x, PACKCORDClientY, DIAMETER,DIAMETER);
				 p.setPackageCordCustomerY(PACKCORDCustomerY);
				 g2D.setColor(Color.pink);
				 g2D.fillOval(x, PACKCORDCustomerY, DIAMETER,DIAMETER);
			 }else if(p.getStatus() == Status.DELIVERED) {
				 g2D.setColor(Color.pink);
				 p.setPackageCordClientY(PACKCORDClientY);
				 g2D.fillOval(x, PACKCORDClientY, DIAMETER,DIAMETER);
				 p.setPackageCordCustomerY(PACKCORDCustomerY);
				 g2D.setColor(Color.red);
				 g2D.fillOval(x, PACKCORDCustomerY, DIAMETER,DIAMETER);
			 }else {
				 g2D.setColor(Color.pink);
				 p.setPackageCordClientY(PACKCORDClientY);
				 g2D.fillOval(x, PACKCORDClientY, DIAMETER,DIAMETER);
				 p.setPackageCordCustomerY(PACKCORDCustomerY);
				 g2D.setColor(Color.pink);
				 g2D.fillOval(x, PACKCORDCustomerY, DIAMETER,DIAMETER);
			 }
		 }else{
			 if(p.getStatus() == Status.COLLECTION) {
				 g2D.setColor(Color.red);
				 p.setPackageCordClientY(PACKCORDClientY);
				 g2D.fillOval(x, PACKCORDClientY, DIAMETER,DIAMETER);
				 p.setPackageCordCustomerY(PACKCORDCustomerY);
				 g2D.setColor(Color.pink);
				 g2D.fillOval(x, PACKCORDCustomerY, DIAMETER,DIAMETER);			
				 
			 }else if(p.getStatus() == Status.DELIVERED) {
				 g2D.setColor(Color.pink);
				 p.setPackageCordClientY(PACKCORDClientY);
				 g2D.fillOval(x, PACKCORDClientY, DIAMETER,DIAMETER);
				 p.setPackageCordCustomerY(PACKCORDCustomerY);
				 g2D.setColor(Color.red);
				 g2D.fillOval(x, PACKCORDCustomerY, DIAMETER,DIAMETER);
			 }else{
				 g2D.setColor(Color.pink);
				 p.setPackageCordClientY(PACKCORDClientY);
				 g2D.fillOval(x, PACKCORDClientY, DIAMETER,DIAMETER);
				 p.setPackageCordCustomerY(PACKCORDCustomerY);
				 g2D.fillOval(x, PACKCORDCustomerY, DIAMETER,DIAMETER);
			 }
		 }
	 }
	 
	 
	 
	 //a method that draws the sorting center and also takes care of drawing the trucks associated with it
	 public void drawHub(Hub hub,Graphics2D g2D) {
		 g2D.setColor(new Color(17,59,8));
		 g2D.fillRect(WIDHT-100, HEIGHT/2 - RECT_HEIGHT/2 , RECT_WIDHT, RECT_HEIGHT);
		 if(flagStart) {
			 if(!flagCoordinates) {
				 int where =  (HEIGHT/2 - RECT_HEIGHT/2) + 10;
				 for(int i = 0 ; i < numOfTrucks ; i++) {
					 hub.getTrucks().get(i).getLocation().x = 1100;
					 hub.getTrucks().get(i).getLocation().y = where-7;
					 drawTruck(Color.green, g2D, hub.getTrucks().get(i).getLocation().getX(), hub.getTrucks().get(i).getLocation().getX());
					 where +=   (RECT_HEIGHT/numOfBranches);
				 }
				 hub.getTrucks().get(numOfTrucks).getLocation().x = 1125;
				 hub.getTrucks().get(numOfTrucks).getLocation().y =  245;
				 drawTruck(Color.red, g2D, hub.getTrucks().get(numOfTrucks).getLocation().getX(), (hub.getTrucks().get(numOfTrucks).getLocation().getY()));
				 flagCoordinates = true;
			 
			 }else{
				 for(int i = 0 ; i < hub.getTrucks().size() - 1  ; i++) {
					 if(hub.getTrucks().get(i).getPackages().isEmpty()) {
						 drawTruck(Color.green, g2D, hub.getTrucks().get(i).getLocation().getX(), hub.getTrucks().get(i).getLocation().getY());
					 }else {
						 drawTruck(new Color(0,65,0), g2D, hub.getTrucks().get(i).getLocation().getX(), hub.getTrucks().get(i).getLocation().getY());
						 g2D.drawString(String.valueOf(hub.getTrucks().get(i).getPackages().size()),  (int)hub.getTrucks().get(i).getLocation().getX()+5 ,(int)hub.getTrucks().get(i).getLocation().getY()-8);
					 }
				 }
				 if(hub.getTrucks().get(numOfTrucks).getPackages().isEmpty())
					 drawTruck(Color.pink, g2D, (int)hub.getTrucks().get(numOfTrucks).getLocation().getX(), hub.getTrucks().get(numOfTrucks).getLocation().getY());
				 else
					 if(hub.getTrucks().get(numOfTrucks).getPackages().get(0).getStatus() != Status.COLLECTION)
						 drawTruck(Color.red, g2D, (int)hub.getTrucks().get(numOfTrucks).getLocation().getX(), hub.getTrucks().get(numOfTrucks).getLocation().getY());
					 else 
						 drawTruck(Color.pink, g2D, (int)hub.getTrucks().get(numOfTrucks).getLocation().getX(), hub.getTrucks().get(numOfTrucks).getLocation().getY());
			 }	
		 }
	 }

	 //this method draws a line.
	 public void drawline(Branch br, Graphics2D g2D, int whereToGo, int spaceBetweenBranch) {
		 g2D.setColor(new Color(17,59,8));
		 g2D.drawLine(CORDX+40, spaceBetweenBranch+15 , 1100, whereToGo);
		 br.getLocation().x = CORDX+40;
		 br.getLocation().y = spaceBetweenBranch+15;
		 
		 br.getTarget().x = 1100;
		 br.getTarget().y = whereToGo;
		 
	 }

	 //A method that draws the branch and also takes care of drawing the vans belonging to these
	 public void drawBranch(Branch br, Graphics2D g2D, int spaceBetweenBranch) {
		 if(br.getPackages().isEmpty()){ ;
			 g2D.setColor(Color.cyan);
			 g2D.fillRect(CORDX, spaceBetweenBranch, 40, 30);
			 if(!flagCoordinates) {
				 for(int i = 0 ; i < br.getTrucks().size(); i++) {
					 br.getTrucks().get(i).getLocation().x = CORDX+40;
					 br.getTrucks().get(i).getLocation().y = spaceBetweenBranch+5;
				 }
			 }
		 }else {
			 for(int i = 0 ; i < br.getTrucks().size() ; i++) {
				 if(!br.getTrucks().get(i).isAvailable()) {
					 drawTruck(Color.blue, g2D , br.getTrucks().get(i).getLocation().getX(), br.getTrucks().get(i).getLocation().getY());
					 g2D.setColor(Color.cyan);
				 	 g2D.fillRect(CORDX, spaceBetweenBranch, 40, 30);
				 }
			 }if(br.ThereIsBranchStorage()) {
				 g2D.setColor(Color.blue);
		 	     g2D.fillRect(CORDX, spaceBetweenBranch, 40, 30);
			 }else {
				 g2D.setColor(Color.cyan);
			 	 g2D.fillRect(CORDX, spaceBetweenBranch, 40, 30);
			 }
		 }
	 }
	 
	 //This method draws a truck and also the wheels of the truck
	 public void drawTruck(Color c,Graphics2D g2D, double x, double y) {
		 Rectangle2D rect = new Rectangle2D.Double(x+0.3, y-0.3, 16, 16);
		 g2D.setColor(c);
		 g2D.fill(rect);
		 drawWheels(g2D, (int)x-5, (int)y-3); // left up wheel
		 drawWheels(g2D, (int)x+10, (int)y-3);// right up wheel
		 drawWheels(g2D, (int)x-5, (int)y+10);// left down wheel
		 drawWheels(g2D, (int)x+10, (int)y+10);// right down wheel
	 }
	 
	//This method draws the line that connects a non-standard truck to a package that it needs to collect.
	 public void drawLineBetWeenPackagesAndNonStandardTruck(Package p, Truck truck ,Graphics2D g2D) {
		 g2D.setColor(Color.red);
		 g2D.drawLine((int)p.getPackageCordX()+10, (int)PACKCORDClientY+28, 1125, 250);
		 g2D.drawLine((int)p.getPackageCordX()+15 ,(int)PACKCORDClientY+27, (int)p.getPackageCordX()+15, PACKCORDCustomerY+4);
	 }
	 
	 //This method draws a line between the branches and the packages that correspond to the branch
	 public void drawLineBetWeenPackagesAndBranch(Package p, ArrayList<Branch> b ,Graphics2D g2D) {
		 g2D.setColor(Color.blue);
		 
		 p.setWhereToGoClient(new Point((int)b.get(p.getSenderAddress().getZip()).getLocation().getX(),(int)b.get(p.getSenderAddress().getZip()).getLocation().getY())); 
		 p.setWhereToGoCustomer(new Point((int)b.get(p.getDestinationAddress().getZip()).getLocation().getX(), (int)b.get(p.getDestinationAddress().getZip()).getLocation().getY()));
		 
		 g2D.drawLine((int)p.getPackageCordX()+10, PACKCORDClientY+27,(int)p.getWhereToGoClient().getX(), (int) p.getWhereToGoClient().getY());
		 
		 //Customer.
		 g2D.drawLine((int)p.getPackageCordX()+10, PACKCORDCustomerY+2 , (int)p.getWhereToGoCustomer().getX(), (int)p.getWhereToGoCustomer().getY());
	 }
	 
	 //This method draws wheels.
	 public void drawWheels(Graphics2D g2D ,int x, int y ) {
		 g2D.setColor(Color.BLACK);
		 g2D.fillOval(x,y,DIAMETER-20,DIAMETER-20);
	 }
	
	 
	 
	 public void start() {
		 if(flagCreate) {
			flagStart = true;
			new Thread(game).start();
		 }else {
			JOptionPane.showMessageDialog(new JFrame(), "You have not created yet a post office");
		 }
	 }
	 
	 
	 /**
	  * branchInfo()
	  * This method prints all the information of the packages related to their affiliated branches
	  * */
	 
	 public void branchInfo() {
		 if(flagStart) {
			 JDialog info = new JDialog();
			 info.setTitle("Choose Branch");
			 Ok_Cancel_Panel ok_cancel = new Ok_Cancel_Panel();
			 info.getContentPane().add(ok_cancel,BorderLayout.SOUTH);			
			 String [] branches = new String[numOfBranches + 1];
			 branches[0] = "Sorting center";
			 for(int i = 1 ; i <= numOfBranches ; i++) {
				 branches[i] = "Branch " + i;
			 }
			 JComboBox<String> comboBox = new JComboBox<String>(branches);
			 
			 ok_cancel.getOk().addActionListener(comboBox);
	
			 comboBox.addActionListener(new ActionListener() {
					
				@Override
				public void actionPerformed(ActionEvent e) {
					if(e.getSource().equals(comboBox)) {
						String str = comboBox.getItemAt(comboBox.getSelectedIndex());
						if(str == null)
							str = "Sorting center";
						String[] columnNames= {"PACKAGE ID","SENDER","DESTINATION","PRIORITY","STATUS"};
						System.out.println("Str - " + str);
						String str2 = "Sorting center";
						if(str != "Sorting center") {
							for(int k = 0 ; k < numOfBranches; k++) {
								str2 = "Branch " + String.valueOf(k + 1);
								if(str.equals(str2)) {
									int count = 0;
									for(int i = 0 ; i < game.getPackages().size(); i++) {
										if(!(game.getPackages().get(i) instanceof NonStandardPackage) && game.getPackages().get(i).getDestinationAddress().getZip() == k)
											count++;
									}
									String[][] data = new String[count][5];
									
									for(int i = 0 , j = 0; i < game.getPackages().size() && j < count ; i++) {
										Package p = game.getPackages().get(i);
										if(!(game.getPackages().get(i) instanceof NonStandardPackage) && game.getPackages().get(i).getDestinationAddress().getZip() == k && !isInTheTable(data, game.getPackages().get(i), count)) {
												 data[j][0]=String.valueOf(p.getPackageID());
												 data[j][1]=String.valueOf(p.getSenderAddress().getZip()+1 +"-"+game.getPackages().get(i).getSenderAddress().getStreet());
												 data[j][2]=String.valueOf(p.getDestinationAddress().getZip()+1 +"-"+game.getPackages().get(i).getDestinationAddress().getStreet());
												 data[j][3]=String.valueOf(p.getPriority());
												 data[j][4]=String.valueOf(p.getStatus());
												 j++;
										}
									}
									JTable table = new JTable(data,columnNames);
									table.setBounds(0, 0, 800, 400);
									table.setEnabled(false);	 
									JScrollPane sp = new JScrollPane(table);
									info.setSize(WIDHT, (table.getRowHeight()*table.getRowCount() + 65));
									info.add(sp);
									info.remove(ok_cancel);
									info.remove(comboBox);
									info.setVisible(true);
									count = 0;
									break;
								}
							}
						}else {
							int count = 0;
							for(int i = 0 ; i < game.getPackages().size(); i++) {
								if((game.getPackages().get(i) instanceof NonStandardPackage))
									count++;
							}
							String[][] data = new String[count][5];
							
							for(int i = 0 , j = 0; i < game.getPackages().size() && j < count ; i++) {
								Package p = game.getPackages().get(i);
								if((game.getPackages().get(i) instanceof NonStandardPackage) && !isInTheTable(data, game.getPackages().get(i), count)) {
										 data[j][0]=String.valueOf(p.getPackageID());
										 data[j][1]=String.valueOf(p.getSenderAddress().getZip()+1 +"-"+game.getPackages().get(i).getSenderAddress().getStreet());
										 data[j][2]=String.valueOf(p.getDestinationAddress().getZip()+1 +"-"+game.getPackages().get(i).getDestinationAddress().getStreet());
										 data[j][3]=String.valueOf(p.getPriority());
										 data[j][4]=String.valueOf(p.getStatus());
										 j++;
								}
							}
							JTable table = new JTable(data,columnNames);
							table.setBounds(0, 0, 800, 400);
							table.setEnabled(false);	 
							JScrollPane sp = new JScrollPane(table);
							info.setSize(WIDHT, table.getRowHeight()*table.getRowCount() + 65);
							info.add(sp);
							info.remove(ok_cancel);
							info.remove(comboBox);
							
							info.setVisible(true);
							count = 0;
						}
					}	
				}
			});
			 
			 info.getContentPane().add(comboBox,BorderLayout.CENTER);		
			 info.setSize(300, 100);
		 
			 info.setVisible(true);
		 }
	 }
	 
	 public boolean isInTheTable(String[][] data, Package p, int count) {
		 if(count == 0)
			 return false;
		 for(int i = 0 ; i < count ; i++) {
			 if(data[i][0] == String.valueOf(p.getPackageID())) {
				 System.out.println("im in the table "+ p.getPackageID());
					 return true;
			 }
		 }
		return false;
	 }
	 
	 
	 /**
	  * allPackagesInfo()
	  * This method prints all the information for all the packages currently in the system!
	  * */
	 public void allPackagesInfo()
	 {
		 if(flagStart) {
			 JFrame info=new JFrame();
			 if(!flagAll) {
				 
				 flagAll=true;
				 info.getContentPane().setBackground(new Color(0,0,0));
				 info.getContentPane().setForeground(Color.white);
				 info.setBounds(0, 0, 800, 400);
				 info.setLocation(0, 0);
				 String[] columnNames= {"PACKAGE ID","SENDER","DESTINATION","PRIORITY","STATUS"};
				 String[][] data=new String[game.getPackages().size()][5];
				 for(int i=0;i<game.getPackages().size();i++)
				 {
					 data[i][0]=String.valueOf(game.getPackages().get(i).getPackageID());
					 data[i][1]=String.valueOf(game.getPackages().get(i).getSenderAddress().getZip()+1 +"-"+game.getPackages().get(i).getSenderAddress().getStreet());
					 data[i][2]=String.valueOf(game.getPackages().get(i).getDestinationAddress().getZip()+1 +"-"+game.getPackages().get(i).getDestinationAddress().getStreet());
					 data[i][3]=String.valueOf(game.getPackages().get(i).getPriority());
					 data[i][4]=String.valueOf(game.getPackages().get(i).getStatus());
				 }			 
				 JTable table = new JTable(data,columnNames);
				 table.setBounds(0, 0, 800, 400);
				 table.setEnabled(false);	 
				 JScrollPane sp = new JScrollPane(table);
				 info.add(sp);
				 info.setSize(WIDHT, table.getRowHeight()*table.getRowCount() + 65);
				 info.setVisible(true);
			 }else {
				 info.dispose();
				 flagAll = false;
			 }
		 }
	 }
	 

	 
	 
	 
	 /**
	  * Class ButtonListener
	  * Takes care of all the pressures that occur in the system and knows what to turn on and what to do.
	  * 
	  *   * */ 
class ButtonListener implements ActionListener{

	private MyPanel panel; 
	private int choice;
	
	public ButtonListener(MyPanel p, int choice) {
		this.panel = p;
		this.choice = choice;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		
		switch (choice) {
		case 0: 
			panel.createSystem();
			break;
		case 1:
			MainOffice.Flag = true;
			panel.start();
			break;
		case 2:
			MainOffice.Flag = false;
			break;
		case 3:
			MainOffice.Flag = true;
			panel.start();
			//panel.resume();
			break;
		case 4:
			panel.allPackagesInfo();
			break;
		case 5:
			panel.branchInfo();
			break;
		}
		
	}
	
	
}
	
}
